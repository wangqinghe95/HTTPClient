#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "TCPClient.hpp"

const int MAX_CONTENT_SIZE = 8192;

TCPClient::TCPClient():m_sockfd(-1)
{

}
TCPClient::~TCPClient()
{
    m_sockfd = -1;
}

int TCPClient::connectServer(const std::string str_IPAddress, const int n_port)
{
    struct sockaddr_in servaddr;

    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, str_IPAddress.data(), &servaddr.sin_addr);
    servaddr.sin_port = htons(n_port);

    int ret = connect(m_sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret == -1) {
        return ret;
    }

    if(m_sockfd == 0) {
        return -1;
    }

    return m_sockfd;
}

std::string TCPClient::getIPAddressFromHostname(const std::string str_hostname)
{
    if(str_hostname.size() == 0) {
        return "";
    }

    int res = 0;
    const char* p_hostname = str_hostname.data();
    
    char p_IPAddress[128] = {0};

    getIPAddressFromHostname(p_hostname, p_IPAddress);

    return p_IPAddress;
}

int TCPClient::getIPAddressFromHostname(const char* p_hostname, char* p_out_IPAddress)
{
    if(p_hostname == NULL || p_out_IPAddress == NULL) {
        return -1;
    }

    addrinfo hits, *res;
    memset(&hits, 0, sizeof(hits));

    hits.ai_family = AF_UNSPEC;
    hits.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(p_hostname, NULL, &hits, &res);

    if(status != 0) {
        // fprintf(stderr, "getaddinfo: %s\n", gai_strerror(status));
        return -1;
    }
    
    // printf("IP address for %s: \n\n", p_hostname);

    bool b_copied = false;
    for(addrinfo* p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char ip_address[INET6_ADDRSTRLEN];
        if(p->ai_family == AF_INET){
            sockaddr_in *ipv4 = (sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
        }
        else {
            sockaddr_in6 *ipv6 = (sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ip_address, sizeof(ip_address));

        if(!b_copied){
            strncpy(p_out_IPAddress, ip_address, sizeof(ip_address));
            b_copied = true;
        }
    }

    freeaddrinfo(res);

    return b_copied;
}

int TCPClient::sendAndRecvMessage(const std::string send_message, std::string& str_out_message)
{
    send(m_sockfd, send_message.data(), send_message.size(), 0);

    // char *recv_buf = new char(8192);
    char recv_buf[MAX_CONTENT_SIZE] = {0};
    int recv_len = recv(m_sockfd, recv_buf, MAX_CONTENT_SIZE, 0);

    str_out_message = std::move(recv_buf);

    return 1;
}