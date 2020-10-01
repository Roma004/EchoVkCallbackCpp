#ifndef VK_API
#define VK_API

#include <string>
#include <nlohmann/json.hpp>

#include "../utils/make_request.hpp"
using json = nlohmann::json;

namespace vk {
    class callback {
    private:
        std::string access_token;

    public:
        callback(): access_token("") {}

        callback(std::string token) {
            this->access_token = token;
        }

        json call_method(std::string method, json params = json()) {

            params["access_token"] = this->access_token;
            params["v"] = "5.103";

            std::cout << "call_method()\n";

            return get_request(
                "https://api.vk.com/method/" + method,
                params
            );
        }

        void set_access_token(std::string new_token) {
            this->access_token = new_token;
        }

    };
}

#endif