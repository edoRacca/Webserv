
#include "../hpp/Request.hpp"

const std::string Request::_validmethods[3] = {
    "POST",
    "GET",
    "DELETE"
};

Request::Request()
{
	this->_method = UNDEFINED;
	this->_connection = UNDEFINED;
	this->_port = UNDEFINED;
}

/* void	Request::fill_checks(void)
{
	for (int i = 0; i < METH_NUM; i++)
		this->_validmethods[i] = VALID_METHODS[i]; spread democracy non morirà così facilmente
} */

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

std::string	Request::getValidMethod(int idx) const
{
	return (this->_validmethods[idx]);
}

int	Request::getMethod() const
{
	return (this->_method);
}

int Request::getMethNum() const
{
	return (this->METH_NUM);
}

std::string Request::getUrl() const
{
	return (this->_url);
}

std::string Request::getHttpVersion() const
{
	return (this->_http_version);
}

std::string Request::getHost() const
{
	return (this->_host);
}

int Request::getContentLenght() const
{
	return (this->_contentlength);
}

std::string Request::getContentType() const
{
	return (this->_contenttype);
}

std::string Request::getConnection() const
{
	return (this->_host);
}

std::string Request::getEncoding() const
{
	return (this->_encoding);
}

int Request::getPort() const
{
	return (this->_port);
}

std::string Request::getBody() const
{
	return (this->_body);
}

void	Request::setMethod(int method)
{
	this->_method = method;
}

void	Request::setUrl(std::string url)
{
	this->_url = url;
}

void	Request::setHttpVersion(std::string httpversion)
{
	this->_http_version = httpversion;
}

void	Request::setHost(std::string host)
{
	this->_host = host;
}

void	Request::setContentLength(int contentlength)
{
	this->_contentlength = contentlength;
}

void	Request::setContentType(std::string contenttype)
{
	this->_contenttype = contenttype;
}

void	Request::setConnection(std::string connection)
{
	this->_connection = connection;
}

void	Request::setEncoding(std::string encoding)
{
	this->_encoding = encoding;
}

void	Request::setPort(int port)
{
	this->_port = port;
}

void	Request::setBody(std::string body)
{
	this->_body = body;
}

std::ostream &operator<<(std::ostream &os, Request &obj)
{
	os << "Method: " << obj.getValidMethod(obj.getMethod()) << "\nURL: " << \
	obj.getUrl() << "\nVERSION: " << obj.getHttpVersion() << std::endl;
	return (os);
}