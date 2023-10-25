#ifndef HTTP_CLIENT_HPP_
#define HTTP_CLINET_HPP_

#include<string>
#include <memory>

#include "TCPClient.hpp"

class HttpClient
{
private:
    std::shared_ptr<TCPClient> m_pTCPClient;
public:

    HttpClient();
    ~HttpClient();

    int connectServerByIPAddress(const std::string str_IPAddress,const int n_port);
    int connectServerByHostName(const std::string str_hostname,const int n_port);

    int sendHTTPGETRequest(const std::string str_request_parms, const std::string str_URL);

private:
    std::string getGETRequestBody(const std::string str_request_parms, const std::string str_URL);
    void writeFile(const std::string str_filename, const std::string& content);
};

#endif