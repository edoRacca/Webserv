#ifndef REQUEST_HPP
#define REQUEST_HPP

# include "../../includes/ether.hpp"

# define UNDEFINED -1

/*
##	CONTENUTO, DESCRIZIONE			ESEMPIO

METODO URI VERSIONE_HTTP		-	POST / HTTP/1.1
Host: porta client				-	Host: localhost:8080
User-Agent: ???					-	User-Agent: curl/8.17.1-DEV
ACCEPT: ???						-	Accept: \*\/\*
Content-Length: lunghezza msg	-	Content-Length: 10
	La lunghezza non deve
	superare un tot
	il tot va definito
Content-Type:	???				-	Content-Type: application/x-www-form-urlencoded
Connection: TYPE				-	Connection: keep-alive
Transfer-Encoding: ???			-	???
\n	(riga vuota)				-	\n
MESSAGGIO						-	ciao monco

_http:		TUTTO
_host:		localhost:8080
_content:	10
_uri:		/
*/

// FIXME - gestire transfer-encoding
class Request
{
private:
	enum e_methods
	{
		POST,
		GET,
		DELETE,
		METH_NUM,
	};
	static const std::string	_validmethods[3];
	int 						_method;
	std::string 				_url;
	std::string 				_http_version;
	std::string 				_host;
	int 						_contentlength;
	std::string 				_contenttype;
	std::string 				_connection;
	std::string 				_encoding;
	int 						_port;
	std::string 				_body;

	// void		fill_checks(void);

public:
	Request();
	~Request();
	Request(const Request &other);
	Request &operator=(const Request &other);

	//getters
	std::string	getValidMethod(int idx) const;
	int			getMethNum() const;
	int			getMethod() const;
	std::string 	getUrl() const;
	std::string 	getHttpVersion() const;
	std::string 	getHost() const;
	int 			getContentLenght() const;
	std::string 	getContentType() const;
	std::string 	getConnection() const;
	std::string 	getEncoding() const;
	int 			getPort() const;
	std::string 	getBody() const;
	
	//setters
	void	setMethod(int method);
	void 	setUrl(std::string);
	void 	setHttpVersion(std::string);
	void 	setHost(std::string);
	void	setContentLength(int);
	void	setContentType(std::string);
	void	setConnection(std::string);
	void 	setEncoding(std::string);
	void 	setPort(int);
	void	setBody(std::string);
};

std::ostream &operator<<(std::ostream &os, Request &obj);

#endif