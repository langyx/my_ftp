/*
** init_message.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Sat Apr 15 21:27:27 2017 Yannis
** Last update Sat May 20 11:59:36 2017 Yannis
*/

#include "my_ftp.h"

t_message	db_messages[] =
  {
    {150, "%d File status okay; about to open data connection.\r\n"},
    {1501, "150 Here comes the directory listing..\r\n"},
    {200, "%d Command okay.\r\n"},
    {214, "%d Help message. BlaBla\r\n"},
    {220, "%d Service ready for new user.\r\n"},
    {221, "%d Service closing control connection.\r\n"},
    {226, "%d Closing data connection. for file %s.\r\n"},
    {2261, "226 Closing data connection.\nDirectory send OK.\r\n"},
    {227, "%d Entering Passive Mode (%s).\r\n"},
    {230, "%d User logged in, proceed.\r\n"},
    {250, "%d Requested file action okay, completed.\r\n"},
    {257, "%d \"%s\" created.\r\n"},
    {331, "%d User name okay, need password.\r\n"},
    {332, "%d Need account for login.\r\n"},
    {425, "%d Use PORT or PASV first.\r\n"},
    {500, "%d Unrecognised %s command.\r\n"},
    {5001, "500 Unrecognised command.\r\n"},
    {5002, "500 Illegal PORT command.\r\n"},
    {501, "%d Syntax error in parameters or arguments.\r\n"},
    {530, "%d %s\r\n"},
    {5301, "530 Command ko.\r\n"},
    {550, "%d Failed to open file.\r\n"},
    {-1, NULL}
  };

int	push_message(int fd, const char *opt, int code)
{
  char	buff[1024];
  int	i;

  memset(buff, 0, 1024);
  i = 0;
  while (db_messages[i].code != -1)
    {
      if (db_messages[i].code == code)
	{
	  if (opt != NULL)
	    sprintf(buff, db_messages[i].text,
		    db_messages[i].code, opt);
	  else
	    sprintf(buff, db_messages[i].text,
		    db_messages[i].code);
	  if ((write(fd, buff, strlen(buff)) == -1))
	    return (error_msg("Error: Write"));
	  return (0);
	}
      i += 1;
    }
  return (-1);
}
