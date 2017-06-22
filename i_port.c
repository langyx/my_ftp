/*
** i_port.c for  in /home/yannis/work/my_ftp_one
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Thu Apr 27 23:13:40 2017 Yannis
** Last update Sat May 20 21:33:38 2017 Yannis
*/

#include "my_ftp.h"

int	port_count_param(t_client *client, char separator)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  while (client->command[1][i])
    {
      if (client->command[1][i] == separator)
	count += 1;
      i += 1;
    }
  return (count);
}

int	port_parse_ip(t_client *client)
{
  char	*temp;
  char	*ip;
  int	i;

  if (port_count_param(client, ',') != 5)
    return (-1);
  i = 0;
  temp = strtok(client->command[1], ",");
  ip = strdup(temp);
  ip = realloc(ip, (strlen(ip) + 1) * sizeof(char));
  strcat(ip, ".");
  while (i < 3)
    port_parse_core(&i, &ip, &temp);
  ip[strlen(ip) - 1] = 0;
  temp = strtok(NULL, ",");
  client->data_socket.port1 = atoi(temp);
  temp = strtok(NULL, ",");
  if (temp == NULL)
    return (-1);
  client->data_socket.port2 = atoi(temp);
  client->data_socket.activ_ip = strdup(ip);
  free(ip);
  return (0);
}

int			port_open_datac(int sock)
{
  struct sockaddr_in	serv;

  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = INADDR_ANY;
  serv.sin_port = htons(20);
  if (bind(sock, (struct sockaddr *) &serv, sizeof(serv)) < 0)
    return (error_msg("Error: Bind on 20"));
  return (0);
}

int			port_connect(t_client *client)
{
  struct sockaddr_in	sockaddrin;
  struct hostent	*host;
  int			sock;

  if (client->data_socket.status == ON)
    kill_port(client);
  client->data_socket.f_port = client->data_socket.port1 * 256
    + client->data_socket.port2;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (error_msg("Error : PORT socket"));
  sockaddrin.sin_family = AF_INET;
  if ((host = gethostbyname(client->data_socket.activ_ip)) == NULL)
    return (error_msg("Error : PORT gethostbyname"));
  bcopy(host->h_addr, &sockaddrin.sin_addr, host->h_length);
  sockaddrin.sin_port = htons(client->data_socket.f_port);
  if ((connect(sock, (struct sockaddr*) &sockaddrin,
		    sizeof(struct sockaddr_in))) == -1)
    return (error_msg("Error : PORT connect"));
  client->data_socket.c_fd = sock;
  return (0);
}

int	i_port(t_client *client)
{
  if (client->command[1] == NULL)
    {
      push_message(client->fd, NULL, 5002);
      return (-1);
    }
  if (WIN)
    return (push_message(client->fd, NULL, 200));
  if (port_parse_ip(client) == -1)
    {
      push_message(client->fd, NULL, 200);
      return (-1);
    }
  else if (port_connect(client) == 0)
    {
      client->data_socket.status = ON;
      client->data_socket.mode = ACTIF;
      push_message(client->fd, NULL, 200);
    }
  else
      push_message(client->fd, NULL, 5301);
  return (0);
}
