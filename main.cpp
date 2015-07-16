#include "btc_api.hpp"
#include <unistd.h>

int main(int argc, char **argv) {
    btc_api api("your_key", "your_secret");
    json_data response = api.getInfo();
    std::cout << response<< "\n\n";
    
    // now you can parse json data
    response = api.tradeHistory();
    std::cout << response<< "\n\n";
    
    return 0;
}