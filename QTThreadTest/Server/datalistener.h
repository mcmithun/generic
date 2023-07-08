#ifndef DATALISTENER_H
#define DATALISTENER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include "Header/header.h"

class DataListener
{
public:
    DataListener(int _port);
    bool Init();
    bool Receive(Header& header, char *&data, size_t maxlen);

    ~DataListener();
private:
    int m_port;
    int m_sockfd;

};

#endif // DATALISTENER_H
