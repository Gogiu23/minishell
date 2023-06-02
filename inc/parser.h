/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 13:47:56 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int	parser(t_minishell *tokens, char *env[], char *string);

int		free_split(char **split, int i);
t_command	*free_len(int **len_words);
void	quotes_check(char *c, int *quotes);
int		correct_quotes(char **split, int index);
char	**free_my_split(char **split, int **len_words, int i);
int		free_split_with_index(char **split, int index, int i);

#endif
