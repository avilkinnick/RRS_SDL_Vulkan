#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <pugixml.hpp>

#include <sstream>
#include <string_view>

class ConfigFile
{
public:
    explicit ConfigFile(std::string_view path);

    void set_current_section(const char* section_name);

    template <typename T>
    T read(const char* property_name);

private:
    const char* get_value_string(const char* property_name);

private:
    std::string_view path;
    pugi::xml_node main_section;
    pugi::xml_node current_section;
};

template <typename T>
T ConfigFile::read(const char* property_name)
{
    std::stringstream ss;
    ss << get_value_string(property_name);

    T value;
    ss >> value;

    return value;
}

template <>
inline const char* ConfigFile::read<const char*>(const char* property_name)
{
    return get_value_string(property_name);
}

template <>
inline std::string_view ConfigFile::read<std::string_view>(const char* property_name)
{
    return get_value_string(property_name);
}

#endif // CONFIG_FILE_H
