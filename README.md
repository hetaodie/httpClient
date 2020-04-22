# httpClient
- 对mongoose进行封装,完成http的请求,支持GET,POST模式

- 支持传入头信息

- 使用方法

- 使用cmake 直接进行编译,生成相应的静态库

  



```c++
int main(){
    WX_HTTP::HttpInfo info;
    info.server = "192.168.0.0";
    info.port = 8080;
    info.path = "/api/ice/ping";
    info.content = "{}";

    std::map<std::string, std::string>header;
    header.insert(std::pair<std::string, std::string>("content-type","application/json"));
    info.header = header;
    info.method = WX_HTTP::HTTP_Method::HTTP_METHOD_POST;

    WX_HTTP::Http_Require httpRequire;
    std::string result = httpRequire.Http_Require::require(info);
    std::cout << "-----------result: " << result << std::endl;
    return 0;
}    

```

