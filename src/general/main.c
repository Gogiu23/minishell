/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/22 16:49:57 by gdominic         ###   ########.fr       */
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
	char		**args;
	char 		**matrix;
	t_command	*tokens;
	int i = 0 ;

	matrix = ft_split(str, ' ');
	while (matrix[i])
	{
		printf("matrix[%d]: %s\n", i, matrix[i]);
		i++;
	}
	printf("matrix en el final: %s\n", matrix[3]);
//	args = (char **)malloc(sizeof(char *) * 4);
//	args[0] = ft_strdup(matrix[0]);
//	args[1] = ft_strdup("test.txt");
//	args[2] = ft_strjoin("/bin/", matrix[0]);
//	args[3] = NULL;
	tokens = add_elem(args[2], args);
	pipes(tokens, env);
	if (!tokens)
		ft_putstr_error("Malloc error\n");
	args = (char **)malloc(sizeof(char *) * 4);
	args[0] = ft_strdup("wc");
	args[1] = ft_strdup("-l");
	args[2] = ft_strjoin("/usr/bin/", str);
	args[3] = NULL;
	tokens->next = add_elem(args[2], args);
	if (!tokens)
		ft_putstr_error("Malloc error\n");
	args = (char **)malloc(sizeof(char *) * 4);
	args[0] = ft_strdup("grep");
	args[1] = ft_strdup("Hello");
	args[2] = ft_strjoin("/usr/bin/", str);
	args[3] = NULL;
	tokens->next->next = add_elem(args[2], args);
	if (!tokens->next->next)
		ft_putstr_error("Malloc error\n");
	printf("Token %p\n", tokens);
}

static	void	ft_usage()
{
	write(2, "Illegal option\nusage: minishell [-help]\n", 40);
	exit (EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *env[])
{
	int		check;
	char	*string;

	check = 1;
	(void)argv;
	if (argc <= 2)
	{
		while (check)
		{
			string = readline("$> ");
			if (string[0] == '\0')
				check = 0;
			else
				minishell(string, env);
		}
	}
	else
		ft_usage();
	return (0);
}
