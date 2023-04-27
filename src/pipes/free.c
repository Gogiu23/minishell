/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:42:05 by vduchi            #+#    #+#             */
/*   Updated: 2023/04/27 23:36:07 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

int	free_double_ret_int(char **split, int i, int out)
{
	if (split)
	{
		if (split[i])
			while (split[i])
				i++;
		while (--i >= 0)
			free(split[i]);
		free(split);
	}
	return (out);
}

char	**free_double_ret_char(char **array, int i)
{
	if (i > 0)
	{
		while (--i >= 0)
			free(array[i]);
		free(array);
		return (NULL);
	}
	else
	{
		while (array[i])
			i++;
		while (--i >= 0)
			free(array[i]);
		free(array);
		return (NULL);
	}
}

int	free_list(t_token **token)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = (*token);
	tmp2 = (*token)->next;
	while (!tmp2)
	{
		free(tmp1->cmd);
		free_double_ret_char(tmp1->args, 0);
		free(tmp1);
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
	free(tmp1->cmd);
	free_double_ret_char(tmp1->args, 0);
	free(tmp1);
	tmp1 = NULL;
	return (1);
}

int	free_new_tok(t_token *token)
{
	if (token->cmd != NULL)
		free(token->cmd);
	free(token);
	return (1);
}
