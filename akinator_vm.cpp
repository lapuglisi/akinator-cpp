#include <cstdlib>
#include <iostream>
#include <sstream>

#include "akinator_vm.hpp"

namespace creatures = akinator::creatures;

namespace akinator
{
namespace presenter
{
    ui_handler::ui_handler() : m_humor_me(false)
    {        
    }

    ui_handler::~ui_handler()
    {        
    }

    /* Singleton instance */
    ui_handler* ui_handler::instance()
    {
        static ui_handler singleton;
        return &singleton;
    }

    /* Public methods */
    bool ui_handler::init()
    {
        bool ret_status = false;

        std::string answer;
        akinator::app::console_ui* ui = akinator::app::console_ui::instance();
        creatures::animal_model *model = creatures::animal_model::instance();

        for (;;)
        {
            std::stringstream iss;

            // Start playing
            ui->do_display("\n\n\nGuessing Game!!!\n\n\n");

            iss.clear();
            iss << "Think about an " << model->get_kingdom() << "...\n\n";
            ui->do_display(iss.str());

            ui->do_display("C - Continue\n");
            ui->do_display("X - Exit\n");

            ui->get_answer(answer);

            char chosen = std::towupper(answer[0]);

            if ('C' == chosen)
            {
                ret_status = true;
                break; // the for(;;) loop
            }
            else if ('X' == chosen)
            {
                ui->do_display("\n\nSee you later!");
                if (m_humor_me)
                {
                    ui->do_display(" (You were expecting me to say 'aligator' here, weren't you?)");                    
                }

                ui->do_display("\n");

                ret_status = false;
                break; // the for(;;) loop
            }
            else
            {
                ui->do_display("\n\nSorry, invalid option... Try again, please.");
                continue; // the for(;;) loop
            }
        }

        return ret_status;
    }

    void ui_handler::game_on()
    {
        std::stringstream iss;

        std::string answer;
        akinator::app::console_ui* ui = akinator::app::console_ui::instance();
        creatures::animal_model *model = creatures::animal_model::instance();

        for (;;)
        {
            iss.clear();
            iss.str("");
            iss << "Does the " << model->get_kingdom() << " you tought " << model->get_filter() << "? (Y/N) ";

            ui->do_display(iss.str());
            ui->get_answer(answer);
            char chosen = std::toupper(answer[0]);

            if ('Y' == chosen)
            {
                // Tell 'model' to guess animals that live in water
                break;
            }
            else if ('N' == chosen)
            {
                // Tell 'model' to guess animals that do not live in water
                break;
            }
            else
            {
                ui->do_display("\nInvalid choice\n");
                continue;
            }
        }
    }

    /* Properties */
    void ui_handler::set_humor_me(bool doit)
    {
        this->m_humor_me = doit;
    }
}
}