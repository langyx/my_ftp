/*
** i_quit.c for  in /home/yannis/rendu/PSU_2016_myftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Mon May  8 14:02:44 2017 Yannis
** Last update Mon May  8 14:05:46 2017 Yannis
*/

#include "my_ftp.h"

int	i_quit(t_client *client)
{
  kill_data_channel(client);
  client->connexion = 0;
  push_message(client->fd, NULL, 221);
  return (0);
}
