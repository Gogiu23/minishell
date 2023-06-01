/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/01 17:49:37 by gdominic         ###   ########.fr       */
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

static void minishell(char *str, char **env)
{
	char 		**matrix;
	t_minishell	*tokens;
//	int i = 0 ;

	if (!str)
		return ;
	matrix = ft_split(str, ' ');
//	while (matrix[i])
//	{
//		printf("matrix[%d]: %s\n", i, matrix[i]);
//		i++;
//	}
//	printf("matrix en el final: %s\n", matrix[3]);
	tokens = malloc(sizeof(t_minishell));
	tokens->path = ft_split(ft_find_path(env), ':');
//	ft_printer(tokens, env);
	tokens->command = add_elem(matrix[0], matrix);
	if (!tokens)
		ft_putstr_error("Malloc error\n");
//	tokens->command->next = add_elem(matrix[1], matrix);
//	if (!tokens)
//		ft_putstr_error("Malloc error\n");
//	tokens->command->next->next = add_elem(matrix[2], matrix);
//	if (!tokens->next->next)
//		ft_putstr_error("Malloc error\n");
	pipes(tokens, env);
	printf("Token %p\n", tokens);
}

static void sigintHandler(int sig)
{
	(void)sig;
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
			signal(SIGINT, sigintHandler);
			string = readline("\033[1;32m min\033[1;37mis\033[1;31mhell\033[0;0m> ");
			if (string[0] != '\0')
			{
				minishell(string, env);
				free (string);
			}
//			free (string);
		}
	}
	return (0);
}
