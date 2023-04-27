/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/04/28 00:10:06 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

int	ft_error_out(int mode, char *arg)
{
	int	i;

	i = 0;
	if (mode > 0 && mode != 3)
		i = write(2, "pipex: ", 7);
	if (arg != NULL && mode != 3)
	{
		i = write(2, arg, ft_strlen(arg));
		i = write(2, ": ", 2);
	}
	if (mode == 2)
	{
		i = write(2, strerror(errno), ft_strlen(strerror(errno)));
		i = write(2, "\n", 1);
	}
	else if (mode == 3)
	{
		i = write(2, arg, ft_strlen(arg));
		i = write(2, "\n", 1);
	}
	return (i);
}

int	print_error(int i, char *arg)
{
	if (!i)
		return (0);
	if (i == 1)
	{
		if (printf("Number of arguments not correct!\n") == -1)
			i = write(2, "Printf error\n", 13);
	}
	else if (i == 2)
	{
		ft_error_out(2, arg);
		return (1);
	}
	else if (i == 3)
	{
		ft_error_out(1, arg);
		ft_error_out(3, "command not found");
	}
	else if (i == 4)
	{
		if (printf("Malloc error!\n") == -1)
			i = write(2, "Printf error\n", 13);
	}
	return (127);
}

char	**dpointer_copy(char **cmd)
{
	int		i;
	char	**res;

	i = 0;
	while (cmd[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		res[i] = ft_strdup(cmd[i]);
		if (!res[i])
			return (free_double_ret_char(res, i - 1));
	}
	res[i] = NULL;
	return (res);
}

int	add_token(t_token **token, char **cmd, int mode)
{
	t_token	*new_tok;

	new_tok = (t_token *)malloc(sizeof(t_token));
	if (!new_tok)
		return (1);
	new_tok->cmd = ft_strdup(cmd[0]);
	if (new_tok->cmd == NULL)
		return (free_new_tok(new_tok));
	new_tok->args = dpointer_copy(cmd);
	if (new_tok->args == NULL)
		return (free_new_tok(new_tok));
	new_tok->next = NULL;
	printf("Now\n");
	if (!mode)
	{
		free(*token);
		(*token) = new_tok;
	}
	else
		(*token)->next = new_tok;
	printf("End\n");
	return (0);
}

int	init_tokens(t_token **token, char ***cmd)
{
	int		i;
	int		res;
	t_token	*tmp;

	i = 1;
	tmp = *token;
	if (tmp->cmd == NULL)
		if (add_token(token, cmd[0], 0))
			return (1);
	while (cmd[i] != NULL)
	{
		res = write(1, "Here\n", 5);
//		printf("I: %d\n", i);
		tmp = *token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (add_token(&tmp, cmd[i], 1))
			return (free_list(token));
		i++;
		printf("While\n");
	}
	res = 0;
	return (res);
}

int	execute_token(char **argv, char *env[], t_token *token)
{
	int	res;

	if (access(argv[1], F_OK | R_OK) == -1)
	{
		print_error(2, argv[1]);
		token[0].fd = -1;
//		token[0].file = NULL;
	}
	else
	{
		token[0].fd = open(argv[1], O_RDWR);
//		token[0].file = argv[1];
	}
	print_error(check_command(argv[2], env, &token[0]), argv[2]);
	res = print_error(check_command(argv[3], env, &token[1]), argv[3]);
//	printf("Res: %d\n", res);
	if (res != 0)
		return (res);
//	if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) != -1)
	token[1].fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (token[1].fd == -1)
		return (print_error(2, argv[4]));
//	token[1].file = argv[4];
//	printf("0:\n\tArgs 0: %s\n\tArgs 1: %s\n1:\n\tArgs 0: %s\n\tArgs 1: %s\nFd 0: %d\nFd 1: %d\nFile 0: %s\nFile 1: %s\n", token[0].args[0], token[0].args[1], token[1].args[0], token[1].args[1], token[0].fd, token[1].fd, token[0].file, token[1].file);
	res = run_command(token, env);
	return (res);
}

int	pipes(char ***cmds)
{
//	int		res;
	t_token	*token;

//	res = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if  (!token)
		return (print_error(4, NULL));
	token->cmd = NULL;
//	token->file = NULL;
	token->args = NULL;
	token->next = NULL;
	if (init_tokens(&token, cmds))
	{
		free(token);
		return (1);
	}
//	printf("Token: %p\n", token);
	printf("Token 0:\n\tCmd: %s\n\tArgs; %s\nToken 1:\n\tCmd: %s\n\tArgs: %s\n", token->cmd, token->args[1], token->next->cmd, token->next->args[1]);
//	free(token);
//	res = check_input(argv, env, token);
//	ft_printf("Res: %d\n", res);
//	if (res != 0)
//		return (res);
//	res = run_commands(token);
//	if (res != 0)
//		return (res);
	return (0);
}
