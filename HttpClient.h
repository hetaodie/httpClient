//
// Created by weixu on 4/21/20.
//

#ifndef HTTP_C_HTTPCLIENT_H
#define HTTP_C_HTTPCLIENT_H

#include <string>
#include <map>
#include "common/mongoose.h"

namespace WX_HTTP {
    typedef enum HTTP_Method {
        HTTP_METHOD_GET,
        HTTP_METHOD_POST,
    };
    typedef struct HttpInfo{
        std::string server;
        int port;
        HTTP_Method method;
        std::string path;
        std::string content;
        std::map<std::string,std::string>header;
    }HttpInfo;
    class Http_Require {
    public:
        Http_Require(){};
        ~Http_Require(){};
        std::string require(HttpInfo info);
        static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
    };
}

#endif //HTTP_C_HTTPCLIENT_H
