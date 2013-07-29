#include <cstdlib>
#include <cstring>
#include <wordexp.h>
#include "settings.h"

namespace HVMixer
{

Settings::Settings()
{
    default_options["mixer_element_1"] = "Master";
    default_options["mixer_element_2"] = "Master Surround";

    desc.add_options()
        ("mixer_element_1", po::value<std::string>(), "Name of mixer element #1")
        ("mixer_element_2", po::value<std::string>(), "Name of mixer element #2")
    ;

    try {
        po::store(po::parse_config_file<char>(get_cfg_file_name(), desc), vm);
        po::notify(vm);
    } catch (std::exception &e) {
        std::cout << "Something wrong with configuration file:\n"
            << e.what() << std::endl;
    }
}

Settings::~Settings()
{
    std::ofstream ocfg(get_cfg_file_name());

    if (!ocfg)
        std::cout << "cannot open configuration file to write" << std::endl;
        return;

    boost::property_tree::ptree root;

    for (std::map<std::string,std::string>::iterator it = options.begin();
        it != options.end(); ++it)
    {
        root.put(it->first, it->second);
    }

    boost::property_tree::ini_parser::write_ini(ocfg, root);
}

const char *
Settings::get_cfg_file_name()
{
    std::string fname = DEFAULT_CONFIG_FILE;

    if (fname.find('~') != std::string::npos) {
        wordexp_t exp;

        wordexp(fname.c_str(), &exp, 0);
        fname = exp.we_wordv[0];
    }
    return fname.c_str();
}

std::string Settings::getValue(std::string key)
{
    if (vm.count(key)) return vm[key].as<std::string>();
    else {
        if (default_options.count(key)) return default_options[key];
        else return "";
    }
}

bool
Settings::setValue(std::string key, std::string value)
{
    if (default_options.count(key)) {
        options[key] = value;
        return true;
    } else return false;
}

} // HVMixer namespace

