/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/03/31 21:11:17 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

void	ft_error_out(int mode, char *arg)
{
	if (mode)
		write(2, "pipex: ", 7);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (mode == 2)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
}

void	init_tokens(t_token *token)
{
	token[0].cmd = NULL;
	token[0].args = NULL;
	token[0].file = NULL;
	token[0].before = NULL;
	token[0].next = &token[1];
	token[1].cmd = NULL;
	token[1].args = NULL;
	token[1].file = NULL;
	token[1].before = &token[0];
	token[1].next = NULL;
}

int	print_error(int i, char *arg)
{
	if (!i)
		return (0);
	if (i == 1)
	{
		if (ft_printf("Number of arguments not correct!\n") == -1)
			write(2, "Printf error\n", 13);
	}
	else if (i == 2)
	{
		ft_error_out(2, arg);
		return (1);
	}
	else if (i == 3)
	{
		ft_error_out(1, arg);
		ft_error_out(0, "command not found");
	}
	else if (i == 4)
	{
		if (ft_printf("Malloc error!\n") == -1)
			write(2, "Printf error\n", 13);
	}
	return (127);
}

int	execute_token(char **argv, char *env[], t_token *token)
{
	int	res;

	if (access(argv[1], F_OK | R_OK) == -1)
	{
		print_error(2, argv[1]);
		token[0].fd = -1;
		token[0].file = NULL;
	}
	else
	{
		token[0].fd = open(argv[1], O_RDWR);
		token[0].file = argv[1];
	}
	print_error(check_command(argv[2], env, &token[0]), argv[2]);
	res = print_error(check_command(argv[3], env, &token[1]), argv[3]);
	if (res != 0)
		return (res);
//	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) != -1)
	token[1].fd = open(argv[4], O_RDWR | O_CREAT, 0644);
	if (token[1].fd == -1)
		return (print_error(2, argv[4]));
	token[1].file = argv[4];
//	printf("0:\n\tArgs 0: %s\n\tArgs 1: %s\n1:\n\tArgs 0: %s\n\tArgs 1: %s\nFd 0: %d\nFd 1: %d\nFile 0: %s\nFile 1: %s\n", token[0].args[0], token[0].args[1], token[1].args[0], token[1].args[1], token[0].fd, token[1].fd, token[0].file, token[1].file);
	res = run_command(token, env);
	return (res);
}

int	pipes(char *argv[], char *env[])
{
	(void)argv;
	(void)env;
	return (0);
}

int	main(void)
{
	printf("hola\n");
	return (0);
}
