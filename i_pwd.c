/*
** i_pwd.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Wed Apr 26 00:04:47 2017 Yannis
** Last update Wed Apr 26 00:31:44 2017 Yannis
*/

#include "my_ftp.h"

int	pwd_current_dir(char **path)
{
  char	buff[1024];

  memset(buff, 0, 1024);
  if (getcwd(buff, sizeof(buff)) == NULL)
    return (error_msg("Error: Getcwd()"));
  *path = strdup(buff);
  return (0);
}

int	i_pwd(t_client *client)
{
  int	i;
  int	j;
  char	buff[1024];
  char	*dir;

  memset(buff, 0, 1024);
  if (getcwd(buff, sizeof(buff)) == NULL)
    return (error_msg("Error: Getcwd()"));
  if (strcmp(buff, client->path_root) == 0)
    {
      push_message(client->fd, "/", 257);
      return (0);
    }
  if ((dir = malloc(sizeof(char)
		    * (strlen(buff) - strlen(client->path_root) + 1))) == NULL)
    return (error_msg("Error: Malloc()"));
  memset(dir, 0, strlen(buff) - strlen(client->path_root + 1));
  i = strlen(client->path_root);
  j = 0;
  while (buff[i])
    dir[j++] = buff[i++];
  push_message(client->fd, dir, 257);
  free(dir);
  return (0);
}
