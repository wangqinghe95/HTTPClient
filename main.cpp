#include "HttpClient.hpp"

const std::string HOSTNAME = "www.bing.com";
const int SERVER_PORT = 80;

int main()
{
    HttpClient CHttpClinet;

    CHttpClinet.connectServerByHostName(HOSTNAME, SERVER_PORT);
    CHttpClinet.sendHTTPGETRequest("/", HOSTNAME);

    return 0;
}