/*
** i_pasv.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Tue Apr 25 12:23:08 2017 Yannis
** Last update Sat May 20 12:11:47 2017 Yannis
*/

#include "my_ftp.h"

int	kill_pasv(t_client *client)
{
  close(client->data_socket.fd);
  client->data_socket.fd = 0;
  close(client->data_socket.c_fd);
  client->data_socket.c_fd = -1;
  client->data_socket.status = OFF;
  return (0);
}

int	pasv_get_port(t_client *client)
{
  (rand() % 2) ? (client->data_socket.port1 = 255)
    : (client->data_socket.port1 = 254);
  client->data_socket.port2 = rand() % 255 - (255 - client->data_socket.port1);
  client->data_socket.f_port = client->data_socket.port1 * 256
    + client->data_socket.port2;
  return (0);
}

void	*pasv_accept(void *arg)
{
  t_client	*client;

  client = (t_client *) arg;
  client->data_socket.c_fd = accept(client->data_socket.fd,
				    NULL, NULL);
  pthread_exit(NULL);
}

int			pasv_run_socket(t_client *client)
{
  struct sockaddr_in	s_addr;
  int			useless;
  pthread_t		accept_t;

  pasv_get_port(client);
  if ((client->data_socket.fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (error_msg("Error: creation of socket"));
  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = INADDR_ANY;
  s_addr.sin_port = htons(client->data_socket.f_port);
  if (setsockopt(client->data_socket.fd, SOL_SOCKET, SO_REUSEADDR,
		 &useless, sizeof(int)) == -1)
    return (error_msg("Error: set setsockopt"));
  if ((bind(client->data_socket.fd, (struct sockaddr*)&s_addr,
	    sizeof((s_addr)))) == -1)
    return (-2);
  if ((listen(client->data_socket.fd, 500)) == -1)
    return (error_msg("Error: set listen"));
  pthread_create(&accept_t, NULL, pasv_accept, (void *) client);
  return (0);
}

int	i_pasv(t_client *client)
{
  char	message[1024];
  int	result;

  if (client->data_socket.status == ON)
    kill_pasv(client);
  if ((result = pasv_run_socket(client)) == 0)
    {
      client->data_socket.status = ON;
      client->data_socket.mode = PASSIVE;
      memset(message, 0, 1024);
      sprintf(message, "127,0,0,1,%d,%d",
	      client->data_socket.port1,
	      client->data_socket.port2);
      push_message(client->fd, message, 227);
    }
  return (0);
}
