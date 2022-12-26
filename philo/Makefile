SRCS			=	srcs/exec.c \
					srcs/free.c \
					srcs/init.c \
					srcs/main.c \
					srcs/utils.c
OBJS			=	${SRCS:.c=.o}

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3 -O3
INCLUDE			=	-Iinclude
RM				=	rm -rf

.c.o:
				${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

PHILOSOPHERS	=	philo

${PHILOSOPHERS}:	${OBJS}
					${CC} ${CFLAGS} ${OBJS} -o ${PHILOSOPHERS}

debug:				${OBJS}
					${CC} ${CFLAGS} -g3 -fsanitize=thread ${OBJS} -o ${PHILOSOPHERS}

all:			${PHILOSOPHERS}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${PHILOSOPHERS} file log_file

re:				fclean all

.PHONY: 		all clean fclean re
