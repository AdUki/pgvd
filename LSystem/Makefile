##
## "THE BEER-WARE LICENSE" (Revision 42):
## <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
## can do whatever you want with this stuff. If we meet some day, and you think
## this stuff is worth it, you can buy me a beer in return.
##

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
