/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:12:32 by vduchi            #+#    #+#             */
/*   Updated: 2023/04/24 20:14:31 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	int		check;
	char	*string;

	check = 1;
	while (check)
	{
		string = readline("Try this, bitch!!: ");
		if (string[0] == '\0')
			check = 0;
		else
			printf("%s\n", string);
	}
	return (0);
}
