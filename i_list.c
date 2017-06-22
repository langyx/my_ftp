/*
** i_ls.c for  in /home/yannis/work/my_ftp_one
**
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
**
** Started on  Tue Apr 25 17:01:46 2017 Yannis
** Last update Sun May 21 23:38:26 2017 Yannis
*/

#include "my_ftp.h"

char	*list_get_buff(int fd)
{
  char	buffer[1024];
  char	*result;

  result = malloc(sizeof(char) * 1);
  strcpy(result, "");
  memset(buffer, 0, 1024);
  while (read(fd, buffer, 1023) != 0)
    {
      result = realloc(result,
		       sizeof(char) * (strlen(buffer) + strlen(result)));
      strcat(result, buffer);
      memset(buffer, 0, 1024);
    }
  return (result);
}

char	*list_exec(t_client *client)
{
  int	pipefd[2];
  char	*args[4];

  pipe(pipefd);
  if (fork() == 0)
    {
      close(pipefd[0]);
      dup2(pipefd[1], 1);
      dup2(pipefd[1], 2);
      close(pipefd[1]);
      args[0] = "/bin/ls";
      args[1] = "-l";
      if (client->command[1] != NULL)
	args[2] = strdup(client->command[1]);
      else
	args[2] = NULL;
      execv(args[0], args);
    }
  else
    {
      wait(NULL);
      close(pipefd[1]);
      return (list_get_buff(pipefd[0]));
    }
  return (NULL);
}

int	list_send_res(t_client *client, char *data)
{
  while (client->data_socket.c_fd == -1);
  if (write(client->data_socket.c_fd, data, strlen(data)) == -1)
    return (error_msg("Error: Write Data Channel"));
  return (0);
}

int	i_list(t_client *client)
{
  if (client->data_socket.status == 0)
    {
      push_message(client->fd, NULL, 425);
      return (-1);
    }
  list_send_res(client, list_exec(client));
  push_message(client->fd, NULL, 1501);
  kill_data_channel(client);
  push_message(client->fd, "", 226);
  return (0);
}
