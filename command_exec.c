/*
** command_exec.c for  in /home/yannis/work/my_ftp
** 
** Made by Yannis
** Login   <yannis.lang@epitech.eu>
** 
** Started on  Fri Apr 21 12:32:59 2017 Yannis
** Last update Sun May 21 21:09:29 2017 Yannis
*/

#include "my_ftp.h"

t_instruct	db_instructs[] =
  {
    {"USER", i_log_in},
    {"PASS", i_pass},
    {"PASV", i_pasv},
    {"LIST", i_list},
    {"CWD", i_cwd},
    {"CDUP", i_cdup},
    {"PWD", i_pwd},
    {"RETR", i_retr},
    {"TYPE", i_type},
    {"PORT", i_port},
    {"QUIT", i_quit},
    {"STOR", i_stor},
    {"NOOP", i_noop},
    {"DELE", i_dele},
    {"HELP", i_help},
    {NULL, NULL}
  };

int	clear_cmd(t_client *client, int ret)
{
  if (client->command[0] != NULL)
    free(client->command[0]);
  if (client->command[1] != NULL)
    free(client->command[1]);
  if (client->command[2] != NULL)
    free(client->command[2]);
  client->command[0] = NULL;
  client->command[1] = NULL;
  client->command[2] = NULL;
  return (ret);
}

int	checking_for_right(t_client *client)
{
  if (client->command[0] == NULL ||
      strlen(client->command[0]) <= 0)
    return (-1);
  if (client->logged == 0
      && (strncmp(client->command[0],
		  db_instructs[0].name, strlen(db_instructs[0].name) != 0))
      && (strcmp(client->command[0],
		 db_instructs[1].name) != 0)
      && (strncmp(client->command[0],
		  db_instructs[10].name, strlen(db_instructs[10].name) != 0)))
    {
      push_message(client->fd, "Please login with USER and PASS.", 530);
      return (-1);
    }
  return (0);
}

int	exec_command(t_client *client)
{
  int	i;

  i = 0;
  if (!checking_for_right(client))
    {
      while (db_instructs[i].name != NULL)
	{
	  if (strcmp(db_instructs[i].name, client->command[0]) == 0)
	    {
	      (db_instructs[i].exec)(client);
	      return (clear_cmd(client, 0));
	    }
	  i += 1;
	}
      push_message(client->fd, NULL, 5001);
    }
  return (clear_cmd(client, -1));
}
