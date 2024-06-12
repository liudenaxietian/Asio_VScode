#include <iostream>
#include "endpoint.h"

using namespace std;

int main()
{

    client_end_point();
    server_end_point();
    create_tcp_socket();
    create_acceptor_socket();

    std::cout<<"done!"<<std::endl;
    std::cin.get();
    return 0;
}