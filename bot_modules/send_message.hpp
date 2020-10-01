#include "../config.hpp"

void send_message(
        int peer_id, 
        std::string message = "",
        std::string attachment = "",
        std::string user_ids = "",
        std::string user_id = "",
        std::string forward_messages = "",
        std::string sticker_id = "",
        std::string keyboard = "",
        std::string peer_ids = "",
        std::string disable_mentions = ""
    ) {

    json to_send = {
        {"peer_id", peer_id},
        {"message", message},
        // {"keyboard", keyboard},
        {"random_id", 0}
    };

    json result = vk_session.call_method("messages.send", to_send); 

    if (result.find("error") != result.end()) {
        std::cout << result << "\n";
    }
}