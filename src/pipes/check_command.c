/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:07:09 by vduchi            #+#    #+#             */
/*   Updated: 2023/03/30 15:46:36 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

char	**update_args(char *exec, char **args)
{
	int		i;
	char	**res;

	i = 0;
	while(args[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		if (i == 0)
			res[i] = ft_strdup(exec);
		else
			res[i] = ft_strdup(args[i]);
		if (!res[i])
			return (free_double_ret_char(res, i));
	}
	res[i] = NULL;
	return (res);
}

int	take_path(char *split, char *input, char **args, t_token *token)
{
	char	*exec;

	exec = NULL;
	if (!ft_strncmp(input, "exit", 4))
		exec = ft_strdup("exit");
	else
	{
		if (input[0] != '/')
			exec = ft_strjoin(ft_strjoin(split, "/"), input);
		else
			exec = ft_strjoin(split, input);
		if (!exec)
			return (-1);
		if (access(exec, F_OK) == -1)
		{
			free(exec);
			exec = NULL;
			return (0);
		}
	}
	token->cmd = exec; 
	token->args = update_args(exec, args);
	if (!token->args)
		return (free_double_ret_int(args, 0, 3));
	free_double_ret_char(args, 0);
	exec = NULL;
//	ft_printf("Cmd: %s\nArg1: %s\nArg2: %s\n", token->cmd, token->args[0], token->args[1]);
	return (1);
}

int	count_args(char *argv)
{
	int	i;
	int	words;
	int	sin;
	int	dob;

	i = -1;
	sin = 0;
	dob = 0;
	words = 0;
//	printf("Argv: %s\n", argv);
	while (argv[++i])
	{
		if (i > 0 && (argv[i - 1] == '\'' || argv[i - 1] == '\"') && sin == 0 && dob == 0)
		{
			words += 1;
//			printf("Hyphen\n");
		}
		else if ((argv[i] == ' ' && sin == 0 && dob == 0) || argv[i + 1] == '\0')
		{
			words += 1;
//			printf("Space or end string\n");
		}
		else if (argv[i] == '\'' && sin == 0)
			sin = 1;
		else if (argv[i] == '\"' && dob == 0)
			dob = 1;
		else if (argv[i] == '\'' && sin == 1)
			sin = 0;
		else if (argv[i] == '\"' && dob == 1)
			dob = 0;
	}
//	printf("Words: %d\n", words);
	return (words);
}

char	**correct_accents(char **res)
{
	int		i;
	int		k;
	int		sin;
	char	*t1;
	char	*t2;

	i = -1;
	sin = 0;
	while (res[++i])
	{
		k = -1;
//		printf("Before: %s\n", res[i]);
		while(res[i][++k])
		{
//			printf("Char: %c\tK: %d\n", res[i][k], k);
			if (res[i][k] == '\'' || res[i][k] == '\"')
			{
				if (sin == 0)
				{
					t1 = ft_substr(res[i], 0, k);
					if (!t1)
						return (NULL);
					t2 = ft_substr(res[i], k, ft_strlen(res[i]) - k);
					if (!t2)
					{
						free(t1);
						return (NULL);
					}
					sin++;
				}
				else
				{
					t1 = ft_substr(res[i], 0, k + 1);
					if (!t1)
						return (NULL);
					t2 = ft_substr(res[i], k + 1, ft_strlen(res[i]) - k);
					if (!t2)
					{
						free(t1);
						return (NULL);
					}
//					printf("T1: %s\tT2: %s\n", t1, t2);
					sin = 0;
				}
//				printf("Char in k: %c\tChar in k + 1: %c\n", res[i][k], res[i][k + 1]);
//				printf("T2: %s\n", t2);
				free(res[i]);
//				char	*temp1;
//				temp1 = ft_strjoin("\"", t2);
//				printf("Temp1: %s\n", temp1);
				res[i] = ft_strjoin(t1, ft_strjoin("\"", t2));
//				printf("Res: %s\n", res[i]);
				if (!res[i])
				{
					free(t1);
					return (NULL);
				}
				k++;
			}
		}
//		printf("1\n");
	}
	return (res);
}

char	**command_split(char *argv)
{
	int		i;
	int		end;
	int		sin;
	int		dob;
	int		word;
	int		start;
	char	**res;

	i = -1;
	end = 0;
	sin = 0;
	dob = 0;
	word = -1;
	start = 0;
	res = malloc(sizeof(char *) * (count_args(argv) + 1));
	while (argv[++i])
	{
		if ((argv[i] == ' ' && sin == 0 && dob == 0))
		{
			end = i - start;
//			printf("1: %d\t%d\n", start, end);
//			int	a = start;
//			int b = end;
//			while (a < b)
//			{
//				printf("%c", argv[a]);
//				a++;
//			}
//			printf("\n");
			res[++word] = ft_substr(&argv[0], start, end);
			start = i + 1;
		}
		else if (argv[i] == '\'' && sin == 0)
			sin = 1;
		else if (argv[i] == '\"' && dob == 0)
			dob = 1;
		else if (argv[i] == '\'' && sin == 1)
			sin = 0;
		else if (argv[i] == '\"' && dob == 1)
			dob = 0;
		if (argv[i + 1] == '\0')
		{
//			printf("Last: %c\n", argv[i]);
//			while(argv[start] == '\"' || argv[start] == '\'')
//				start++;
//			while(argv[i] == '\"' || argv[i] == '\'')
//			{
//				printf("%c", argv[i]);
//				i--;
//			}
//			printf("\nI: %d\n", i);
			end = i - start + 1;
//			printf("2: %d\t%d\n", start, end);
//			int	a = start;
//			int b = i + 1;
//			while (a < b)
//			{
//				printf("%c", argv[a]);
//				a++;
//			}
//			printf("\nStart: %c\n", argv[start]);
			res[++word] = ft_substr(&argv[0], start, end);
//			start = i;
			break;
		}
//		if (i > 0 && (argv[i] == '\'' || argv[i] == '\"') && sin == 0 && dob == 0)
//		{
//			if (argv[i - 2] == '\"' || argv[i - 2] == '\'')
//				end = i - start - 1;
//			else
//				end = i - start;
//		}
	}
//	while (!argv[++i])
//	{
//		if (argv[i] == ' ' && sin == 0 && dob == 0)
//			ft_strlcpy(res[++word], &argv[start], i - start);
//
//	}
	res[++word] = NULL;
	correct_accents(res);
//	if (res[1] == NULL)
//		printf("Argv 0: %s\nArgv 1: %s\n", res[0], res[1]);
//	else
//		printf("Argv 0: %s\nArgv 1: %s\nArgv 2: %s\n", res[0], res[1], res[2]);
	return (res);
}

int	execute_path(char **split, char *argv, t_token *token)
{
	int		i;
	int		res;
	char	**args;
//	char	**test;

	i = -1;
	args = command_split(argv);	
//	args = ft_split(argv, ' ');
	if (!args)
		return (4);
	while (split[++i])
	{
		res = take_path(split[i], args[0], args, token);
		if (res == -1)
			return (free_double_ret_int(split, i, 4));
		else if (res == 0)
			continue ;
		else
			break;
	}
	if (!split[i])
		return (free_double_ret_int(split, i, 3));
	return (free_double_ret_int(split, i, 0));
}

int	check_command(char *argv, char *env[], t_token *token)
{
	int		i;
	char	**split;

	i = -1;
	split = NULL;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' &&  env[i][3] == 'H')
		{
			split = ft_split(ft_substr(env[i], 5, ft_strlen(env[i]) - 5), ':');
			break;
		}
	}
	if (!split)
		return (4);
	return (execute_path(split, argv, token));
}
