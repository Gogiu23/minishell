/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/26 10:58:35 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

int	pipes(t_command *tokens, char *env[])
{
//	int		i = 0;
	int		res;

	res = 0;
	while (tokens) 
	{
	    printf("Command: %s\n", tokens->cmd);
	    printf("Arguments:\n");
	    char **args = tokens->args;
	    while (*args) 
		{
	        printf(" - %s\n", *args);
	        args++;
	    }
	    printf("\n");
	    tokens = tokens->next;  // Avanzar al siguiente nodo de la lista
	}
//	while (env[i])
//	{
//		printf("%s\n", env[i]);
//		i++;
//	}
	res = run_commands(tokens, env);
	printf("res: %d\n", res);
	return (0);
}
