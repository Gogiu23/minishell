/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/19 13:34:48 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_token
{
	int				fd;
	char			*cmd;
	char			**args;
	struct s_token	*next;
}		t_token;

typedef struct s_command
{
	int					n;
	int					fd_in;
	int					fd_out;
	char				*cmd;
	char				**args;
	struct s_command	*next;
}	t_command;

/* ---		Check_command.c		--- */
//char	*just_the_command(char *argv);
int		check_command(char *argv, char *env[], t_token *token);

/* ---		Run_command.c		--- */
int		run_commands(t_command **token);

t_token	*free_tokens(t_token *token);
char	**free_double_ret_char(char **array, int i);
int		free_double_ret_int(char **split, int i, int out);
int		free_list(t_token **token);
int		free_new_tok(t_token *token);
int		pipes(t_command *tokens, char *env[]);

#endif
