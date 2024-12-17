#include "ConfigFile.h"

#include "pugixml.hpp"

#include <stdexcept>
#include <string>

ConfigFile::ConfigFile(const char* path)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(path);
    if (!result)
    {
        throw std::runtime_error(std::string("Failed to load \"") + path + '\"');
    }

    main_section = doc.child("Config");
    if (!main_section)
    {
        throw std::runtime_error(std::string("Failed to find \"Config\" section in \"") + path + '\"');
    }
}

void ConfigFile::set_current_section(const char* section_name)
{

}
