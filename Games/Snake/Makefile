CC					=						gcc
GPP					=						g++
RM 					= 					rm -f

PATHTOGAME	=						../../games
NAME 				=						lib_arcade_snake.so

SRC					=						Snake.cpp

CXXFLAGS		=						-Werror -W -Wall -Wextra -std=c++14

FLAGS				=						-I./../../../Include

OBJ					=						$(SRC:.cpp=.o)

all:	$(NAME)

$(NAME):
	$(GPP) -c -fPIC $(SRC) $(CXXFLAGS)
	$(GPP) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all
