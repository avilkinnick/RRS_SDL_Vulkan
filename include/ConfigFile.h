#pragma once

#include <pugixml.hpp>

#include <sstream>
#include <string>
#include <string_view>

class ConfigFile
{
public:
    explicit ConfigFile(std::string_view path);
    ConfigFile(const ConfigFile&) = delete;
    ConfigFile& operator=(const ConfigFile&) = delete;

    void set_current_section(const char* section_name);

    template <typename T>
    T read(const char* property_name) const;

    template <typename F>
    void for_each(const char* property_name, F function);

private:
    const char* get_value_string(const char* property_name) const;

private:
    std::string path;
    pugi::xml_document document;
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

template <typename F>
void ConfigFile::for_each(const char* property_name, F function)
{
    for (pugi::xml_node property : main_section.children(property_name))
    {
        current_section = property;
        function();
    }
}

