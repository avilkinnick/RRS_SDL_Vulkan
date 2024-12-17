#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <pugixml.hpp>

class ConfigFile
{
public:
    explicit ConfigFile(const char* path);

    void set_current_section(const char* section_name);

    int read_int(const char* property_name);
    float read_float(const char* property_name);
    double read_double(const char* property_name);

private:
    pugi::xml_node main_section;
    pugi::xml_node current_section;
};

#endif // CONFIG_FILE_H
