/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/19 18:18:06 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

int	run_commands(t_command **token)
{
	int			status;
	int			p[2];
	t_command	*temp;

	status = 0;
	temp = (*token);
	if (pipe(p) == -1)
		return (2);
	while (temp != NULL)
	{
		if (fork() == 0)
		{
			printf("Child no. %d\n", getpid());
			if (execve(temp->cmd, temp->args, NULL) == -1)
			{
				perror(temp->cmd);
				exit(127);
			}
		}
		wait(&status);
		temp = temp->next;
	}
	temp = NULL;
	return (0);
}
