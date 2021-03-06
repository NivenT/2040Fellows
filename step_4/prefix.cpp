#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

void filter_prefix(const std::string& prefix, std::vector<std::string>& array) {
    auto end = std::remove_if(array.begin(), array.end(), [&](const std::string& str) {
        return str.find(prefix) == 0;
    });
    //remove_if returns new end of range, so array size needs to be adjusted
    array.resize(end - array.begin());
}

int main(int argc, char** argv) {
    json request;
    request["token"] = "dfbacfcbb73aa62b337f3f0daa90f522";

    std::cout<<"request: "<<request.dump(4)<<std::endl
             <<std::endl;

    auto response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/prefix"},
                              cpr::Header{{"Content-Type", "application/json"}},
                              cpr::Body{request.dump()});

    if (response.status_code/100 == 2) {
        auto dictionary = json::parse(response.text);
        std::vector<std::string> filtered = dictionary["array"];
        filter_prefix(dictionary["prefix"], filtered);

        std::cout<<"prefix: "<<dictionary["prefix"]<<std::endl
                 <<"array: "<<dictionary["array"]<<std::endl
                 <<"filtered array: "<<json(filtered)<<std::endl
                 <<std::endl;

        request["array"] = filtered;
        std::cout<<"second request: "<<request.dump(4)<<std::endl
                 <<std::endl;
        
        response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/prefix/validate"},
                             cpr::Header{{"Content-Type", "application/json"}},
                             cpr::Body{request.dump()});

        std::cout<<"response status: "<<response.status_code<<std::endl
                 <<"response body: "<<response.text<<std::endl
                 <<std::endl;
    } else {
        std::cout<<"Error: request did not go through (code "<<response.status_code<<")"<<std::endl;
        return 1;
    }

    return 0;
}