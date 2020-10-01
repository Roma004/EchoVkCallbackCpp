#ifndef URL_ENCODE
#define URL_ENCODE

#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


std::string encode(std::string value) 
{
    using namespace std;

    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) 
    {
        string::value_type c = (*i);

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }
        else if (c == ' ') {
            escaped << "+";
            continue;
        }

        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

std::string json_encode(json url_map) {
    std::ostringstream res;
    res << "?";

    std::cout << url_map["message"].get<std::string>() << "\n";

    int i = 0;

    for (auto & [key, value] : url_map.items()) {
        res << encode(key) << "=";

        if (value.is_string()) {
            res << encode(value.get<std::string>());
        } else if (value.is_number()) {
            res << value.get<int>();
        } else if (value.is_boolean()) {
            res << value.get<bool>();
        } else {
            std::cout << "\n\nNot a valid type!\n\n";
        }

        if (i != url_map.size() - 1) {
            res << "&";
        }
        ++i;
    }

    return res.str();
}

#endif