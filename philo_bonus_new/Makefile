SRCS			=	srcs/death.c \
					srcs/dinner.c \
					srcs/error.c \
					srcs/launcher.c \
					srcs/main.c \
					srcs/semaphores_safe.c \
					srcs/struct_infos.c \
					srcs/struct_philo.c \
					srcs/time.c \
					srcs/utils.c

OBJS			=	${SRCS:.c=.o}

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g3
INCLUDE			=	-Iinclude
RM				=	rm -rf

.c.o:
				${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

PHILOSOPHERS	=	philo_bonus

${PHILOSOPHERS}:	${OBJS}
					${CC} ${CFLAGS} ${OBJS} -o ${PHILOSOPHERS}

all:			${PHILOSOPHERS}

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${PHILOSOPHERS} file log_file

re:				fclean all

.PHONY: 		all clean fclean re
