/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 05:14:22 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

static char *ft_find_path(char *env[])
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

static void get_path(char *env[], t_command *token)
{
	token = (t_command *)malloc(sizeof(t_command));
	if (!token)
		exit (EXIT_FAILURE);
	printf("test get_path\n");
	token->path = ft_find_path(env);
	token->next = NULL;
	printf("token->path: %s\n", token->path);
}

int	run_commands(t_command *token, char *env[])
{
	int			pipe_fd[2];
	pid_t		pid;

	get_path(env, token);
 	execve("/bin/cat", token->args, env);
	if (pipe(pipe_fd) == -1)
		perror("Error_pipe\n");
	pid = fork();
//	exit (0);
	printf("pid: %d\n", pid);
	if (pid < 0)
		perror("fork");
	while (token)
	{
		if (fork() != 0)
		{
			printf("Child no. %d\n", getpid());
			if (execve(token->cmd, token->args, env) == -1)
			{
				perror(token->cmd);
				exit(127);
			}
		}
		wait(NULL);
		token = token->next;
	}
	token = NULL;
	return (0);
}
