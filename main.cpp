//
// Created by weixu on 4/21/20.
//
#include <iostream>
#include "HttpClient.h"

int main(){
    WX_HTTP::HttpInfo info;
    info.server = "192.168.0.0";
    info.port = 9090;
    info.path = "/api/ice/info";
    info.content = "{}";

    std::map<std::string, std::string>header;
    header.insert(std::pair<std::string, std::string>("content-type","application/json"));
    info.method = WX_HTTP::HTTP_Method::HTTP_METHOD_POST;
    WX_HTTP::Http_Require httpRequire;
    std::string result = httpRequire.Http_Require::require(info);
    std::cout << "-----------result: " << result << std::endl;
	system("pause");
    return 0;
}