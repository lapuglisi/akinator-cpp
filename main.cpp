#include <iostream>
#include <string.h>

#include "akinator_vm.hpp"

int main(int argc, char **argv)
{
    akinator::presenter::ui_handler *app = akinator::presenter::ui_handler::instance();    

    /* handle cli arguments */
    for (int _i = 1; _i < argc; _i++)
    {
        if (strcmp(argv[_i], "-humorme") == 0)
        {
            app->set_humor_me(true);
        }
    }
    
    for (;;)
    {
        if ( !app->init() )
        {
            break;
        }
        app->game_on();
    }

    return 0;
}