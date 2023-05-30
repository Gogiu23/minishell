/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 16:54:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "built-ins.h"

int		free_split(char **split, int i);
char	**free_len(int **len_words);
void	quotes_check(char *c, int *quotes);
int		correct_quotes(char **split, int index);
char	**free_my_split(char **split, int **len_words, int i);
int		free_split_with_index(char **split, int index, int i);

#endif
