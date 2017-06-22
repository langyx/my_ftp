/*
** i_noop.c for  in /home/yannis/rendu/PSU_2016_myftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Mon May  8 19:13:03 2017 Yannis
** Last update Mon May  8 19:39:59 2017 Yannis
*/

#include "my_ftp.h"

int	i_noop(t_client *client)
{
  push_message(client->fd, NULL, 200);
  return (0);
}
