/*
** my_ftp.h for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Sat Apr 15 16:52:02 2017 Yannis
** Last update Sun May 21 22:27:53 2017 Yannis
*/

#ifndef MY_FTP_H_
# define MY_FTP_H_

# include <sys/wait.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <pthread.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <netdb.h>
# include <fcntl.h>
# include <errno.h>

# define PASSIVE 1
# define ACTIF 0

# define ASCII 0
# define BINARY 1

# define ON 1
# define OFF 0

# define WIN 0

typedef struct	s_serv
{
  int		s_fd;
  int		s_port;
  int		c_fd;
  char		*path;
  char		*host;
}		t_serv;

typedef struct	s_dsocket
{
  int		status;
  int		mode;
  int		type;
  int		fd;
  int		c_fd;
  int		port1;
  int		port2;
  int		f_port;
  int		byte_readed;
  char		*activ_ip;
}		t_dsocket;

typedef struct	s_client
{
  int		fd;
  int		connexion;
  int		logged;
  char		*path_root;
  char		*user;
  char		**command;
  t_dsocket	data_socket;
}		t_client;

typedef struct	s_message
{
  int		code;
  char		*text;
}		t_message;

typedef struct	s_instruct
{
  char		*name;
  int		(* exec)(t_client *client);
}		t_instruct;

int	check_datac(t_client *);
int	init_serv(char *port, char *path, t_serv *serv);
int	enter_client(t_serv *serv);
int	error_msg(const char *msg);
int	push_message(int fd, const char *opt, int code);
int	interaction_client(t_serv *serv);
int	exec_command(t_client *client);
int	command_core(t_client *client);
int	kill_pasv(t_client *client);
int	pwd_current_dir(char **);
char	*list_get_buff(int);
int	kill_port(t_client *);
int	port_parse_core(int *i, char **ip, char **temp);
int	kill_data_channel(t_client *);
void	help(char *);
char	*fd_get_buff(int fd);
int	file_exist(char *filename);

int	i_log_in(t_client *);
int	i_pass(t_client *client);
int	i_pasv(t_client *client);
int	i_list(t_client *client);
int	i_cwd(t_client *);
int	i_cdup(t_client *);
int	i_pwd(t_client *);
int	i_retr(t_client *);
int	i_type(t_client *);
int	i_port(t_client *);
int	i_quit(t_client *);
int	i_stor(t_client *);
int	i_noop(t_client *);
int	i_dele(t_client *);
int	i_help(t_client *);

#endif
