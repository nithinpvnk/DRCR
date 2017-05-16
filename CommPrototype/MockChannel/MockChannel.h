#ifndef MOCKCHANNEL_H
#define MOCKCHANNEL_H

///////////////////////////////////////////////////////////////////////
// MockChannel.h - Acts as a channel between C++ and native code	 //
//				 - build as DLL										 //
//-------------------------------------------------------------------//
// ver 1.0                                                           //
// Application: Project-4  Dependency based Remote Code Repository	 //
//				CSE687 - Object Oriented Design						                 //
// Author:		Venkata Nithin Kumar, Syracuse University				       //
// source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* This package implements a client that sends HTTP style messages and
* files to a server that simply displays messages and stores files.

Public Interface:
=================
*	std::string getMessage() - receives messages from client to display on GUI
*	void postMessage()	- send HTTP style message request to client
*	void start()		- starts the client

Build Process:
==============
Required Files:
*   MsgClient.h, MsgClient.cpp
*   HttpMessage.h, HttpMessage.cpp
*	WPF.h, WPF.cpp, Cpp11-BlockingQueue.h

Build commands:
===============
*   devenv CommPrototype.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 03 May 16
- first release

*/

#ifdef IN_DLL
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif
#include <string>

struct IMockChannel
{
public:
	virtual std::string getMessage() = 0;
	virtual void postMessage(const std::string& msg, const std::string& body) = 0;
	virtual void start() = 0;
};

extern "C" {
  struct ObjectFactory
  {
    DLL_DECL IMockChannel* createMockChannel(std::string ip, int port);
  };
}


#endif


