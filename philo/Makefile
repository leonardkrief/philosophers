SRCS			=	srcs/exec.c \
					srcs/free.c \
					srcs/init.c \
					srcs/main.c \
					srcs/utils_1.c \
					srcs/utils_2.c

OBJS			=	${SRCS:.c=.o}

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDE			=	-Iinclude
RM				=	rm -rf

.c.o:
				${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

PHILOSOPHERS	=	philo

${PHILOSOPHERS}:	${OBJS}
					${CC} ${CFLAGS} ${OBJS} -o ${PHILOSOPHERS}

all:			${PHILOSOPHERS}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${PHILOSOPHERS} file log_file

re:				fclean all

.PHONY: 		all clean fclean re
