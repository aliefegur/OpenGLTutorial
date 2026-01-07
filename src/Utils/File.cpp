#include "File.h"
#include <fstream>
#include <sstream>

std::string File::Read(const std::string& filename)
{
    std::ifstream ifs(filename);
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    return ss.str();
}
