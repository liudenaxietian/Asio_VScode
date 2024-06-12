#include "endpoint.h"

using namespace boost;

int client_end_point()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned char port_num = 33445;
    boost::system::error_code ec;

    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);
    if (ec.value() != 0)
    {
        std::cout << "Fail to parse the IP addrss, Error code = " << ec.value() << ". message :" << ec.message() << std::endl;
        return ec.value();
    }

    asio::ip::tcp::endpoint ep(ip_address, port_num);

    return 0;
}

int server_end_point()
{
    unsigned short port_num = 3333;
    boost::asio::ip::address ip_address = boost::asio::ip::address_v6::any();

    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

    return 0;
}

int create_tcp_socket()
{
    boost::asio::io_context ios;

    boost::asio::ip::tcp protocol = asio::ip::tcp::v4();
    boost::asio::ip::tcp::socket sock(ios);

    boost::system::error_code ec;
    sock.open(protocol, ec);
    if (ec.value() != 0)
    {
        std::cout << "Fail to open the socket! Error code = " << ec.value() << ". Message:" << ec.message() << std::endl;
        return ec.value();
    }
}

int create_acceptor_socket()
{
    boost::asio::io_context ios;
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v6();
    boost::asio::ip::tcp::acceptor acceptor(ios);

    boost::system::error_code ec;

    acceptor.open(protocol, ec);

    if (ec.value() != 0)
    {
        std::cerr << "Fail to open the acceptor socket!" << "Error code: " << ec.value() << ". Message:" << ec.message() << std::endl;
        return ec.value();
    }
    return 0;
}

int bind_acceptor_socket()
{
    unsigned short port_num = 3333;
    boost::asio::ip::tcp::endpoint ed(asio::ip::address_v4::any(), port_num);

    boost::asio::io_context ios;

    boost::asio::ip::tcp::acceptor acceptor(ios, ed.protocol());

    boost::system::error_code ec;
    acceptor.bind(ed, ec);
    if (ec.value() != 0)
    {
        std::cerr << "Fail to open the acceptor socket!" << "Error code: " << ec.value() << ". Message:" << ec.message() << std::endl;
        return ec.value();
    }
    return 0;
}

int connect_to_end()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    try
    {
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(raw_ip_address), port_num);

        boost::asio::io_context ios;

        boost::asio::ip::tcp::socket sock(ios, ep.protocol());

        sock.connect(ep);
    }
    catch (system::system_error &e)
    {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();

        return e.code().value();
    }
}


int dns_connect_to_end(){
    std::string host = "127.0.0.1";
    std::string port_num = "3333";

    boost::asio::io_context ios;

    boost::asio::ip::tcp::resolver::query resolver_query(host,port_num,boost::asio::ip::tcp::resolver::query::numeric_host);

    boost::asio::ip::tcp::resolver resolver(ios);

    try{
        boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);

        boost::asio::ip::tcp::socket sock(ios);

        boost::asio::connect(sock,it);

    }catch(system::system_error& e){
        std::cout<<"Error occured! Error code = "<< e.code()<<". Message: "<<e.what()<<std::endl;
        return e.code().value();
    }

    return 0;
}