/*
** read_inf.c for  in /home/yannis/work/my_irc_one/server
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Thu May 11 13:13:36 2017 Yannis
** Last update Sun May 21 22:25:10 2017 Yannis
*/

#include "my_ftp.h"

char	*fd_get_buff(int fd)
{
  char	buffer[10];
  char	*result;

  result = malloc(sizeof(char) * 1);
  strcpy(result, "");
  memset(buffer, 0, 10);
  while (read(fd, buffer, 9) != 0)
    {
      result = realloc(result, sizeof(char) *
		       (strlen(buffer) + strlen(result)));
      strcat(result, buffer);
      if (strstr(result, "\n") != NULL ||
	  strstr(result, "\r") != NULL)
	return (result);
      memset(buffer, 0, 10);
    }
  return (result);
}
