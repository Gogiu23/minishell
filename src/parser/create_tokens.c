/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/31 16:20:21 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_command	*load_commands(char **split)
{
	int	i;
	int	after_pipe;

	i = -1;
	while (split[++i])
	{
		if (i == 0 && split[i][0] == '|' && split[i][1] == '\0')
			return (NULL); // Qui si dovrebbe ritornare un errore e non eseguire nessun comando
	}
}
