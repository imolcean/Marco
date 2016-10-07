/*
 * WSServer.h
 *
 *  Created on: 07.10.2016
 *      Author: imolcean
 */

#ifndef SRC_WSSERVER_H_
#define SRC_WSSERVER_H_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef std::function<void(std::string)> func;

namespace marco
{

class WSServer
{
private:
	Server m_endpoint;
	func m_callback;
	unsigned int m_port;

	void open_handler(websocketpp::connection_hdl hdl);
	void fail_handler(websocketpp::connection_hdl hdl);
	void close_handler(websocketpp::connection_hdl hdl);
	void message_handler(websocketpp::connection_hdl hdl, Server::message_ptr msg);

public:
	WSServer(boost::asio::io_service& io, func callback, unsigned int port, bool logs);

	void run();

	virtual ~WSServer();
};

} /* namespace marco */

#endif /* SRC_WSSERVER_H_ */
