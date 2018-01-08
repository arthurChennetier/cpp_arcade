CC					=						gcc
GPP					=						g++
RM 					= 					rm -f
MAKE 				= 					make -C
MAKE_RE			=						make re -C
MAKE_CL			= 					make clean -C
MAKE_FC			=						make fclean -C

######			GUIS				######
SFML 			= 						SFML/
OPENGL		= 						OpenGL/
NCURSES		=							Ncurses/

all:
	$(MAKE) $(NCURSES)
	$(MAKE) $(SFML)
	$(MAKE) $(OPENGL)

clean:
	$(MAKE_CL) $(NCURSES)
	$(MAKE_CL) $(SFML)
	$(MAKE_CL) $(OPENGL)

fclean:
	$(MAKE_FC) $(NCURSES)
	$(MAKE_FC) $(SFML)
	$(MAKE_FC) $(OPENGL)

re: clean fclean all
