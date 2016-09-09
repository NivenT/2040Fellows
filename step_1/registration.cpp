#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>

int main(int argc, char** argv) {
    auto r = cpr::Get(cpr::Url("http://httpbin.org/get"));
    auto json = nlohmann::json::parse(r.text);

    std::cout<<r.url<<std::endl; 
	std::cout<<r.status_code<<std::endl;
	std::cout<<r.header["content-type"]<<std::endl;
	std::cout<<r.text<<std::endl;

	std::cout<<json["headers"]<<std::endl;
}