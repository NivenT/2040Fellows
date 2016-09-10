#include <cpr/cpr.h>
#include <json.hpp>

using json = nlohmann::json;

int main(int argc, char** argv) {
	json request;
	request["github"] = "https://github.com/NivenT/2040Fellows";
	request["token"] = "dfbacfcbb73aa62b337f3f0daa90f522";

    std::cout<<"request: "<<request.dump(4)<<std::endl
    		 <<std::endl;

    auto response = cpr::Post(cpr::Url{"http://challenge.code2040.org/api/register"},
    						  cpr::Body{request.dump()},
    						  cpr::Header{{"Content-Type", "application/json"}});

    std::cout<<"response status: "<<response.status_code<<std::endl
    		 <<"response body: "<<response.text<<std::endl
    		 <<std::endl;

    return 0;
}