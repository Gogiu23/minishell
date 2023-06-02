/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 11:18:22 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*add_elem(char *cmd, char **args)
{
	t_command	*tok;

	tok = (t_command *)malloc(sizeof(t_command));
	if (!tok)
		return (NULL);
	tok->cmd = cmd;
	tok->args = args;
	tok->next = NULL;
	return (tok);
}

static	void	minishell(char *str, char **env)
{
	char		**matrix;
	t_minishell	*tokens;

	if (!str)
		return ;
	matrix = ft_split(str, ' ');
	tokens = malloc(sizeof(t_minishell));
	tokens->path = ft_split(ft_find_path(env), ':');
	tokens->command = add_elem(matrix[0], matrix);
	if (!tokens)
		ft_putstr_error("Malloc error\n");
	pipes(tokens, env);
//	printf("Token %p\n", tokens);
}

static void	siginthandler(int sig)
{
	printf("\nSig: %d\n", sig);
	exit (0);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*string;

	(void)argv;
	if (argc == 1)
	{
		while (SIGINT)
		{
			signal(SIGINT, siginthandler);
			string = readline("\033[1;32m min\033[1;37"
					"mis\033[1;31mhell\033[0;0m> ");
			if (!string)
				break ;
			if (string[0] != '\0')
			{
				minishell(string, env);
				free (string);
			}
		}
	}
	return (0);
}
