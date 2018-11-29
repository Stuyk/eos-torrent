find_package(eosio.cdt)
add_contract(torrent torrent ${CMAKE_CURRENT_SOURCE_DIR}/src/torrent.cpp)
#add_executable(torrent.wasm ${CMAKE_CURRENT_SOURCE_DIR}/src/torrent.cpp)
target_include_directories(torrent.wasm
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(torrent.wasm
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")