#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

std::tm get_time(const std::string& time_str, const char* format) {
    std::tm time;
    std::stringstream time_stream(time_str);
    time_stream>>std::get_time(&time, format);
    return time;
}

std::tm advance_time(std::tm now, long duration) {
    time_t then = mktime(&now) + duration;
    return *localtime(&then);
}

int main(int argc, char** argv) {
    json request;
    request["token"] = "dfbacfcbb73aa62b337f3f0daa90f522";

    std::cout<<"request: "<<request.dump(4)<<std::endl
             <<std::endl;

    auto response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/dating"},
                              cpr::Body{request.dump()},
                              cpr::Header{{"Content-Type", "application/json"}});

    if (response.status_code/100 == 2) {
        const char* format = "%Y-%m-%dT%H:%M:%SZ";
        auto dictionary = json::parse(response.text);
        auto time = advance_time(get_time(dictionary["datestamp"], format), dictionary["interval"]);

        std::cout<<"datestamp: "<<dictionary["datestamp"]<<std::endl
                 <<"interval: "<<dictionary["interval"]<<std::endl
                 <<"datestamp after interval seconds: "<<std::put_time(&time, format)<<std::endl
                 <<std::endl;

        char* time_buffer = new char[20];
        strftime(time_buffer, 20, format, &time);

        request["datestamp"] = time_buffer;
        std::cout<<"second request: "<<request.dump(4)<<std::endl
                 <<std::endl;

        response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/dating/validate"},
                             cpr::Body{request.dump()},
                             cpr::Header{{"Content-Type", "application/json"}});

        std::cout<<"response status: "<<response.status_code<<std::endl
                 <<"response body: "<<response.text<<std::endl
                 <<std::endl;
    } else {
        std::cout<<"Error: request did not go through (code "<<response.status_code<<")"<<std::endl;
        return 1;
    }

    return 0;
}