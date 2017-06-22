/*
** i_log_in.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Fri Apr 21 12:37:04 2017 Yannis
** Last update Mon May  8 13:53:52 2017 Yannis
*/

#include "my_ftp.h"

int	i_pass(t_client *client)
{
  if (client->user == NULL)
    {
      push_message(client->fd, NULL, 332);
      return (0);
    }
  if (strcmp("Anonymous" , client->user) == 0
      && client->command[1] == NULL)
    {
      client->logged = 1;
      push_message(client->fd, NULL, 230);
    }
  else
    push_message(client->fd, "Please login with USER and PASS.", 530);
  return (0);
}

int	i_log_in(t_client *client)
{
  if (client->logged)
    {
      push_message(client->fd, "Can't change from guest user.", 530);
      return (0);
    }
  if (client->command[1] != NULL
      && strlen(client->command[1]) > 0)
    client->user = strdup(client->command[1]);
  else
    {
      push_message(client->fd, NULL, 501);
      return (-1);
    }
  push_message(client->fd, NULL, 331);
  return (0);
}
