#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

#include <vector>
#include <string>

using namespace eosio;

const std::string magnet_prefix = "magnet:?xt=urn:btih:";

typedef std::pair<std::string, std::string> titlemag;
typedef std::pair<name, uint8_t>            votedata;

CONTRACT torrent : public contract {
   public:
      using contract::contract;
      torrent( name receiver, name code, datastream<const char*> ds)
      : contract(receiver, code, ds), _userdata(receiver, receiver.value) {}

      // Create a new torrent to add to storage.
      ACTION create(name user, std::string title, std::string magnet, std::string hash);

      // Remove a torrent.
      ACTION remove(name user, uint64_t id);

      TABLE magnetdata {
         uint64_t       id;
         std::string    title;
         std::string    magnet;
         std::string    hash;
         votedata       data;
      };

      TABLE userdata {
         name                       user;
         std::vector<magnetdata>   torrents;

         uint64_t primary_key() const { return user.value; }
      };

      typedef eosio::multi_index<"userdata"_n, userdata> userdat;

   private:
      userdat _userdata;
};

EOSIO_DISPATCH(torrent, (create)(remove))