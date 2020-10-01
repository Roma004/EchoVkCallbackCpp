#ifndef MAKE_REQUEST
#define MAKE_REQUEST

#include <map>
#include <string>
#include <curl/curl.h>
// #include <iostream>
#include "url_encode.hpp"
#include <nlohmann/json.hpp>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

using json = nlohmann::json;

json get_request(std::string url, json params) {
    CURL *curl;
    CURLcode res;

    std::string read_buffer = "";
    std::string encoded_params = json_encode(params);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_URL, (url + encoded_params).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {

            std::string error = curl_easy_strerror(res);

            return {
                {"error", "curl_easy_perform() failed: " + error + "\n"},
                {"error_code", 0}
            };
        }
    
        curl_easy_cleanup(curl);
    }

    if (read_buffer == "") {
        return {
            {"error", "null data returned"},
            {"code", 1}
        };
    }

    json result = json::parse(read_buffer);

    return result;
}

#endif