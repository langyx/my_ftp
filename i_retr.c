/*
** i_retr.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Wed Apr 26 00:48:43 2017 Yannis
** Last update Sun May 21 23:39:59 2017 Yannis
*/

#include "my_ftp.h"

int	retr_rw_ascii(t_client *client)
{
  char		*file_r;
  int		fd;
  struct stat	st;
  char		message[1024];

  if ((fd = open(client->command[1], O_RDONLY)) == -1)
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  stat(client->command[1], &st);
  sprintf(message, "%s", client->command[1]);
  push_message(client->fd, NULL, 150);
  file_r = list_get_buff(fd);
  while (client->data_socket.c_fd == -1);
  write(client->data_socket.c_fd, file_r, strlen(file_r));
  push_message(client->fd, message, 226);
  free(file_r);
  return (0);
}

int	read_binary_inf(t_client *client)
{
  char	buffer[1024];
  FILE	*source;
  FILE	*dest;

  source = fopen(client->command[1], "rb");
  if (!source)
    return (-1);
  while (client->data_socket.c_fd == -1);
  dest = fdopen(client->data_socket.c_fd, "wb");
  memset(buffer, 0, 1024);
  while (!feof(source))
    {
      client->data_socket.byte_readed = fread(buffer, 1, 1024, source);
      fwrite(buffer, 1, client->data_socket.byte_readed, dest);
      memset(buffer, 0, 1024);
    }
  fclose(source);
  fclose(dest);
  return (0);
}

int		retr_rw_binary(t_client *client)
{
  struct stat	st;
  char		message[1024];

  if (read_binary_inf(client) == -1)
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  stat(client->command[1], &st);
  sprintf(message, "%s", client->command[1]);
  push_message(client->fd, NULL, 150);
  client->data_socket.byte_readed = 0;
  return (0);
}

int	retr_core(t_client *client)
{
  if (client->data_socket.type == ASCII)
    return (retr_rw_ascii(client));
  else
    return (retr_rw_binary(client));
}

int	i_retr(t_client *client)
{
  if (client->data_socket.status == 0)
    {
      push_message(client->fd, NULL, 150);
      return (-1);
    }
  if (client->command[1] == NULL)
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  if (retr_core(client) == -1)
    return (-1);
  kill_data_channel(client);
  push_message(client->fd, "", 226);
  return (0);
}
