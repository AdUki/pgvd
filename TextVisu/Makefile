
NAME		=	textvisu

DIRECTORY	=	TextVisu

CC		=	g++

RM		=	rm -f

SRC		=	main.cpp \
			element.cpp \
			composite.cpp \
			camera.cpp \

CFLAGS		=	-Wall \
			-W \
			- O2 \
			-Werror \
			-std=c++0x

IFLAGS		=

LFLAGS		=	-lFreeGlut \
				-lopengl32 \
				-lglu32 \

OBJ		=	$(SRC:.cpp=.o)

all :		$(NAME)

$(NAME) :	$(OBJ)
		$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

clean :
		$(RM) $(OBJ)
		$(RM) *~ \#*\#

run :		all
		./$(NAME)
