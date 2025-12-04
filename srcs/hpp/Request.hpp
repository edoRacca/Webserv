#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "../../includes/ether.hpp"

class	Request;
class	Response;

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

//FIXME - gestire transfer-encoding
class Request
{
	private:
		enum e_methods
		{
			POST,
			GET,
			DELETE
		};
		enum e_methods	_method;
		std::string		_url;
		std::string		_http_version;
		std::string		_host;
		int				_contentlength;
		std::string		_contenttype;
		std::string		_connection;
		std::string		_encoding;
		int				_port;
		std::string		_body;

	public:
		Request();
		~Request();
		Request(const Request &other);
		Request	&operator=(const Request &other);

		std::string getRequest() const; //format request
};

#endif