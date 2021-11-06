#include <cstdlib>
#include <iostream>
#include <sstream>

#include "akinator_vm.hpp"

namespace models = akinator::creatures;

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
        models::animal_model *model = models::animal_model::instance();

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

    bool ui_handler::game_on()
    {
        bool yes_chosen = false;

        std::stringstream iss;

        std::string answer;
        akinator::app::console_ui* ui = akinator::app::console_ui::instance();
        models::animal_model *model = models::animal_model::instance();

        models::creature_type_t animal_type = models::animal_model::default_type;

        models::creature_types_t::const_iterator it;
        for (it = model->get_types().begin(); 
             it != model->get_types().end(); it++)
        {
            // Iterate through animal types
            for (;;)
            {
                iss.clear();
                iss.str("");
                
                iss << "Does the " << model->get_kingdom() << " you tought " << it->second << "? (Y/N) ";

                yes_chosen = ask_yes_no(iss.str(), answer);
                if (yes_chosen)
                {
                    // Tell 'model' to guess animals with type == it->first
                    animal_type = it->first;
                    break;
                }
                else
                {
                    // Must guess another animal type
                    break;
                }
            } // for (it animal_types)
        }

        if (animal_type > 0)
        {
            return guess_by_type(animal_type);
        }

        return false;
    }

    bool ui_handler::guess_by_type(models::creature_type_t type)
    {
        bool success = false;
        bool yes_chosen = false;

        std::string answer;
        std::stringstream iss;

        akinator::app::console_ui* ui = akinator::app::console_ui::instance();
        models::animal_model *model = models::animal_model::instance();
        
        models::creature_collection_t creatures;
        models::creature_collection_t::iterator it;
        
        model->filter_by_type(creatures, type);

        for (it = creatures.begin(); it != creatures.end(); it++)
        {
            iss.clear();
            iss.str("");

            iss << "Does the animal you tought " << it->get_ability() << "? (Y/N) ";
            yes_chosen = ask_yes_no(iss.str(), answer);

            if (yes_chosen)
            {
                iss.clear();
                iss.str("");
                iss << "Is the animal you thought about a " << it->get_name() << "? (Y/N) ";

                yes_chosen = ask_yes_no(iss.str(), answer);
                if (yes_chosen)
                {
                    // display "I'm a winner"
                    im_a_winner();
                    success = true;
                    break; // the for(it) loop
                }
                else // answer == 'N'
                {
                    ask_for_creature(type, *it);
                    success = true;
                }
            }
            else // answer == 'N'
            {
                continue; // the for (it) loop
            }
        }

        // Hasn't guessed yet.
        // Try default options
        if (!success)
        {
            // Must proceed with default guessing steps
            models::creature cur_creature;
            if (model->get_default_by_type(type, cur_creature))
            {
                iss.clear();
                iss.str("");

                iss << "Is the " << model->get_kingdom() << " you thought about a " << cur_creature.get_name() << "? (Y/N) ";
                yes_chosen = ask_yes_no(iss.str(), answer);

                if (yes_chosen)
                {
                    // display "I'm a winner"
                    im_a_winner();
                    success = true;
                }
                else
                {
                    ask_for_creature(type, cur_creature);
                }
            }
            else
            {
                // highly unlikely, but who know
            }
        }

        return success;
    }

    bool ui_handler::ask_yes_no(const std::string& prompt, std::string& answer)
    {
        bool yes_chosen = false;
        char chosen = 0x00;

        akinator::app::console_ui* ui = akinator::app::console_ui::instance();

        for ( ; chosen == 0x00; )
        {
            ui->do_display(prompt);
            ui->get_answer(answer);

            chosen = answer[0];

            switch (chosen)
            {
                case 'y':
                case 'Y':
                {
                    answer.assign(1, std::toupper(chosen));
                    yes_chosen = true;
                    break;
                }
                case 'n':
                case 'N':
                {
                    answer.assign(1, std::toupper(chosen));
                    yes_chosen = false;
                    break;
                }            

                default:
                {
                    ui->do_display("\nInvalid choice\n");
                    chosen = 0x00;
                }
            }

        }

        return yes_chosen;
    }

    void ui_handler::ask_for_creature(models::creature_type_t type, const models::creature& compared)
    {
        std::string prompt;
        std::string name, ability;

        models::animal_model *model = models::animal_model::instance();
        akinator::app::console_ui* ui = akinator::app::console_ui::instance();

        name.clear();
        for (; name.empty(); )
        {
            prompt = "What was the " + model->get_kingdom() + " you thought about? ";
            ui->do_display(prompt);
            ui->get_line(name);
        }

        prompt = "What does a " + name + " do, that a " + compared.get_name() + " does not? ";
        ability.clear();
        for (; ability.empty(); )
        {
            ui->do_display(prompt);
            ui->get_line(ability);
        }

        // Ok, now we have the creature name and its ability.
        // Add the new creature to the model collection
        models::creature new_creature;
        new_creature.set_name(name);
        new_creature.set_ability(ability);
        new_creature.set_type(type);
        new_creature.set_is_default(false);

        model->add(new_creature);
    }

    void ui_handler::im_a_winner()
    {
        akinator::app::console_ui* ui = akinator::app::console_ui::instance();

        ui->do_display("\n\nI win!!!\n");
    }

    /* Properties */
    void ui_handler::set_humor_me(bool doit)
    {
        this->m_humor_me = doit;
    }
}
}