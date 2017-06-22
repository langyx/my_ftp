/*
** init_client.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Sat Apr 15 18:18:13 2017 Yannis
** Last update Sun May 21 22:14:30 2017 Yannis
*/

#include "my_ftp.h"

int	check_datac(t_client *client)
{
  if (fcntl(client->data_socket.c_fd, F_GETFD) != -1 || errno != EBADF)
    return (1);
  return (0);
}

int	kill_data_channel(t_client *client)
{
  if (client->data_socket.mode == PASSIVE)
    kill_pasv(client);
  else if (client->data_socket.mode == ACTIF)
    kill_port(client);
  return (0);
}

int			enter_client(t_serv *serv)
{
  struct sockaddr_in	c_addr;
  int			new_fd;

  new_fd = sizeof(c_addr);
  if ((new_fd = accept(serv->s_fd,
		       (struct sockaddr*)&(c_addr),
		       (socklen_t*)&new_fd)) <= 0)
    return (error_msg("Error: Accept Client"));
  else
    printf("Client %s at port %d is connecting\n",
	   inet_ntoa(c_addr.sin_addr),
	   (int) ntohs(c_addr.sin_port));
  return (new_fd);
}

int	define_client(t_serv *serv, t_client *client)
{
  client->user = NULL;
  client->fd = serv->c_fd;
  client->connexion = 1;
  client->logged = 0;
  push_message(client->fd, NULL, 220);
  if ((client->command = malloc(sizeof(char *) * 4)) == NULL)
    return (error_msg("Error : Malloc Command Tab"));
  memset(client->command, 0, sizeof(char*) * 4);
  client->command[0] = NULL;
  client->command[1] = NULL;
  client->command[2] = NULL;
  client->command[3] = NULL;
  client->data_socket.status = OFF;
  client->data_socket.type = BINARY;
  client->data_socket.c_fd = -1;
  client->data_socket.byte_readed = 0;
  client->data_socket.activ_ip = NULL;
  pwd_current_dir(&client->path_root);
  return (0);
}

int		interaction_client(t_serv *serv)
{
  t_client	client;

  memset(&client, 0, sizeof(t_client));
  if (define_client(serv, &client) == -1)
    return (-1);
  while (client.connexion == 1)
    command_core(&client);
  return (0);
}
