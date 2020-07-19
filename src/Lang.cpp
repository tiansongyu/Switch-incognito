#include <filesystem>
#include <fstream>
#include "json.hpp"
#include "Lang.hpp"
#include <sstream>

namespace Lang
{

    nlohmann::json j = nullptr;
    bool setFile(std::string path)
    {
        if (!std::filesystem::exists(path))
        {
            return false;
        }
        std::ifstream in(path);
        j = nlohmann::json::parse(in);
        return true;
    }
    bool setLanguage(Language l)
    {
        std::string path = "";
        switch (l)
        {
        case English:
            path = "romfs:/lang/en.json";
            break;
        case Chinese:
            path = "romfs:/lang/ch.json";
            break;
        default:
            break;
        }
        return setFile(path);
    }
    std::string string(std::string key)
    {
        // First 'navigate' to nested object
        nlohmann::json t = j;
        std::istringstream ss(key);
        std::string k;
        while (std::getline(ss, k, '.') && t != nullptr)
        {
            t = t[k];
        }

        // If the string is not present return key
        if (t == nullptr || !t.is_string())
        {
            return std::string("fail");
        }

        return t.get<std::string>();
    }
    const char *stringtochar(std::string str)
    {
        return str.c_str();
    }
} // namespace Lang