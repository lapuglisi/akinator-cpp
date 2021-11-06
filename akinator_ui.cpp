#include <iostream>
#include <limits>

#include "akinator_ui.hpp"

namespace akinator
{
namespace app
{
    /* CTOR / DTOR */
    console_ui::console_ui()
    {
    }

    console_ui::~console_ui()
    {   
    }

    /* Singleton instance */
    console_ui *console_ui::instance()
    {
        static console_ui singleton;
        return &singleton;
    }

    /* Public methods */
    void console_ui::do_display(const std::string& prompt)
    {
        std::cout.clear();
        std::cout << prompt;
    }

    const std::string &console_ui::get_answer(std::string& answer)
    {
        std::cin.clear();
        std::cin >> answer;

        return answer;
    }

    const std::string &console_ui::get_line(std::string& answer)
    {
        while (std::cin.peek() == '\n')
        {
            std::cin.ignore();
        }

        std::getline(std::cin, answer, '\n');

        return answer;
    }
}
}