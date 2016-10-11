/*
 * WSServer.cpp
 *
 *  Created on: 07.10.2016
 *      Author: imolcean
 */

#include "WSServer.h"

#include "easylogging++.h"

namespace marco
{

WSServer::WSServer(boost::asio::io_service& io, func callback, unsigned int port, bool logs) : m_callback(callback), m_port(port)
{
	if(logs)
	{
		m_endpoint.set_error_channels(websocketpp::log::elevel::all);
		m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
	}
	else
	{
		m_endpoint.set_error_channels(websocketpp::log::elevel::none);
		m_endpoint.set_access_channels(websocketpp::log::alevel::none);
	}

    m_endpoint.init_asio(&io);

    m_endpoint.set_open_handler(std::bind(&WSServer::open_handler, this, std::placeholders::_1));
    m_endpoint.set_fail_handler(std::bind(&WSServer::fail_handler, this, std::placeholders::_1));
    m_endpoint.set_close_handler(std::bind(&WSServer::close_handler, this, std::placeholders::_1));
    m_endpoint.set_message_handler(std::bind(&WSServer::message_handler, this, std::placeholders::_1, std::placeholders::_2));
}

void WSServer::run()
{
    m_endpoint.listen(boost::asio::ip::tcp::v4(), m_port);
    m_endpoint.start_accept();
    m_endpoint.run();
}

void WSServer::open_handler(websocketpp::connection_hdl hdl)
{
	LOG(INFO) << "Connection open" << std::endl;
}

void WSServer::fail_handler(websocketpp::connection_hdl hdl)
{
	LOG(INFO) << "Connection failed" << std::endl;
}

void WSServer::close_handler(websocketpp::connection_hdl hdl)
{
	LOG(INFO) << "Connection closed" << std::endl;
}

void WSServer::message_handler(websocketpp::connection_hdl hdl, Server::message_ptr msg)
{
	LOG(INFO) << "Received: " << msg->get_payload() << " | " << msg->get_opcode() << std::endl;

	m_callback(msg->get_payload());
}

WSServer::~WSServer() {}

} /* namespace marco */
