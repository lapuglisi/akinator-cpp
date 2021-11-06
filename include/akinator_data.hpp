#ifndef __akinator_data_hpp__
#define __akinator_data_hpp__

#include <cstdlib>
#include <string>
#include <map>

namespace akinator
{
namespace creatures
{
    class creature
    {
    public:
        creature();
        ~creature();

        const std::string &get_name() const;
        const std::string &get_ability() const;
        const std::string &get_kingdom() const;

        void set_name(const std::string& /*name*/);
        void set_ability(const std::string& /*ability*/);

        static creature* instance();
    protected:

    private:  
        std::string m_name;
        std::string m_ability;
        std::string m_kingdom;      
    };

    class creature_model
    {
    public:
        creature_model() = default;
        virtual ~creature_model() = default;

        virtual const std::string& get_kingdom() const;
        virtual const std::string& get_filter() const;

        static creature_model* instance();

    protected:
        std::string m_kingdom;
        std::string m_filter;

    private:
    };

    class animal_model : public creature_model
    {
    private:
        std::map<std::string, creature> m_collection;

    protected:

    public:
        animal_model();
        ~animal_model();

        void add(const std::string& /*name*/, creature& /*entity*/);

        const creature &get_creature(const std::string& /*name*/) const;
        void set_creature(const std::string& /* name */, const creature& /*entity*/);

        static animal_model* instance();
    };
}
}

#endif // __akinator_data_hpp__