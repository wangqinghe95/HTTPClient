#include "HttpClient.hpp"
#include "Logger.hpp"
#include "JsonParser.hpp"
#include "FileOperation.hpp"

const std::string CONFIG_FILE = "config.json";

int main()
{
    // read config file
    FileOperation CFileOperation;
    string string_config_content;
    CFileOperation.readContentFromFile(string_config_content, CONFIG_FILE);

    // parase json string
    JsonValue root = JsonParser::toJsonValue(string_config_content);
    JsonObject result = root.toObject();
    JsonObject json_http_server = result["HttpServer"].toObject();

    string string_http_hostname = json_http_server["URL"].toString();
    int n_http_port = json_http_server["port"].toLongLong();

    HttpClient CHttpClient;

    CHttpClient.connectServerByHostName(string_http_hostname, n_http_port);
    CHttpClient.sendHTTPGETRequest("/", HOSTNAME);

    string string_http_ipaddress = CHttpClient.getIPAddress();

    DEBUG("Connect: ", string_http_hostname, " IPaddress: ", string_http_ipaddress ," port: ", n_http_port);
    DEBUG("Send Message:\n",CHttpClient.getSendMessage());
    DEBUG("Get Response\n", CHttpClient.getRecvMessage());

    return 0;
}