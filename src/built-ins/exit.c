/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:03:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 13:19:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void	ft_exit(void)
{
//	printf("exit\n");
	write(1, "\rexit", 5);
//	rl_replace_line("exit", 0);
//	rl_on_new_line();
//	rl_redisplay();
	exit(0);
}
