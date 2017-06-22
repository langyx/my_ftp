/*
** main.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Fri Apr 14 16:32:44 2017 Yannis
** Last update Tue Apr 25 14:19:35 2017 Yannis
*/

#include "my_ftp.h"

void	help(char *name)
{
  printf("%s : port path\n", name);
}

void	sigcatch(int sig)
{
  exit(sig);
}

int		main(int ac, char **av)
{
  t_serv	serv;

  srand(time(NULL));
  signal(SIGINT, sigcatch);
  if (ac < 3)
    help(av[0]);
  else
    if (init_serv(av[1], av[2], &serv) == -1)
      return (-1);
  return (0);
}
