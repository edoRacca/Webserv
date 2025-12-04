NAME = webserv

CC = c++
FLAGS = -Wall -Wextra -Werror -g -D_GLIBCXX_DEBUG
CPPFLAGS = -std=c++98


SRCS = $(addprefix srcs/, main.cpp $(CPP) $(PARSING))
PARSING = $(addprefix parsing/, parseRequest.cpp)
CPP = $(addprefix cpp/, Server.cpp Client.cpp Request.cpp)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(CPPFLAGS) $^ -o $(NAME)

clean:
	@echo "wassup"

fclean:
	rm -f $(NAME)

re: fclean all

run: re
	clear ; ./$(NAME)

val: $(NAME)
	clear ; valgrind ./$(NAME)

.PHONY: all clean fclean run val
# .SILEN
