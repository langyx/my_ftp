##
## Makefile for  in /home/yannis/work/my_ftp
## 
## Made by Yannis
## Login   <yannis.lang@epitech.eu>
## 
## Started on  Fri Apr 14 16:41:55 2017 Yannis
## Last update Sun May 21 22:09:15 2017 Yannis
##

SRC	= main.c \
	  init_client.c \
	  init_message.c \
	  init_server.c \
	  command_core.c \
	  command_exec.c \
	  i_log_in.c \
	  i_pasv.c \
	  i_list.c \
	  i_pwd.c \
	  i_retr.c \
	  i_type.c \
	  i_port.c \
	  i_quit.c \
	  i_stor.c \
	  i_dele.c \
	  i_help.c \
	  i_noop.c \
	  i_port_end.c \
	  i_cwd.c \
	  read_inf.c

NAME	= server

CFLAGS  = -lpthread -W -Wall -Wextra -Werror

CC	= cc

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
