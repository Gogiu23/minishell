/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:28:03 by vduchi            #+#    #+#             */
/*   Updated: 2022/11/16 15:45:09 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);

char	*ft_uint_to_asc(unsigned int n);
int		ft_print_char(char c, int *count);
int		ft_print_ptr(va_list args, int *count);
int		ft_print_str(char *str, int mode, int *count);
int		ft_print_num(unsigned int u, int i, int *count);
int		ft_print_hex(unsigned int x, unsigned long long p, \
		int mode, int *count);

char	*ft_int_to_asc(int n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif
