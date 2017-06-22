/*
** init_server.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Sat Apr 15 17:16:32 2017 Yannis
** Last update Thu May 11 23:26:25 2017 Yannis
*/

#include "my_ftp.h"

int	error_msg(const char *msg)
{
  printf("%s\n", msg);
  return (-1);
}

void	define_serv(char *port, char *path, t_serv *serv)
{
  serv->s_port = atoi(port);
  if (serv->s_port == 0)
    serv->s_port = 21;
  serv->path = strdup(path);
}

int			run_socket(t_serv *serv)
{
  int			useless;
  struct sockaddr_in	s_addr;

  serv->host = strdup("127.0.0.1");
  if ((serv->s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (error_msg("Error: creation of socket"));
  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = INADDR_ANY;
  s_addr.sin_port = htons(serv->s_port);
  if (setsockopt(serv->s_fd, SOL_SOCKET, SO_REUSEADDR,
		 &useless, sizeof(int)) == -1)
    return (error_msg("Error: set setsockopt"));
  if ((bind(serv->s_fd, (struct sockaddr*)&s_addr,
	    sizeof((s_addr)))) == -1)
    return (error_msg("Error: set bind"));
  if ((listen(serv->s_fd, 500)) == -1)
    return (error_msg("Error: set listen"));
  printf("Just start server on port %d\n", serv->s_port);
  return (0);
}

int	run_serv_loop(t_serv *serv)
{
  int	new_fd;
  pid_t	pid;

  while (1)
    {
      if ((new_fd = enter_client(serv)) == -1)
	return (-1);
      if ((pid = fork()) == 0)
	{
	  close(serv->s_fd);
	  serv->c_fd = new_fd;
	  interaction_client(serv);
	  close(new_fd);
	  return (0);
	}
      else if (pid < 0)
	return (error_msg("Error: fork"));
      else
	close(new_fd);
    }
  return (0);
}
int	init_serv(char *port, char *path, t_serv *serv)
{
  if (chdir(path) == -1)
    return (error_msg("Anonymous Path Invalid"));
  define_serv(port, path, serv);
  if (run_socket(serv) != 0)
    return (-1);
  return (run_serv_loop(serv));
}
