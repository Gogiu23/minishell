/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/17 19:53:27 by vduchi           ###   ########.fr       */
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
			return (free_double_ret_char(res, i));
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
	if (!mode)
	{
		free(*token);
		(*token) = new_tok;
	}
	else
		(*token)->next = new_tok;
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
		tmp = *token;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (add_token(&tmp, cmd[i], 1))
			return (free_list(token));
		i++;
	}
	res = 0;
	return (res);
}

/*
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
		print_error(check_command(argv[2], env, &token[0]), argv[2]);
	}
	res = print_error(check_command(argv[3], env, &token[1]), argv[3]);
	if (res != 0)
		return (res);
	token[1].fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (token[1].fd == -1)
		return (print_error(2, argv[4]));
	res = run_command(token, env);
	return (res);
}
*/

int	change_command(t_token **token, char **paths, char *correct_path)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(correct_path, "/");
	if (!tmp1)
		return (free_double_ret_int(paths, 0, 4));
	tmp2 = ft_strjoin(tmp1, (*token)->cmd);
	if (!tmp2)
	{
		free(tmp1);
		tmp1 = NULL;
		return (free_double_ret_int(paths, 0, 4));
	}
	free((*token)->cmd);
	(*token)->cmd = tmp2;
	free(tmp1);
	tmp1 = NULL;
	tmp2 = NULL;
	free((*token)->args[0]);
	(*token)->args[0] = NULL;
	(*token)->args[0] = ft_strdup((*token)->cmd);
	if ((*token)->args[0] == NULL)
		return (free_double_ret_int(paths, 0, 4));
	return (free_double_ret_int(paths, 0, 0));
}

int	check_path(t_token **token, char *path)
{
	int		out;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(path, "/");
	if (!tmp1)
		return (2);
	tmp2 = ft_strjoin(tmp1, (*token)->cmd);
	if (!tmp2)
	{
		free(tmp1);
		return (2);
	}
	if (access(tmp2, F_OK | X_OK) == -1)
		out = 1;
	else
		out = 0;
	free(tmp1);
	free(tmp2);
	return (out);
}

int	check_tokens(t_token **token, char *env[])
{
	int		i;
	char	**paths;

	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H') 
			break ;
	if ((*token)->cmd[0] == '/')
		if (access((*token)->cmd, F_OK | X_OK) == -1)
			return (print_error(3, (*token)->cmd));
	paths = ft_split(env[i], ':');
	if (!paths)
		return (1);
	i = -1;
	while (paths[++i])
	{
		if (!check_path(token, paths[i]))
			break;
		else if (check_path(token, paths[i]) == 2)
			return (print_error(free_double_ret_int(paths, 0, 4), NULL));
	}
//	printf("Paths %s\n", paths[i]);
	if (!paths[i])
		return (print_error(free_double_ret_int(paths, 0, 3), (*token)->cmd));
	return (change_command(token, paths, paths[i]));
}

int	pipes(t_command *tokens, char *env[])
{
	int		res;
//	t_token	*token;

	res = 0;
	(void)env;
//	token = (t_token *)malloc(sizeof(t_token));
//	if  (!token)
//		return (print_error(4, NULL));
//	token->cmd = NULL;
//	token->args = NULL;
//	token->next = NULL;
//	res = init_tokens(&token, cmds);
//	if (res)
//		return (free_list(&token));
//	res = check_tokens(&token, env);
//	if (res)
//		return (free_list(&token));
//	printf("Token 0:\n\tCmd: \t%s\n\tArgs: \t%s\n\t\t%s\nToken 1:\n\tCmd: \t%s\n\tArgs: \t%s\n\t\t%s\n", token->cmd, token->args[0], token->args[1], token->next->cmd, token->next->args[0], token->next->args[1]);
	res = run_commands(&tokens);
//	free_list(&token);
	return (0);
}
