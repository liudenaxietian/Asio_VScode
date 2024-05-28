#ifndef __SERIALPORTMANAGER_H__
#define __SERIALPORTMANAGER_H__

#include <vector>
#include <mutex>
#include "boost/asio.hpp"

struct PortConfig{
    std::string ComPort;
    int BaudRate;
    int DataBits;
    int StopBits;
    int Parity;
    int timeOut;
};

class SerialPortManager
{
public:
    SerialPortManager();
    ~SerialPortManager();
    void addSerialPort(const PortConfig& portConfig);

private:
    void initSerialPort(boost::asio::serial_port& serialPort,const PortConfig& portConfig);
    void readFromSerialPort(boost::asio::serial_port& serialPort);
    void handleRead(const boost::system::error_code& err,size_t bytesTransfer,boost::asio::serial_port& serialPort,std::vector<char> &buf);
    boost::asio::io_service io_service;
    std::vector<std::unique_ptr<boost::asio::serial_port>> serialPorts;
    std::mutex mutex;
    std::vector<std::thread*> threads;
};

#endif //__SERIALPORTMANAGER_H__