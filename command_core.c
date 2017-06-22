/*
** command_core.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Sat Apr 15 22:54:33 2017 Yannis
** Last update Sun May 21 22:25:47 2017 Yannis
*/

#include "my_ftp.h"

char	*epure_command(char *str)
{
  char	*src;
  int	i;
  int	j;

  i = 0;
  j = 0;
  if ((src = malloc(sizeof(char *) * strlen(str))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
	    i = i + 1;
	  if (j > 0 && str[i] != '\0')
	    src[j++] = ' ';
	}
      src[j] = str[i];
      j = j + 1;
      i = i + 1;
    }
  src[j] = 0;
  return (src);
}

int	parse_command(t_client *client, char *buff)
{
  char	*temp;
  int	i;

  i = strlen(buff);
  while (i-- >= 0)
    if (buff[i] == '\n' || buff[i] == '\r')
      buff[i] = ' ';
  temp = strtok(epure_command(buff), " ");
  if (temp != NULL)
    client->command[0] = strdup(temp);
  if ((temp = strtok(NULL, " ")) != NULL)
    client->command[1] = strdup(temp);
  else
    client->command[1] = NULL;
  if ((temp = strtok(NULL, " ")) != NULL)
    client->command[2] = strdup(temp);
  else
    client->command[2] = NULL;
  return (0);
}

int	command_core(t_client *client)
{
  char	*buff;

  buff = fd_get_buff(client->fd);
  if (strlen(buff) == 0)
    client->connexion = 0;
  else
    {
      parse_command(client, buff);
      if (client->command[0] != NULL)
	exec_command(client);
      else
	push_message(client->fd, "", 500);
    }
  return (0);
}
