/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/04/27 23:53:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
//	int		check;
//	char	*string;
//
//	check = 1;
//	while (check)
//	{
//		string = readline("Try this, bitch!!: ");
//		if (string[0] == '\0')
//			check = 0;
//		else
//			printf("%s\n", string);
//	}
//	return (0);
	char	***cmds;

	cmds = (char ***)malloc(sizeof(char **) * 3);
	cmds[0] = (char **)malloc(sizeof(char *) * 3);
	cmds[0][0] = ft_strdup("First command");
	cmds[0][1] = ft_strdup("First Argument");
	cmds[0][2] = NULL;
	cmds[1] = (char **)malloc(sizeof(char *) * 3);
	cmds[1][0] = ft_strdup("Second command");
	cmds[1][1] = ft_strdup("Second Argument");
	cmds[1][2] = NULL;
	cmds[2] = NULL;
	pipes(cmds);
	return (0);
}
