/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/29 18:53:35 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "built-ins.h"

int	free_split(char **split, int i);
char	**free_len(int **len_words);
void	quotes_check(char *c, int *quotes);
char	**free_my_split(char **split, int **len_words, int i);

#endif
