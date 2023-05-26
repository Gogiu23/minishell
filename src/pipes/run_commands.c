/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/26 11:36:43 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

static char *get_path(char *env[], t_command *token)
{
	char *str;

	(void)env;
	str = NULL;
	token = 0;
	printf("test get_path\n");
	return (str);
}

int	run_commands(t_command *token, char *env[])
{
	int			pipe_fd[2];
	pid_t		pid;

	token->path = get_path(env, token);
	printf("entramos\n");
	if (pipe(pipe_fd) == -1)
		perror("Error_pipe\n");
	pid = fork();
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
