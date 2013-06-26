#include <cstdlib>
#include <cstring>
#include "settings.h"

namespace HVMixer
{

Settings::Settings(std::string filename)
{
    std::string fname;
    
    if (filename == "")
        fname = std::string(getenv("HOME")) + "./hvmixerrc";
    else
        fname = filename;
    
    file.open(fname.c_str());
    if (file)
        openned = true;
    else
        openned = false;
}

Settings::~Settings()
{
}

std::string Settings::getValue(std::string key)
{
    if (!openned)
        return "";
        
    int nlines = 1;
    std::string * lines = new std::string[nlines];
    
    for (int i = 0; file.eof(); i++) {
        std::string temp;
        std::string * newl;
        getline(file, temp);
        newl = new std::string[nlines];
        memcpy(newl, lines, nlines - 1 * sizeof(std::string));
        delete [] lines;
        lines = (std::string *) memcpy(newl, &temp, sizeof(std::string));
    }
    
    std::cout << "lines have: " << lines;
}

} // HVMixer namespace

