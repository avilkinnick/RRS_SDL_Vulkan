#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <pugixml.hpp>

#include <sstream>
#include <string>
#include <string_view>

class ConfigFile
{
public:
    explicit ConfigFile(std::string_view path);

    void set_current_section(const char* section_name);

    template <typename T>
    T read(const char* property_name) const;

private:
    const char* get_value_string(const char* property_name) const;

private:
    std::string path;
    pugi::xml_node main_section;
    pugi::xml_node current_section;
};

template <typename T>
T ConfigFile::read(const char* property_name) const
{
    std::stringstream ss;
    ss << get_value_string(property_name);

    T value;
    ss >> value;

    return value;
}

#endif // CONFIG_FILE_H
