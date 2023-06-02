/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 16:24:05 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int argc, char *argv[], char *env[]);

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

static void	minishell(t_minishell *tokens, char *env[], char *str)
{
	char		**matrix;
//	t_minishell	*tokens;

	if (!str)
		return ;
	matrix = ft_split(str, ' ');
	if (!matrix)
	{
		free(tokens);
		perror("Malloc error #1");
		exit (1);
	}
	tokens->command = add_elem(matrix[0], matrix);
	if (!tokens->command)
	{
		free(tokens);
//		free(matrix);	// free a double pointer
		perror("Malloc error #2");
		exit (1);
	}
	pipes(tokens, env);
//	printf("Token %p\n", tokens);
}

static int	ft_readline(t_minishell *tokens, char *env[])
{
	char	*string;

	string = readline("\033[1;32m min\033[1;37"
			"mis\033[1;31mhell\033[0;0m> ");
	if (!string)
	{
		rl_clear_history();
//		ft_exit();
		return (1) ;
	}
	else if (string && string[0] == '\0')
		free(string);
	else if (string && string[0] != '\0')
	{
		add_history(string);
		parser(tokens, env, string);
		minishell(tokens, env, string);
		free (string);
	}
	string = NULL;
	return (0);
}

static t_minishell	*init_struct(char *env[])
{
	t_minishell	*tokens;

	tokens = (t_minishell *)malloc(sizeof(t_minishell));
	if (!tokens)
	{
		perror("Malloc error #3");
		exit (1);
	}
	tokens->path = ft_split(ft_find_path(env), ':');
	if (!tokens->path)
	{
		free(tokens);
		tokens = NULL;
		perror("Malloc error #4");
		exit (1);
	}
	tokens->command = NULL;
	return (tokens);
}

static void	siginthandler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
    rl_redisplay();
}

int	main(int argc, char *argv[], char *env[])
{
	t_minishell	*tokens;

	(void)argv;
	signal(SIGINT, siginthandler);
	if (argc == 1)
	{
		tokens = init_struct(env);
		while (1)
			if (ft_readline(tokens, env))
				break ;
//		system("leaks minishell");
//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
