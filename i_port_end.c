/*
** i_port_end.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Fri Apr 28 19:48:12 2017 Yannis
** Last update Fri Apr 28 20:09:23 2017 Yannis
*/

#include "my_ftp.h"

int	kill_port(t_client *client)
{
  client->data_socket.fd = 0;
  close(client->data_socket.c_fd);
  client->data_socket.c_fd = -1;
  client->data_socket.status = OFF;
  if (client->data_socket.activ_ip != NULL)
    {
      free(client->data_socket.activ_ip);
      client->data_socket.activ_ip = NULL;
    }
  return (0);
}

int	port_parse_core(int *i, char **ip, char **temp)
{
  *temp = strtok(NULL, ",");
  *ip = realloc(*ip, sizeof(char) * (strlen(*ip) + strlen(*temp) + 1));
  strcat(*ip, *temp);
  strcat(*ip, ".");
  *i += 1;
  return (0);
}
