#include <string>
#include <iostream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#ifdef _WIN32
const char* clear { "cls" };
#include <Windows.h> // sleep(seconds)
#else
const char* clear { "clear" };
#include <unistd.h> // sleep(seconds)
#endif

using json = nlohmann::json;

const std::string URL{"https://ticker-api.cointelegraph.com/rates/"};


void prices() {
    cpr::Response r = cpr::Get(cpr::Url{URL});
    json ret = json::parse(r.text);

    for (const auto &val : ret["data"].items()) {

        /* change to float for better looking + comapring */
        const float change{ val.value()["USD"][1].get<float>()} ;
        const float price{ val.value()["USD"][0].get<float>() };

        std::cout << '[' << val.key() << "] " << '$' << price;

        if (change > 0) {
            std::cout << " \u001b[32m(" << change << ")\u001b[0m\n";
        } else {
            std::cout << " \u001b[31m(" << change << ")\u001b[0m\n";
        }
    }
}


int main() {
    while (true) {
        prices();
        sleep(10); /* 10 second sleep */
        system(clear);
    }
}
