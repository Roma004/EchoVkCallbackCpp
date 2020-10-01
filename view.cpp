#include "bot_modules/message_handler.hpp"

#ifndef VIEW_CPP
#define VIEW_CPP

#include <asyncd/asyncd.h>
#include <string>
#include <iostream>


void write_message(ad_conn_t *conn, std::string text) {
    ad_http_response(conn, 200, "text/html", text.c_str(), text.size());
}

void write_json(ad_conn_t *conn, json data) {
    std::string dumped_json = data.dump();
    ad_http_response(conn, 200, "application/json", dumped_json.c_str(), dumped_json.size());
}

// /vk path router
void vk_handler(
        ad_conn_t *conn, ad_http_t *http,
        json data
    ) {

    if (data.find("type") == data.end()) {
        write_message(conn, "not_vk");
    }

    if (data.find("secret") != data.end() && data["secret"] == cfg::config["vk_secret"]) {
        if (data["type"] == "confirmation") {
            write_message(conn, cfg::config["vk_confirmation"]);
        } else if (data["type"] == "message_new") {
            std::cout << data.dump() << "\n";
            process_message(data);

            write_message(conn, "ok");
        } else {
            write_message(conn, "ok");
        }
    }

    write_message(conn, "ok");
}

#endif