#ifndef __akinator_vm_hpp__
#define __akinator_vm_hpp__

#include <cstdlib>

#include "akinator_ui.hpp"
#include "akinator_data.hpp"

namespace akinator
{
namespace presenter
{
    class ui_handler
    {
    public:
        ui_handler();
        ~ui_handler();

        /* Delete copy and move constructors */
        ui_handler(const ui_handler&) = delete;
        ui_handler(ui_handler&&) = delete;

        /* Delete copy and move '=' operators */
        ui_handler& operator=(const ui_handler&) = delete;
        ui_handler& operator=(ui_handler&&) = delete;

        void set_question();
        void get_answer();

        static ui_handler *instance();

        /* Interaction methods */
        bool init();
        void game_on();

        /* Properties */
        void set_humor_me(bool /*doit*/);

    private:
        bool m_humor_me;
    };
}
}

#endif // __akinator_vm_hpp__