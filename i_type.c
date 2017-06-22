/*
** i_type.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Thu Apr 27 16:51:13 2017 Yannis
** Last update Thu Apr 27 17:22:14 2017 Yannis
*/

#include "my_ftp.h"

int	i_type(t_client *client)
{
  if (client->command[1] == NULL)
    {
      push_message(client->fd, "TYPE", 500);
      return (-1);
    }
  if (strcmp(client->command[1], "I") == 0
      || strcmp(client->command[1], "i") == 0)
    {
      client->data_socket.type = BINARY;
      push_message(client->fd, "Switching to Binary mode", 200);
    }
  else if (strcmp(client->command[1], "A") == 0
	   || strcmp(client->command[1], "a") == 0)
    {
      client->data_socket.type = ASCII;
      push_message(client->fd, "Switching to ASCII mode", 200);
    }
  else
    {
      push_message(client->fd, "TYPE", 500);
      return (-1);
    }
  return (0);
}
