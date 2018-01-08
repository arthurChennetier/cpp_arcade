CC					=						gcc
GPP					=						g++
RM 					= 					rm -f
MAKE 				= 					make -C
MAKE_RE			=						make re -C
MAKE_CL			= 					make clean -C
MAKE_FC			=						make fclean -C

######			GAMES				#####
SNAKE 			= 					Snake/
PACMAN			= 					Pacman/

######			GUIS				######
SFML 			= 						GUIs/SFML
OPENGL		= 						GUIs/OpenGL
NCURSES		=							GUIs/Ncurses

all:
	$(MAKE) $(SNAKE)
	$(MAKE) $(PACMAN)

clean:
	$(MAKE_CL) $(PACMAN)
	$(MAKE_CL) $(SNAKE)

fclean:
	$(MAKE_FC) $(PACMAN)
	$(MAKE_FC) $(SNAKE)

re: clean fclean all
