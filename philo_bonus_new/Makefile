SRCS			=	srcs/child_process/dinner.c \
					srcs/child_process/struct_philo.c \
					srcs/child_process/threads.c \
					srcs/main_process/launcher.c \
					srcs/main_process/main.c \
					srcs/main_process/struct_infos.c \
					srcs/utils/error.c \
					srcs/utils/semaphores_safe.c \
					srcs/utils/time.c \
					srcs/utils/utils.c

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
