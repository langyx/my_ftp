/*
** i_cwd.c for  in /home/yannis/work/my_ftp_one
**
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
**
** Started on  Tue Apr 25 23:45:02 2017 Yannis
** Last update Sun May 21 23:11:46 2017 Yannis
*/

#include "my_ftp.h"

int		file_exist(char *filename)
{
  struct stat	buffer;

  return (stat(filename, &buffer) == 0);
}

int	cwd_chdir(t_client *client, const char *path)
{
  if (chdir(path) != -1)
    {
      if (strcmp(client->command[0], "CDUP") == 0)
	push_message(client->fd, NULL, 200);
      else
	push_message(client->fd, NULL, 250);
    }
  else
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  return (0);
}

int	i_cdup(t_client *client)
{
  char	buff[1024];

  memset(buff, 0, 1024);
  getcwd(buff, sizeof(buff));
  if (strcmp(buff, client->path_root) == 0)
    {
      push_message(client->fd, NULL, 200);
      return (-1);
    }
  return (cwd_chdir(client, ".."));
}

int	i_cwd(t_client *client)
{
  if (client->command[1] == NULL)
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  if (WIN && file_exist(client->command[1]))
    return (push_message(client->fd, NULL, 250));
  else if (WIN && !file_exist(client->command[1]))
    return (push_message(client->fd, NULL, 550));
  return (cwd_chdir(client, client->command[1]));
}
