# NodePP Redux - O(1) embedded database

designed for realtime data access, `nodepp::redux_t`, unlike traditional Hash Maps that suffer collisions, cache misses and rehashing; Redux utilizes an algorithmic **Pointer Authentication Codes (PAC)** which transforms memory addresses into secure 8-byte tokens that validate their own integrity in O(1) without ever consulting an external index.

## Quick Start

```cpp
#include <nodepp/nodepp.h>
#include <redux/redux.h>

using namespace nodepp;

struct Player { float x, y; int health; };

void onMain(){

    redux_t<Player> players;
    
    auto h_player = players.create(); players.write({ 100.0f, 200.0f, 100 }, h_player);
    auto p = players.read (h_player);

    if( !p.null() ){ console::log( p->x, p->y, p->health ); }
    
}
```