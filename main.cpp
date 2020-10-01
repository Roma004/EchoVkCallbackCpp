#include <iostream>
#include <string>

#include <asyncd/asyncd.h>

#include "view.cpp"
#include "vk_modules/vk_api.hpp"


int get_handler(short event, ad_conn_t *conn, void *userdata) {
    if (event & AD_EVENT_READ) {
        if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {

            ad_http_t *http = (ad_http_t *) ad_conn_get_extra(conn);
            printf("METHOD: %s  PATH: %s\n", http->request.method, http->request.path);

            ad_http_response(conn, 200, "text/html", "{\"status\": \"ok\"}", 16);
            return ad_http_is_keepalive_request(conn) ? AD_DONE : AD_CLOSE;
        }
    }
    return AD_OK;
}

int post_handler(short event, ad_conn_t *conn, void *userdata) {
    
    if (event & AD_EVENT_READ) {
        if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {


            ad_http_t *http = (ad_http_t *) ad_conn_get_extra(conn);
            std::string path = http->request.path;

            printf("METHOD: %s  PATH: %s\n", http->request.method, path.c_str());
            std::string post = (char *)ad_http_get_content(conn, http->request.contentlength, 0);

            json data;
            try {
                data = json::parse(post);
            } catch (json::parse_error) {
                ad_http_response(conn, 200, "text/html", "Could not read JSON data", 24);
            }

            if (path == "/vk") {
                vk_handler(conn, http, data);
            } else {
                ad_http_response(conn, 200, "text/html", "Not implemented", 15);
            }

            return ad_http_is_keepalive_request(conn) ? AD_DONE : AD_CLOSE;
        }
    }

    return AD_OK;
}

int my_http_default_handler(short event, ad_conn_t *conn, void *userdata) {
    if (event & AD_EVENT_READ) {
        if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {
            ad_http_response(conn, 501, "text/html", "Not implemented", 15);
            return AD_CLOSE;
        }
    }
    return AD_OK;
}

int main(int argc, char **argv) {

    ad_server_t *server = ad_server_new();
    ad_server_set_option(server, "server.port", "8889");
    ad_server_register_hook(server, ad_http_handler, NULL);

    ad_server_register_hook_on_method(server, "GET", get_handler, NULL);
    ad_server_register_hook_on_method(server, "POST", post_handler, NULL);
    ad_server_register_hook(server, my_http_default_handler, NULL);

    std::cout << "Sever started" << "\n";
    vk_session.set_access_token(cfg::config["vk_group_token"]);

    return ad_server_start(server);
}

// export LD_LIBRARY_PATH=/usr/local/lib