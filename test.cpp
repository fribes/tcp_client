
#include "tcp_client.hpp"

int main(int argc , char *argv[])
{
     tcp_client* c; 

    string host="localhost";
    int port = 5000;

    c = new tcp_client();
     
    //connect to host
    c->conn(host , port);
   

    //send some data
    c->send_data("Hi!\n");

    //connect to host
    c->conn(host , port);
   

    //send some data
    c->send_data("Hi2!\n");
          
    //done
    return 0;
}