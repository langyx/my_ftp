/*
** i_stor.c for  in /home/yannis/rendu/PSU_2016_myftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Mon May  8 14:53:54 2017 Yannis
** Last update Sun May 21 23:40:25 2017 Yannis
*/

#include "my_ftp.h"

int	stor_binary(t_client *client)
{
  char	buffer[1024];
  FILE	*source;
  FILE	*dest;

  source = fdopen(client->data_socket.c_fd, "rb");
  dest = fopen(client->command[1], "wb");
  if (!source || !dest)
    {
      push_message(client->fd, NULL, 5301);
      return (-1);
    }
  memset(buffer, 0, 1024);
  while (!feof(source))
    {
      client->data_socket.byte_readed = fread(buffer, 1, 1024, source);
      fwrite(buffer, 1, client->data_socket.byte_readed, dest);
      memset(buffer, 0, 1024);
    }
  push_message(client->fd, client->command[1], 226);
  fclose(dest);
  fclose(source);
  return (0);
}

int	stor_ascii(t_client *client)
{
  char	*file_received;
  int	new_file;

  file_received = list_get_buff(client->data_socket.c_fd);
  if ((new_file = open(client->command[1],
		       O_WRONLY | O_CREAT, 0664)) == -1)
    {
      push_message(client->fd, NULL, 5301);
      return (-1);
    }
  if (write(new_file, file_received, strlen(file_received)) == -1)
    push_message(client->fd, NULL, 5301);
  else
    push_message(client->fd, client->command[1], 226);
  free(file_received);
  return (0);
}

int	stor_core(t_client *client)
{
  while (client->data_socket.c_fd == -1);
  if (client->data_socket.type == ASCII)
    return (stor_ascii(client));
  else
    return (stor_binary(client));
}

int	i_stor(t_client *client)
{
  if (client->command[1] == NULL)
    {
      push_message(client->fd, NULL, 550);
      return (-1);
    }
  if (WIN)
    return (push_message(client->fd, NULL, 250));
  push_message(client->fd, NULL, 150);
  stor_core(client);
  kill_data_channel(client);
  push_message(client->fd, "", 226);
  return (0);
}
