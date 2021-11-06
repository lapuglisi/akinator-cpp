#include "akinator_data.hpp"

namespace akinator
{
namespace creatures
{
    /* Class creature */
    creature::creature() : m_is_default(false)
    {        
    }

    creature::~creature()
    {
    }

    /* Getters */
    const std::string &creature::get_name() const
    {
        return this->m_name;
    }

    const std::string &creature::get_ability() const
    {
        return this->m_ability;
    }

    const std::string &creature::get_kingdom() const
    {
        return this->m_kingdom;
    }

    unsigned int creature::get_type() const
    {
        return this->m_type;
    }

    bool creature::get_is_default() const
    {
        return this->m_is_default;
    }

    /* Setters */
    void creature::set_name(const std::string &value)
    {
        this->m_name = value;
    }

    void creature::set_ability(const std::string &value)
    {
        this->m_ability = value;
    }

    void creature::set_type(unsigned int value)
    {
        this->m_type = value;
    }

    void creature::set_is_default(bool value)
    {
        this->m_is_default = value;
    }

    void creature::copy_from(const creature& source)
    {
        this->set_name(source.get_name());
        this->set_ability(source.get_ability());
        this->set_type(source.get_type());
        this->set_is_default(source.get_is_default());
    }

    /* Class creature_model */
    creature_model* creature_model::instance()
    {
        static creature_model singleton;
        return &singleton;
    }

    const std::string &creature_model::get_kingdom() const
    {
        return m_kingdom;
    }


    /* Class animal_model */
    /* CTOR */
    animal_model::animal_model()
    {
        creature_model::m_kingdom = "animal";

        init();
    }

    /* DTOR */
    animal_model::~animal_model()
    {
    }

    /* Private stuff */
    void animal_model::init()
    {
        // Initialize animal types so that the ViewModel may use it
        m_animal_types[creature_type_t::lives_in_water] = "live in water";

        // Initialize default collection
        creature new_creature;

        // Monkey - does not live in water
        new_creature.set_name("monkey");
        new_creature.set_ability("eat bananas");
        new_creature.set_type(creature_type_t::everything_else);
        new_creature.set_is_default(true);

        m_defaults.push_back(new_creature);

        // shark - lives in water
        new_creature.set_name("shark");
        new_creature.set_ability("kills people");
        new_creature.set_type(creature_type_t::lives_in_water);
        new_creature.set_is_default(true);

        m_defaults.push_back(new_creature);
    }

    /* Singleton instance */
    animal_model* animal_model::instance()
    {
        static animal_model singleton;
        return &singleton;
    }

    /* Public Stuff */
    const creature_types_t& animal_model::get_types() const
    {
        return m_animal_types;
    }

    creature_collection_t& animal_model::filter_by_type(creature_collection_t &creatures, unsigned int type)
    {
        creatures.clear();
        creature_collection_t::iterator it;

        for (it = m_collection.begin(); it != m_collection.end(); it++)
        {
            if (it->get_type() == type)
            {
                creatures.push_back(*it);
            }
        }

        return creatures;
    }

    bool animal_model::get_default_by_type(creature_type_t type, creature& target) const
    {
        bool found = false;
        creature_collection_t::const_iterator it;

        for (it = m_defaults.begin(); it != m_defaults.end(); it++)
        {
            if (it->get_type() == type)
            {
                target.copy_from(*it);
                found = true;
                break;
            }
        }

        return found;
    }

    void animal_model::add(creature &source)
    {
        m_collection.push_back(source);
    }
}
} 