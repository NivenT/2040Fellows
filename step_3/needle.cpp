#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

size_t find_needle(const std::string& needle, const std::vector<std::string>& haystack) {
    return std::find(haystack.begin(), haystack.end(), needle) - haystack.begin();
}

int main(int argc, char** argv) {
	json request;
	request["token"] = "dfbacfcbb73aa62b337f3f0daa90f522";

    std::cout<<"request: "<<request.dump(4)<<std::endl
    		 <<std::endl;

    auto response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/haystack"},
    						  cpr::Body{request.dump()},
    						  cpr::Header{{"Content-Type", "application/json"}});

    if (response.status_code/100 == 2) {
        auto dictionary = json::parse(response.text);
        auto position = find_needle(dictionary["needle"], dictionary["haystack"]);

        std::cout<<"needle: "<<dictionary["needle"]<<std::endl
                 <<"haystack: "<<dictionary["haystack"]<<std::endl
                 <<"position of needle in haystack: "<<position<<std::endl
                 <<std::endl;

        request["needle"] = position;
        std::cout<<"second request: "<<request.dump(4)<<std::endl
                 <<std::endl;

        response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/haystack/validate"},
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