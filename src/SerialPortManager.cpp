#include "SerialPortManager.h"

SerialPortManager::SerialPortManager(){

};

SerialPortManager::~SerialPortManager(){

};

void SerialPortManager::addSerialPort(const PortConfig &portConfig)
{
    auto serialPort = std::make_unique<boost::asio::serial_port>(io_service);
    initSerialPort(*serialPort, portConfig);
    serialPorts.push_back(std::move(serialPort));
};

void SerialPortManager::initSerialPort(boost::asio::serial_port &serialPort, const PortConfig &portConfig)
{
    serialPort.open(portConfig.ComPort);
    serialPort.set_option(boost::asio::serial_port_base::baud_rate(portConfig.BaudRate));
    serialPort.set_option(boost::asio::serial_port_base::character_size(portConfig.DataBits));
    serialPort.set_option(boost::asio::serial_port_base::parity(static_cast<boost::asio::serial_port_base::parity::type>(portConfig.Parity)));
    serialPort.set_option(boost::asio::serial_port_base::stop_bits(static_cast<boost::asio::serial_port_base::stop_bits::type>(portConfig.StopBits)));
}

void SerialPortManager::handleRead(const boost::system::error_code& err,size_t bytesTransfer,boost::asio::serial_port& serialPort,std::vector<char>& buf){

};

void SerialPortManager::readFromSerialPort(boost::asio::serial_port& serialPort){
    auto buf = std::make_shared<std::vector<char>>(1024);
    serialPort.async_read_some(boost::asio::buffer(*buf),[this,&serialPort,buf](const boost::system::error_code& err,size_t bytesTransfer){
        handleRead(err,bytesTransfer,serialPort,*buf);
    });
}