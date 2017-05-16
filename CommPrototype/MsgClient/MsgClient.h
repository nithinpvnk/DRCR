#ifndef MSGCLIENT_H
#define MSGCLIENT_H

///////////////////////////////////////////////////////////////////////
// MsgClient.h -  Implements client and send files to server		 //
//																	 //
//-------------------------------------------------------------------//
// ver 1.0                                                           //
// Application: Project-4  Dependency based Remote Code Repository	 //
//				CSE687 - Object Oriented Design						 //
// Author:		Venkata Nithin Kumar, Syracuse University		     //
// source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* This package implements a client that sends HTTP style messages and
* files to a server that simply displays messages and stores files.

Public Interface:
=================
*	void start() - starts sender and receiver threads upon request
*	void startSender() - starts client sender i.e socketconnector to send messages to server
*	bool Connect() - connects to the server upon request
*	void processRequest() - processes the request received from server
*	void MsgClient::postHMessage() - enqueue HTTP message request sent by GUI
*	void startReceiver() - starts client receiver i.e socketlistener to receive messages from server
*	void startSenderThread() - starts client sender on C++ thread
*	void startReceiverThread() - starts client receiver on C++ thread
*	std::string MsgClient::getMessage()- dequeues receiving queue to send to GUI for display
*	BlockingQueue<HttpMessage> getQ() - return the Blocking queue reference

Build Process:
==============
Required Files:
*   Server.h, MsgServer.cpp
*   HttpMessage.h, HttpMessage.cpp
*   Cpp11-BlockingQueue.h
*   Sockets.h, Sockets.cpp
*   FileSystem.h, FileSystem.cpp
*   Logger.h, Logger.cpp
*   Utilities.h, Utilities.cpp

Build commands:
===============
*   devenv CommPrototype.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 03 May 16
- first release

*/

#include "../HttpMessage/HttpMessage.h"
#include "../Sockets/Sockets.h"
#include "../FileSystem/FileSystem.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include <string>
#include <iostream>

using Show = StaticLogger<1>;
using namespace Utilities;
using Utils = StringHelper;


class ClientReceiver
{
public:
	ClientReceiver(BlockingQueue<HttpMessage>& msgQ) : msgQ_(msgQ) {}
	void operator()(Socket socket);
private:
	bool connectionClosed_;
	HttpMessage readMessage(Socket& socket);
	HttpMessage getParseMessage(Socket& socket);
	bool readFile(const std::string& filename, size_t fileSize, Socket& socket);
	BlockingQueue<HttpMessage>& msgQ_;
};

/////////////////////////////////////////////////////////////////////
// MsgClient class
// - was created as a class so more than one instance could be 
//   run on child thread
//
class MsgClient
{
public:
	using EndPoint = std::string;
	MsgClient(std::string ip, int port):ip_(ip),port_(port),clientReceiver(rcvQueue) {}
	void start();
	void startSender();
	bool Connect(SocketConnecter& si, std::string ipAddress, int port);
	void processRequest(SocketConnecter& si, std::string msg, std::string body);
	void MsgClient::postHMessage(const HttpMessage& msg);
	void startReceiver();
	void startSenderThread();
	void startReceiverThread();
	std::string MsgClient::getMessage();
	BlockingQueue<HttpMessage> getQ() { return sendingQueue; }
private:
	EndPoint endpoint;
	std::string ip_;
	int port_;
	BlockingQueue<HttpMessage> sendingQueue;
	BlockingQueue<HttpMessage> rcvQueue;
	HttpMessage makeMessage(size_t n, const std::string& msgBody, const EndPoint& ep);
	void sendMessage(HttpMessage& msg, Socket& socket);
	bool sendFile(const std::string& fqname, const std::string& dep, Socket& socket);
	ClientReceiver clientReceiver;
};

#endif