PHILOSOPHERS	=	philo

DIR_SRCS		=	srcs
DIR_OBJS		=	objs

SRCS_NAMES		=	error.c \

SRCS			=	${addprefix ${DIR_SRCS}/,${SRCS_NAMES}}
OBJS			=	${addprefix ${DIR_OBJS}/,${OBJS_NAMES}}

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}
DEPS			=	${SRCS_NAMES:.c=.d}

INCLUDE			=	-Iinclude
CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
CDFLAGS			=	-MMD -MP

${PHILOSOPHERS}:	${DIR_OBJS} ${OBJS}
					${CC} ${CFLAGS} ${OBJS} -o ${PHILOSOPHERS}

all:				${PHILOSOPHERS}

${DIR_OBJS}:
					mkdir -p ${DIR_OBJS}


${OBJS} :			${DIR_OBJS}/%.o : ${DIR_SRCS}/%.c
					${CC} ${CFLAGS} ${CDFLAGS} ${INCLUDE} -c $< -o $@

clean:
					rm -rf ${DIR_OBJS}

fclean:				clean
					rm -rf ${PHILOSOPHERS}

re:					fclean all

-include			${DEPS}

.PHONY:				all clean fclean re
.SILENT:
