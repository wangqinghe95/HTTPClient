#ifndef TCP_CLIENT_HPP_
#define TCP_CLIENT_HPP_

#include <string>

class TCPClient
{
private:
    int m_sockfd;
public:
    TCPClient();
    ~TCPClient();

    int connectServer(const std::string str_IPAddress, const int n_port);

    std::string getIPAddressFromHostname(const std::string str_hostname);

    int sendAndRecvMessage(const std::string send_message, std::string& str_out_message);
private:
    int getIPAddressFromHostname(const char* p_hostname, char* p_out_IPAddress);

};

#endif