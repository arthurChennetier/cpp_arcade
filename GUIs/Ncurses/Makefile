CC	=	g++

DIRPATH = ../../games

RM	=	rm -f

SRC	=	Ncurses.cpp \

NAME	=	lib_arcade_ncurses.so

OBJ = $(SRC:.cpp=.o)

PIC	=	-fpic

SHARED	=	-shared

CXXFLAGS = -std=c++14 -W -Wall -Wextra -Werror

CPPFLAGS = -I./../../../Include -lncurses -lmenu

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
