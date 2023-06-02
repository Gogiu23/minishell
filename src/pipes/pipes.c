/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 11:22:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

int	pipes(t_minishell *tokens, char *env[])
{
	int			res;
	t_command	*tmp;

	tmp = tokens->command;
	res = 0;
	while (tmp)
	{
	    printf("Command: %s\n", tmp->cmd);
	    printf("Arguments:\n");
	    char **args = tmp->args;
	    while (*args) 
		{
	        printf(" - %s\n", *args);
	        args++;
	    }
//	    printf("\n");
	    tmp = tmp->next;  // Avanzar al siguiente nodo de la lista
	}
	if (check_command(tokens, env) == 0)
		res = run_commands(tokens->command, env);
	else
		ft_putstr_error("BUILTIN pending manage\n");
//	printf("res: %d\n", res);
	return (0);
}
