#include "tcp_client.hpp"

#define DEBUG( x ) if (debug == true) cout<<x

 tcp_client::tcp_client(bool initdebug)
{
    sock = -1;
    port = 0;
    address = "";
    connected = false;
    debug = initdebug;
    DEBUG("Constructor\n");
}
 
/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(string address , int port)
{
    DEBUG("Entering connect\n");
    if (connected == true) {
        DEBUG("Reusing existing connection\n");
        return true;
    }

    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }
         
        DEBUG("Socket created\n");
    }
    else {   
        DEBUG("Reusing existing socket\n");
    }
     
    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            perror("gethostbyname");
            DEBUG("Failed to resolve hostname\n");
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            DEBUG(address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl);
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    connected = true;
    DEBUG("Connected\n");
    return true;
}
 
/**
    Send data to the connected host
*/
bool tcp_client::send_data(string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    DEBUG("Data send\n");
     
    return true;
}
 
/**
    Receive data from the connected host
*/
string tcp_client::receive(int size=512)
{
    char buffer[size];
    string reply;
     
    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        DEBUG("recv failed\n");
    }
     
    reply = buffer;
    return reply;
}
 
