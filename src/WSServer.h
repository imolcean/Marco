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

/**
 * Receives messages using the websocket protocol.
 */
class WSServer
{
private:
	Server m_endpoint;
	func m_callback;
	unsigned int m_port;

	/**
	 * Callback for the connection establishing.
	 *
	 * @param hdl connection object
	 */
	void open_handler(websocketpp::connection_hdl hdl);

	/**
	 * Callback for the connection failure.
	 *
	 * @param hdl connection object
	 */
	void fail_handler(websocketpp::connection_hdl hdl);

	/**
	 * Callback for the connection closing.
	 *
	 * @param hdl connection object
	 */
	void close_handler(websocketpp::connection_hdl hdl);

	/**
	 * Callback for the receiving of a message.
	 *
	 * @param hdl connection object
	 * @param msg message object
	 */
	void message_handler(websocketpp::connection_hdl hdl, Server::message_ptr msg);

public:

	/**
	 * Constructor.
	 *
	 * @param io io service
	 * @param callback callback function for the message payload
	 * @param port network port to start the websocket server on
	 * @param logs whether the WebSocket++ logs have to be enabled
	 */
	WSServer(boost::asio::io_service& io, func callback, unsigned int port, bool logs);

	/**
	 * Starts the websocket server.
	 *
	 * This method blocks, so call it in a separate thread
	 */
	void run();

	/**
	 * Destructor.
	 */
	virtual ~WSServer();
};

} /* namespace marco */

#endif /* SRC_WSSERVER_H_ */
