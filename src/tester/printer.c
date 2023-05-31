/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:30:16 by gdominic          #+#    #+#             */
/*   Updated: 2023/05/30 20:15:39 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

void	ft_printer(t_minishell *command, char **env)
{
	char	**paths;

	(void)env;
	paths = command->path;
	printf("Paths:\n");
	while (*paths)
	{
		printf("-%s\n", *paths);
		paths++;
	}
	printf("\n");
}
