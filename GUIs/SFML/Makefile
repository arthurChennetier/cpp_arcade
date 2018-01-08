CC	=	g++

DIRPATH = ../../games

RM	=	rm -f

SRC	=	Sfml.cpp \

NAME	=	lib_arcade_sfml.so

OBJ = $(SRC:.cpp=.o)

PIC	=	-fpic

SHARED	=	-shared

CXXFLAGS = -std=c++14 -W -Wall -Wextra -Werror

CPPFLAGS = -I./../../Include/ -I./../../Buildings/SFML/include/ -L./../../Buildings/SFML/lib/ -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system

MV	=	mv

all: $(NAME)

$(NAME):
	$(CC) -c $(PIC) $(SRC) $(CXXFLAGS) $(CPPFLAGS)
	$(CC) $(SHARED) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
