CC					=						gcc
GPP					=						g++
RM 					= 					rm -f
MAKE 				= 					make -C
MAKE_RE			=						make re -C
MAKE_CL			= 					make clean -C
MAKE_FC			=						make fclean -C
CP					=						cp

######			GAMES				#####
GAMES				=						Games/

######			GUIS				######
LIBS 				=						GUIs/

FLAGS				=						-W -Wall -Werror -Wextra -Wl,-rpath="./Buildings/SFML/lib" -Wl,-rpath="./Buildings/OpenGL/GLEW/"

FLAGS				+=					-ldl -I./Include -std=c++14

ARCADE 			=						arcade

SRC					=						arcade.cpp

OBJ					= 					$(SRC:.cpp=.o)

all:
	$(MAKE) $(GAMES)

ra: $(ARCADE)
	$(MAKE) $(GAMES)
	$(MAKE) $(LIBS)

$(ARCADE):
	$(GPP) -c $(SRC) $(FLAGS)
	$(GPP) -o $(ARCADE) $(OBJ) $(FLAGS)

clean:
	$(MAKE_CL) $(GAMES)
	$(MAKE_CL) $(LIBS)
	$(RM) $(OBJ)

fclean: clean
	$(MAKE_FC) $(GAMES)
	$(MAKE_FC) $(LIBS)
	$(RM) $(ARCADE)

copy:
	$(CP) Games/Pacman/lib_arcade_pacman.so games
	$(CP) Games/Snake/lib_arcade_snake.so games
	$(CP) GUIs/Ncurses/lib_arcade_ncurses.so lib
	$(CP) GUIs/SFML/lib_arcade_sfml.so lib
	$(CP) GUIs/OpenGL/lib_arcade_opengl.so lib

re: clean fclean all
