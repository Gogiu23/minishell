/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 21:55:14 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

char *ft_find_path(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

static int is_builtin(char *str)
{
	if (!ft_strncmp("echo", str, 4))
		return (1);
	else if (!ft_strncmp("cd", str, 2))
		return (2);
	else if (!ft_strncmp("pwd", str, 3))
		return (3);
	else if (!ft_strncmp("export", str, 6))
		return (4);
	else if (!ft_strncmp("unset", str, 5))
		return (5);
	else if (!ft_strncmp("env", str, 3))
		return (6);
	else if (!ft_strncmp("exit", str, 4))
		return (7);
	return (0);
}

int check_command(t_minishell *cmd, char **env)
{
	(void)env;
	char	*str = cmd->command->args[0];
	if (is_builtin(str) == 0)
		return (0);
	return (1);
}

int	run_commands(t_command *token, char *env[])
{
	int			pipe_fd[2];
	pid_t		pid;

	if (fork() == 0)
		printf("%p\n", token);
	execve("/bin/cat", token->args, env);
	if (pipe(pipe_fd) == -1)
		perror("Error_pipe\n");
	pid = fork();
	printf("pid: %d\n", pid);
	if (pid < 0)
		perror("fork");
//	while (token)
//	{
//		if (fork() == 0)
//		{
//			printf("Child no. %d\n", getpid());
//			if (execve(token->cmd, token->args, env) == -1)
//			{
//				perror(token->cmd);
//				exit(127);
//			}
//		}
//		wait(NULL);
//		token = token->next;
//	}
//	token = NULL;
	return (0);
}
