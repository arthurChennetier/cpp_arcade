CC	=	g++

DIRPATH = ../../games

RM	=	rm -f

SRC	=	OpenGl.cpp \
		Shader.cpp \
		DDS.cpp \
		Font.cpp \
		Mesh.cpp \
		Model.cpp \

NAME	=	lib_arcade_opengl.so

OBJ = $(SRC:.cpp=.o)

PIC	=	-fpic

SHARED	=	-shared

CXXFLAGS = 	-std=c++14 -W -Wall -Werror -Wextra -rdynamic -lGLEW -lGLU -lGL -lglfw3 -lXext -ldl -lrt -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lassimp -lSOIL

CPPFLAGS = -I./../../Include/

MV	=	mv

all: $(NAME)

$(NAME):
	$(CC) -c $(PIC) $(SRC) $(CPPFLAGS) $(CXXFLAGS)
	$(CC) $(SHARED) -o $(NAME) $(OBJ) $(CPPFLAGS) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
