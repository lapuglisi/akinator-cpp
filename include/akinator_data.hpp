#ifndef __akinator_data_hpp__
#define __akinator_data_hpp__

#include <cstdlib>
#include <string>
#include <vector>
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
        unsigned int get_type() const;
        bool get_is_default() const;

        void set_name(const std::string& /*name*/);
        void set_ability(const std::string& /*ability*/);
        void set_type(unsigned int /*type*/);
        void set_is_default(bool /*value*/);

        void copy_from(const creature& /*source*/);
    protected:

    private:  
        std::string m_name;
        std::string m_ability;
        std::string m_kingdom;
        unsigned int m_type;
        bool m_is_default;
    };

    class creature_model
    {
    public:
        creature_model() = default;
        virtual ~creature_model() = default;

        virtual const std::string& get_kingdom() const;

        static creature_model* instance();

    protected:
        std::string m_kingdom;

    private:
    };

    typedef std::map<unsigned int, std::string> creature_types_t;
    typedef std::vector<creature> creature_collection_t;

    class animal_model : public creature_model
    {
    private:
        creature_types_t m_animal_types;
        creature_collection_t m_collection;
        creature_collection_t m_defaults;

        void init();

    protected:

    public:
        animal_model();
        ~animal_model();

        const creature_types_t& get_types() const;

        void add(creature& /*entity*/);

        const creature &get_creature(const std::string& /*name*/) const;
        void set_creature(const std::string& /* name */, const creature& /*entity*/);

        creature_collection_t& filter_by_type(creature_collection_t& /*creatures*/, unsigned int /*type*/);

        bool get_default_by_type(unsigned int /*type*/, creature& /*target*/) const;

        static animal_model* instance();
    };
}
}

#endif // __akinator_data_hpp__