# c++VkCallback

# About Project

It's a work piece of VK callback server. It's also an echo server in that configuration, but it's possible to use it as a future project base.

# Configuring:

Firstly, you ougth to create a file named `config.hpp`, that conteins:
```c++
#include <nlohmann/json.hpp>
#include "vk_modules/vk_api.hpp"

using json = nlohmann::json;

namespace cfg {

    const extern json config = {
        { "vk_secret", "vk_group_secret" },
        { "vk_confirmation", "callback_confirmation_code" },
        { "vk_group_token", "your_vk_group_token" }
    };

}

static vk::callback vk_session = vk::callback(); // main vk_api session
```

__**all your settings should be stored here to prevent viriable conflict**__

Then you ought to install all dependences from next paragraph.
After that you are able to start your server:

For UNIX users:
```bash
$ ./make.sh     // to make and run your project
$ ./main        // (only after compiling) to run the project
```

For Windows Users:
```cmd
g++ main.cpp -o main.exe -std=c++17 -lasyncd -levent -lssl -lqlibc -levent_openssl -lcurl       // to compile the project
.\main.exe     // to run the project
```


# Dependences

### C++ libs
- [**libasyncd**](https://github.com/wolkykim/libasyncd/) - A realy great libriary, that allows HTTP(s) serving in C/C++
- [**nlohmann/json**](https://github.com/nlohmann/json/) - Best JSON libriary for modern C++, IMHO
- [**CURLpp**](https://github.com/jpbarrette/curlpp) - C/C++ wrapper over libcurl, great libriary, easy to make HTTP(s) request

### You need also
- [**libcurl**](https://curl.haxx.se/libcurl/) - Legendary console utility for working with http(s) requests
- [**openssl**](https://github.com/openssl/openssl) - OpenSource SSL libriary (it's possible to install another one)
- [**libevent**](https://github.com/libevent/libevent) - EventLoop libriary for C/C++ (the dependency of libasyncd)
