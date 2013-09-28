
NAME		=	particlesystem

DIRECTORY	=	ParticleSystem

CC		=	g++

RM		=	rm -f

SRC		=	main.cpp \
			Particle.cpp \
			initializer.cpp \

CFLAGS		=	-Wall \
			-W \
			-Werror \
			-O2 \
			-std=c++0x

IFLAGS		=

LFLAGS		=	-lSOIL \
				-lFreeGlut \
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
