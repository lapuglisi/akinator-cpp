#ifndef __akinator_ui_hpp__
#define __akinator_ui_hpp__

#include <cstdlib>

namespace akinator
{
namespace app
{
    class console_ui
    {
    private:
        /* CTORs */
        console_ui();
        console_ui(const console_ui&) = delete;
        console_ui(console_ui&&) = delete;

        /* DTORs */
        ~console_ui();

        /* Operators */
        // Delete both copy and move operators
        console_ui& operator=(const console_ui&) = delete; 
        console_ui& operator=(console_ui&&) = delete;

    protected:        

    public:
        static console_ui *instance();

        void do_display(const std::string& /*prompt*/);
        const std::string &get_answer(std::string& /*answer*/);
        const std::string &get_line(std::string& /*answer*/);
    };
}
}

#endif // __akinator_ui_hpp__