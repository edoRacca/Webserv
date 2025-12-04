
#include "../hpp/Request.hpp"

Request::Request()
{

}

Request::~Request()
{

}

Request::Request(const Request &other)
{
	*this = other;
}

Request&	Request::operator=(const Request &other)
{
	if (this == &other)
		return (*this);
	this->_method = other._method;
	this->_url = other._url;
	this->_http_version = other._http_version;
	this->_host = other._host;
	this->_contentlength = other._contentlength;
	this->_contenttype = other._contenttype;
	this->_connection = other._connection;
	this->_encoding = other._encoding;
	this->_port = other._port;
	this->_body = other._body;
	return (*this);
}
