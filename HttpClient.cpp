#include "HttpClient.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>

const char STRING_HTTP_GET[64] = "GET";
const char STRING_HTTP_VERSION[16] = "HTTP/1.1";
const char STRING_HTTP_HOST[16] = "Host";
const char STRING_NEWLINE_CHARACTER[16] = "\r\n";
const char CHAR_SPACE[8] = " ";
const char CHAR_COLON[8] = ":";
const char FILENAME_GET_REQUEST[32] = "GETREQUEST.txt";


HttpClient::HttpClient() : m_pTCPClient(std::make_shared<TCPClient>())
{

}
HttpClient::~HttpClient()
{

}

int HttpClient::connectServerByIPAddress(const std::string str_IPAddress,const int n_port)
{
    m_pTCPClient->connectServer(str_IPAddress, n_port);
}
int HttpClient::connectServerByHostName(const std::string str_hostname,const int n_port)
{
    std::string str_IPAddress = m_pTCPClient->getIPAddressFromHostname(str_hostname);
    m_pTCPClient->connectServer(str_IPAddress, n_port);
}

std::string HttpClient::getGETRequestBody(const std::string str_request_parms, const std::string str_URL)
{
    // "GET / HTTP/1.1\r\nHost: www.bing.com\r\n\r\n"

    std::string str_request_HTTP_GET_message;
    str_request_HTTP_GET_message += STRING_HTTP_GET;
    str_request_HTTP_GET_message += CHAR_SPACE;

    str_request_HTTP_GET_message += str_request_parms;
    str_request_HTTP_GET_message += CHAR_SPACE;
    
    str_request_HTTP_GET_message += STRING_HTTP_VERSION;
    str_request_HTTP_GET_message += CHAR_SPACE;

    str_request_HTTP_GET_message += STRING_NEWLINE_CHARACTER;

    str_request_HTTP_GET_message += STRING_HTTP_HOST;
    str_request_HTTP_GET_message += CHAR_COLON;
    str_request_HTTP_GET_message += CHAR_SPACE;
    str_request_HTTP_GET_message += str_URL;

    str_request_HTTP_GET_message += STRING_NEWLINE_CHARACTER;
    str_request_HTTP_GET_message += STRING_NEWLINE_CHARACTER;

    return str_request_HTTP_GET_message;
}


int HttpClient::sendHTTPGETRequest(const std::string str_request_parms, const std::string str_URL)
{
    std::string send_message = getGETRequestBody(str_request_parms, str_URL);

    std::string recv_message;

    m_pTCPClient->sendAndRecvMessage(send_message, recv_message);

    writeFile(FILENAME_GET_REQUEST, recv_message);

    return 0;
}

void HttpClient::writeFile(const std::string str_filename, const std::string& content)
{
    std::ofstream outfile(str_filename);
    // outfile << content;
    std::cout << content << std::endl;
    
    outfile.close();
}