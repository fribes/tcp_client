
#include "tcp_client.hpp"

int main(int argc , char *argv[])
{
    tcp_client c;
    string host;
    int port;
     
    cout<<"Enter hostname : ";
    cin>>host;

    cout<<"Enter port : ";
    cin>>port;
     
    //connect to host
    c.conn(host , port);
     

    //send some data
    c.send_data("Hi!");
          
    //done
    return 0;
}