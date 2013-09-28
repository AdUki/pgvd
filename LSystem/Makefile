
NAME		=	lsystem

DIRECTORY	=	LSystem

CC		=	g++

RM		=	rm -f

SRC		=	main.cpp \
			lsystem.cpp \

CFLAGS		=	-Wall \
				-W \
				-Werror \
				-O2 \
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

run :	all
		./$(NAME)
