/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 13:31:18 by vduchi           ###   ########.fr       */
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

int check_command(t_minishell *cmd)
{
	char	*str = cmd->command->args[0];
	if (is_builtin(str) == 0)
		return (0);
	return (1);
}

static	int	is_cmd(t_command *token)
{
	(void)token;
	if (ft_strncmp(token->cmd, "cat", ft_strlen(token->cmd)) != 0)
		return (-2);
	if (access("/bin/cat", F_OK | X_OK) == 0)
		return (0);
	perror("Access invalid");
	return (-1);
}
		
int	run_commands(t_command *token, char *env[])
{
	pid_t	pid;
//	int		exit_status;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (is_cmd(token) == 0)
			execve("/bin/cat", token->args, env);
		printf("errno: %d\n", errno);
//		perror("Error execve");
		exit (0);
	}
	else if (pid > 0)
	{
		write (1, "Before\n", 7);
		printf("Return value %d\n", waitpid(pid, &status, 0));
		write (1, "After\n", 6);
//		if (WIFEXITED(status))
//		{
//			exit_status = WEXITSTATUS(status);
//			printf("Codice uscita child: %d\n", exit_status);
//		}
	}
	else
	{
		perror("fork");
		return(1);
	}
	return (0);
}
