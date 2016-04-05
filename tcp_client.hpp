/**
    C++ client example using sockets
*/
#include <iostream>
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <string>  //string
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
 
using namespace std;
 
/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
    bool connected;
    bool debug;
     
public:
    tcp_client(bool initdebug=false);
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
};

