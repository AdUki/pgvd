##
## "THE BEER-WARE LICENSE" (Revision 42):
## <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
## can do whatever you want with this stuff. If we meet some day, and you think
## this stuff is worth it, you can buy me a beer in return.
##

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
