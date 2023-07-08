#include "datalistener.h"

DataListener::DataListener(int _port):  m_port(_port), m_sockfd(-1)
{

}

bool DataListener::Init()
{
    m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_sockfd < 0) {
        perror("socket");
        return false;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(m_port);

    if (bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(m_sockfd);
        return false;
    }

    return true;
}

bool DataListener::Receive(Header& header, char* &data, size_t maxlen) {
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    ssize_t nrecv = recvfrom(m_sockfd, &header, sizeof(header), 0,
                             (struct sockaddr*)&addr, &addrlen);
    if (nrecv < 0) {
        perror("recvfrom");
        return false;
    }
    if (nrecv != sizeof(header)) {
        fprintf(stderr, "Received incomplete header (%ld bytes)\n", nrecv);
        return false;
    }

    if (header.size > maxlen) {
        fprintf(stderr, "Received data payload too large (%d bytes, max %zd)\n",
                header.size, maxlen);
        return false;
    }

    nrecv = recvfrom(m_sockfd, data, (size_t)header.size, 0,
                     (struct sockaddr*)&addr, &addrlen);
    if (nrecv < 0) {
        perror("recvfrom");
        return false;
    }
    if (nrecv != header.size) {
        fprintf(stderr, "Received incomplete data payload (%ld bytes)\n", nrecv);
        return false;
    }

    return true;
}

DataListener::~DataListener() {
    if (m_sockfd >= 0) {
        close(m_sockfd);
    }
}
