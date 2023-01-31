CFLAGS 			= -Wall -Wextra -Werror
CC 				= cc
RM 				= rm -f
NAME			= client_server

MANDSERVERSRC=	server.c
MANDCLIENTSRC=	client.c
MANDSERVEROBJS= ${MANDSERVERSRC:.c=.o}
MANDCLIENTOBJS= ${MANDCLIENTSRC:.c=.o}

SERVERSRCBONUS=	server_bonus.c
CLIENTSRCBONUS=	client_bonus.c
BONUSSERVEROBJS= ${SERVERSRCBONUS:.c=.o}
BONUSCLIENTOBJS= ${CLIENTSRCBONUS:.c=.o}

%.o:%.c
		${CC} -c $< -o $@ ${CFLAGS}

all:    ${NAME}

${NAME}: 	print client server 
			
print:	
		make all -C ft_printf
		make all -C ft_libft

bonus:	print client_bonus server_bonus

server: ${MANDSERVEROBJS}
		${CC} ${CFLAGS} ${MANDSERVEROBJS} ft_printf/libftprintf.a ft_libft/libft.a -o server

client: ${MANDCLIENTOBJS}
		${CC} ${CFLAGS} ${MANDCLIENTOBJS} ft_printf/libftprintf.a ft_libft/libft.a -o client

server_bonus:	${BONUSSERVEROBJS}
				${CC} ${CFLAGS} ${BONUSSERVEROBJS} ft_printf/libftprintf.a ft_libft/libft.a -o server

client_bonus:	${BONUSCLIENTOBJS}
				${CC} ${CFLAGS} ${BONUSCLIENTOBJS} ft_printf/libftprintf.a ft_libft/libft.a -o client

clean:	
		${RM} ${MANDSERVEROBJS} ${MANDCLIENTOBJS} ${BONUSSERVEROBJS} ${BONUSCLIENTOBJS}
		make -C ft_printf clean
		make -C ft_libft clean
	
fclean:	clean
		${RM} client server
		make -C ft_libft fclean

re:	fclean all

.PHONY: all re fclean