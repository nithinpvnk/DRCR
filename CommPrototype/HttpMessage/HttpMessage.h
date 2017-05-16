#ifndef HTTP_H
#define HTTP_H

///////////////////////////////////////////////////////////////////////
// HttpMessage.h -  Build and parse HTTP style messages				 //
//-------------------------------------------------------------------//
// ver 1.0                                                           //
// Application: Project-4  Dependency based Remote Code Repository	 //
//				CSE687 - Object Oriented Design						                 //
// Author:		Venkata Nithin Kumar, Syracuse University				       //
// source:      Jim Fawcett, Syracuse University, CST 4-187          //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* This packages implements the building and parsing of 
* HTTP style messaging
*

Public Interface:
=================
*	void addAttribute(const Attribute& attrib) - add attribute pair to attribute collection
*	Value findValue(const Name& name) - find value of attribute with specified name
*	size_t findAttribute(const Name& name) - find attribute by name
*	bool removeAttribute(const Name& name) - remove attribute by name
*	Attributes& attributes() - retrieve attribute collection
*	static std::string attribString()- convert attribute pair to string
*	static Attribute attribute() - build attribute from name and value
*	static Attribute parseAttribute() - retrieve attribute collection
*	void setBody(byte buffer[], size_t Buflen)- fill body from buffer
*	size_t getBody(byte buffer[], size_t& Buflen)- fill buffer from body
*	void addBody(const Body& body) - replace body with old one
*	void addBody(const std::string& body)- replace body with contents of string
*	void addBody(size_t numBytes, byte* pBuffer)- replace body from buffer contents
*	Body& body() - retrieve body
*	size_t bodyLength() - return length of body in bytes
*	std::string headerString() const - convert message header to string
*	std::string bodyString() const - convert body to string
*	std::string toString() const - convert message to string
*	std::string toIndentedHeaderString() const - convert message header to indented string
*	std::string toIndentedBodyString() const - convert body to indented string
*	std::string toIndentedString() const - convert message to indented string
*	void clear() - remove all message contents
*	static void fillBuffer() - fill buffer with char

Build Process:
==============
Required Files:
  HttpMessage.h, Utilities.h, Utilities.cpp

Build commands:
===============
*   devenv CommPrototype.sln /rebuild debug

Maintenance History:
====================
ver 1.0 : 03 May 16
- first release

*/

#include <vector>
#include <string>

class HttpMessage
{
public:
  using byte = char;
  using Name = std::string;
  using Value = std::string;
  using Attribute = std::pair<Name, Value>;
  using Attributes = std::vector<Attribute>;
  using Terminator = std::string;
  using Body = std::vector<byte>;

  // message attributes
  void addAttribute(const Attribute& attrib);
  Value findValue(const Name& name);
  size_t findAttribute(const Name& name);
  bool removeAttribute(const Name& name);
  Attributes& attributes();
  static std::string attribString(const Attribute& attrib);
  static Attribute attribute(const Name& name, const Value& value);
  static Attribute parseAttribute(const std::string& src);

  // message body
  void setBody(byte buffer[], size_t Buflen);
  size_t getBody(byte buffer[], size_t& Buflen);
  void addBody(const Body& body);
  void addBody(const std::string& body);
  void addBody(size_t numBytes, byte* pBuffer);
  Body& body();
  size_t bodyLength();

  // display
  std::string headerString() const;
  std::string bodyString() const;
  std::string toString() const;
  std::string toIndentedHeaderString() const;
  std::string toIndentedBodyString() const;
  std::string toIndentedString() const;

  // cleanup
  void clear();
  static void fillBuffer(byte buffer[], size_t BufSize, byte fill = '\0');

private:
  Attributes attributes_;
  Terminator term_ = "\n";
  Body body_;
};

#endif