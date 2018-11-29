#include <torrent/torrent.hpp>

ACTION torrent::create(name user, std::string title, std::string magnet, std::string hash) {
   // Require Authorization
   require_auth(user);

   // Ensure string length is less than 24.
   eosio_assert(title.length() <= 24, "title length is too long.");
   eosio_assert(magnet.find(magnet_prefix) != std::string::npos, "that is not a magnet link");
   eosio_assert(hash.length() >= 32, "that is not an md5 hash");

   // Check for mutli-index table to emplace into.
   auto useracc = _userdata.find(user.value);

   if (useracc != _userdata.end()) {
       uint64_t lastid;
      if (useracc->torrents.size() > 0) {
         lastid = useracc->torrents.back().id;
      } else {
         lastid = 0;
      }

      // Determine if a title already exists inside of the iterated content.
      for(auto& x : useracc->torrents) {
         eosio_assert(x.title  != title, "that title already exists in your library");
         eosio_assert(x.magnet != magnet, "that magnet link already exists");
         eosio_assert(x.hash   != hash, "that hash already exists");
      }

      // Found the user account.
      _userdata.modify(useracc, user, [&](userdata& x) {
         x.torrents.push_back(magnetdata({lastid + 1, title, magnet, hash}));
      });
   } else {
      // Create the user account.
      _userdata.emplace(user, [&](userdata& x) {
         x.user = user;
         x.torrents.push_back(magnetdata({0, title, magnet, hash}));
      });
   }
}

ACTION torrent::remove(name user, uint64_t id) {
   // Require Authorization
   require_auth(user);

   // Check for mutli-index table to emplace into.
   auto useracc = _userdata.find(user.value);

   // Check if the user has any existing torrents.
   eosio_assert(useracc != _userdata.end(), "user has not posted any torrents.");
   
   // Check if the ID exists and determine the vector position of said item.
   bool does_id_exist = false;
   uint64_t position  = 0;

   for (auto& x : useracc->torrents) {
      if (x.id == id) {
         does_id_exist = true;
         break;
      }
      position += 1;
   }

   eosio_assert(does_id_exist, "the torrent with that id does not exist.");

   // Remove the item.
   _userdata.modify(useracc, user, [&](userdata& x) {
      x.torrents.erase(x.torrents.begin() + position);
   });
}