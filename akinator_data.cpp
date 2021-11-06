#include "akinator_data.hpp"

namespace akinator
{
namespace creatures
{
    /* Class creature */
    creature::creature() : m_kingdom("animal")
    {        
    }

    creature::~creature()
    {
    }

    /* Singleton instance */
    creature *creature::instance()
    {
        static creature singleton;
        return &singleton;
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

    /* Setters */
    void creature::set_name(const std::string &value)
    {
        this->m_name = value;
    }

    void creature::set_ability(const std::string &value)
    {
        this->m_ability = value;
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

    const std::string &creature_model::get_filter() const
    {
        return m_filter;
    }


    /* Class animal_model */
    /* CTOR */
    animal_model::animal_model()
    {
        creature_model::m_kingdom = "animal";
        creature_model::m_filter = "live in water";
    }

    /* DTOR */
    animal_model::~animal_model()
    {        
    }

    /* Singleton instance */
    animal_model* animal_model::instance()
    {
        static animal_model singleton;
        return &singleton;
    }
}
} 