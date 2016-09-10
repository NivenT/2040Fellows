#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

std::string reverse_string(const std::string& orig) {
    return std::string(orig.rbegin(), orig.rend());
}

int main(int argc, char** argv) {
	json request;
	request["token"] = "dfbacfcbb73aa62b337f3f0daa90f522";
    std::cout<<"request: "<<request.dump(4)<<std::endl
    		 <<std::endl;

    auto response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/reverse"},
                              cpr::Body{request.dump()},
                              cpr::Header{{"Content-Type", "application/json"}});

    if (response.status_code/100 == 2) {
        auto reversed = reverse_string(response.text);
        std::cout<<"Received string \""<<response.text<<"\""<<std::endl
                 <<"The string reversed is \""<<reversed<<"\""<<std::endl
                 <<std::endl;

        request["string"] = reversed;
        std::cout<<"second request: "<<request.dump(4)<<std::endl
                 <<std::endl;

        response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/reverse/validate"},
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