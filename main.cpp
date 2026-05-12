#include <nodepp/nodepp.h>
#include <redux/redux.h>

using namespace nodepp;

struct Player { float x, y; int health; };

void onMain(){

    redux_t<Player> players;
    
    auto h_player = players.create();
    
    do{ players.update({ 100.0f, 200.0f, 100 }, h_player);
        auto p = players.read( h_player );
        if ( p.has_value() ) { auto x = p.value();
            console::log( x.x, x.y, x.health );
        }
    } while(0);

    do{ players.remove( h_player );
        auto p = players.read( h_player );
        if ( p.has_value() ) { auto x = p.value();
            console::log( x.x, x.y, x.health );
        }
    } while(0);
    
}