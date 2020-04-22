//
// Created by weixu on 4/21/20.
//

#include "HttpClient.h"
#include "common/mongoose.h"

namespace WX_HTTP{
    static int s_exit_flag = 0;
    static std::string message;
    void Http_Require::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
    {
        http_message *hm = (struct http_message *)event_data;
        int connect_status;

        switch (event_type)
        {
            case MG_EV_CONNECT:
                connect_status = *(int *)event_data;
                if (connect_status != 0)
                {
                    printf("Error connecting to server, error code: %d\n", connect_status);
                    s_exit_flag = 1;
                }
                break;
            case MG_EV_HTTP_REPLY:
            {
                printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
                std::string rsp = std::string(hm->body.p, hm->body.len);
                connection->flags |= MG_F_SEND_AND_CLOSE;
                s_exit_flag = 1; // 每次收到请求后关闭本次连接，重置标记

                // 回调处理
                message = rsp;
            }
                break;
            case MG_EV_CLOSE:
                if (s_exit_flag == 0)
                {
                    connection->flags |= MG_F_SEND_AND_CLOSE;
                    printf("Server closed connection\n");
                    s_exit_flag = 1;
                };
                break;
            default:
                break;
        }
    }

    std::string Http_Require::require(HttpInfo info){
        message = "";
        // 给回调函数赋值
        mg_mgr mgr;
        mg_mgr_init(&mgr, NULL);
        std::string url = info.server+ ":" + std::to_string(info.port)+ info.path;
        std::string extra_headers;
        for (auto &i : info.header) {
            extra_headers +=i.first + ":" + i.second + "\r\n";
        }

        std::string post_data = info.content.empty() ? "{}" : info.content;

        if (info.method == HTTP_Method::HTTP_METHOD_POST) {
            auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(),extra_headers.c_str(), post_data.c_str());
            mg_set_protocol_http_websocket(connection);
        } else if(info.method == HTTP_Method::HTTP_METHOD_GET) {
            auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(),NULL, NULL);
            mg_set_protocol_http_websocket(connection);
        }

        // loop
        while (s_exit_flag == 0)
            mg_mgr_poll(&mgr, 500);

        mg_mgr_free(&mgr);
        std::string result = message;
        s_exit_flag = 0;
        return "result";

    }
}