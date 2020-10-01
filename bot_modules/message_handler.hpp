#ifndef MESSAGE_HANDLER
#define MESSAGE_HANDLER

#include <iostream>
#include "send_message.hpp"

void process_message(json data) {
    std::cout << "New message request\n";

    std::string text = data["object"]["message"]["text"].get<std::string>();
	int peer_id = data["object"]["message"]["peer_id"].get<int>();

    send_message(
        peer_id,
        text    
    );
}

#endif