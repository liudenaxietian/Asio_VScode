#include <iostream>
#include <string>
#include "boost/asio.hpp"

using namespace std;
using namespace boost::asio::ip;

const int MAX_LENGHT = 1024;

// boost/asio client test
int main()
{
    try
    {
        boost::asio::io_context ioc;
        tcp::endpoint remote_ep(address::from_string("127.0.0.1"), 10086);
        tcp::socket sock(ioc);
        boost::system::error_code error = boost::asio::error::host_not_found;
        sock.connect(remote_ep, error);

        if (error)
        {
            cout << "connect failed,code is:" << error.what() << " error message is: " << error.message() << std::endl;
            return 0;
        }
        std::cout << "Enter message: ";
        char request[MAX_LENGHT];
        std::cin.getline(request, MAX_LENGHT);
        size_t request_Length = strlen(request);

        boost::asio::write(sock, boost::asio::buffer(request, request_Length));

        char reply[MAX_LENGHT];
        size_t reply_length = boost::asio::read(sock, boost::asio::buffer(reply, reply_length));
        std::cout << "reply is:";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception &e)
    {
        std::cerr << "Expection: " << e.what() << std::endl;
    }
}