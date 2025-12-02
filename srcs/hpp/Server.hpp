
#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <poll.h>
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <sys/poll.h>
# include <netinet/in.h>
# include <unistd.h>
# include <vector>
# include <cstring>
# include <cstdlib>
# include <exception>

# ifndef MAX_CONNECTION
#  define MAX_CONNECTION 420
# endif

class Server //classe Server(HTTP) -> gestisce piu ip:porta in contemporanea
{
	private:
		std::vector<struct pollfd> _addrs; //pollfd per poll(), una struct per ogni ip:porta in ascolto
		int	_server_fd; //con piu server, se la classe Server rimane chiamata da 1 oggetto solo, e' inutile

	public:
		Server();
		~Server();
		
		void 			addSocket();
		struct pollfd	*getAddrs(void);
		size_t			getAddrSize(void) const;
		void			checkForConnection();
};


#endif