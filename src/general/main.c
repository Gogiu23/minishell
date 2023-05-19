/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/19 19:39:36 by gdominic         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *env[])
{
	int		check;
	char	*string;

	check = 1;
	while (check)
	{
		string = readline("$> ");
		if (string[0] == '\0')
			check = 0;
		else
			printf("%s\n", string);
	}
//	return (0);
//	char	***cmds;
	char		**args;
	t_command	*tokens;

	if (argc > 1)
		return (0);
	(void)argv;
	args = (char **)malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("cat");
	args[1] = ft_strdup("test.txt");
	args[2] = NULL;
	tokens = add_elem("/bin/cat", args);
	pipes(tokens, env);
	if (!tokens)
	{
		printf("Malloc error\n");
		return (2);
	}
	args = (char **)malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("wc");
	args[1] = ft_strdup("-l");
	args[2] = NULL;
	tokens->next = add_elem("/usr/bin/wc", args);
	if (!tokens)
	{
		printf("Malloc error\n");
		return (2);
	}
	args = (char **)malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("grep");
	args[1] = ft_strdup("Hello");
	args[2] = NULL;
	tokens->next->next = add_elem("/usr/bin/grep", args);
	if (!tokens->next->next)
	{
		printf("Malloc error\n");
		return (2);
	}
	printf("Token %p\n", tokens);
//	cmds = (char ***)malloc(sizeof(char **) * 3);
//	cmds[0] = (char **)malloc(sizeof(char *) * 3);
//	cmds[0][0] = ft_strdup("cat");
//	cmds[0][1] = ft_strdup("First Argument");
//	cmds[0][2] = NULL;
//	cmds[1] = (char **)malloc(sizeof(char *) * 3);
//	cmds[1][0] = ft_strdup("Second command");
//	cmds[1][1] = ft_strdup("Second Argument");
//	cmds[1][2] = NULL;
//	cmds[2] = NULL;
	pipes(tokens, env);
//	free(cmds[0][0]);
//	free(cmds[0][1]);
//	free(cmds[1][0]);
//	free(cmds[1][1]);
//	free(cmds[0]);
//	free(cmds[1]);
//	free(cmds);
//	printf("Main\n");
//	cmds = NULL;
//	printf("Cmds: \n\t%s\n\t%s\n", cmds[0][0], cmds[0][1]);
//	free(cmds[0][0]);
//	cmds[0][0] = ft_strdup("My first test");
//	printf("Cmds: \n\t%s\n\t%s\n", cmds[0][0], cmds[0][1]);
	return (0);
}
