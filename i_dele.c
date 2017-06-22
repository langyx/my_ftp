/*
** i_dele.c for  in /home/yannis/rendu/PSU_2016_myftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Mon May  8 19:51:55 2017 Yannis
** Last update Sat May 20 21:38:50 2017 Yannis
*/

#include "my_ftp.h"

int	i_dele(t_client *client)
{
  if (client->command[1] == NULL)
    {
      push_message(client->fd, NULL, 501);
      return (-1);
    }
  else
    {
      if (WIN && file_exist(client->command[1]))
	return (push_message(client->fd, NULL, 250));
      else if (WIN && !file_exist(client->command[1]))
	return (push_message(client->fd, NULL, 550));
      else if (WIN && remove(client->command[1]) == -1)
	return (push_message(client->fd, NULL, 550));
      if (remove(client->command[1]) == -1)
	{
	  push_message(client->fd, NULL, 550);
	  return (-1);
	}
      push_message(client->fd, NULL, 250);
    }
  return (0);
}
