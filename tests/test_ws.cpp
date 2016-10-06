/*
 * test_timer.cpp
 *
 *  Created on: 06.10.2016
 *      Author: imolcean
 */

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

//#include <functional>

// TODO Собственный IO

typedef websocketpp::server<websocketpp::config::asio> server;

class utility_server
{
private:
    server m_endpoint;

public:
    utility_server()
	{
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        m_endpoint.init_asio();

        m_endpoint.set_open_handler(std::bind(&utility_server::open_handler, this, std::placeholders::_1));
        m_endpoint.set_fail_handler(std::bind(&utility_server::fail_handler, this, std::placeholders::_1));
        m_endpoint.set_close_handler(std::bind(&utility_server::close_handler, this, std::placeholders::_1));
        m_endpoint.set_message_handler(std::bind(&utility_server::message_handler, this, std::placeholders::_1, std::placeholders::_2));
    }

    void run()
    {
        m_endpoint.listen(9002);
        m_endpoint.start_accept();
        m_endpoint.run();
    }

//    void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg)
//    {
//        m_endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
//    }

    void open_handler(websocketpp::connection_hdl hdl)
    {
    	std::cout << "Connection open" << std::endl;
    }

    void fail_handler(websocketpp::connection_hdl hdl)
    {
    	std::cout << "Connection failed" << std::endl;
    }

    void close_handler(websocketpp::connection_hdl hdl)
    {
    	std::cout << "Connection closed" << std::endl;
    }

    void message_handler(websocketpp::connection_hdl hdl, server::message_ptr msg)
    {
    	std::cout << "Received: " << msg->get_payload() << " | " << msg->get_opcode() << std::endl;
    }


};

int main() {
    utility_server s;

    s.run();

    return 0;
}
