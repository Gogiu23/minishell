/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/26 18:19:16 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

//# include "minishell.h"
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../readline/library/include/readline/readline.h"

void	ft_exit(void);
void	ft_cd(char *path);
void	ft_echo(char *str);
void	ft_env(char *env[]);
char	**ft_unset(char *env[], char *str);
char	**ft_export(char *env[], char *new_string);

char	**free_double_pointer(char **arr, int i);

#endif
