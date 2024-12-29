#include "ConfigFile.h"

#include <pugixml.hpp>

#include <stdexcept>
#include <string>
#include <string_view>

ConfigFile::ConfigFile(std::string_view path)
    : path(path)
{
    pugi::xml_parse_result result = document.load_file(path.data());
    if (!result)
    {
        throw std::runtime_error(std::string("Failed to load \"") + path.data() + '\"');
    }

    main_section = document.child("Config");
    if (!main_section)
    {
        throw std::runtime_error(std::string("Failed to find \"Config\" section in \"") + path.data() + '\"');
    }
}

void ConfigFile::set_current_section(const char* section_name)
{
    current_section = main_section.child(section_name);
    if (!current_section)
    {
        throw std::runtime_error(
            std::string("Failed to find \"") + section_name + "\" section in \"" + path + '\"'
        );
    }
}

const char* ConfigFile::get_value_string(const char* property_name) const
{
    const char* value_string = current_section.child_value(property_name);
    if (value_string[0] == '\0')
    {
        throw std::runtime_error(
            std::string("Section \"")
            + current_section.name()
            + "\" in \""
            + path
            + "\" does not contain property \""
            + property_name
            + "\" or it is empty"
        );
    }

    return value_string;
}
