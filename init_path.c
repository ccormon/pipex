/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:23:04 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/17 17:00:14 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	found_path_line(char *str)
{
	if (!str || ft_strlen(str) < 5)
		return (false);
	if (*str == 'P' && *(str + 1) == 'A' && *(str + 2) == 'T'
		&& *(str + 3) == 'H' && *(str + 4) == '=')
		return (true);
	return (false);
}

char	*init_path_cmd(char **path, char *cmd_argv)
{
	char	*path_test;

	if (!path || !(*path))
		return (NULL);
	path_test = ft_strjoin_path(*path, cmd_argv);
	while (path && path_test)
	{
		if (access(path_test, X_OK) == 0)
			return (path_test);
		free(path_test);
		path++;
		path_test = ft_strjoin_path(*path, cmd_argv);
	}
	free(path_test);
	return (NULL);
}

void	init_path(t_cmd *cmd, char **argv, char **envp)
{
	char	**path;

	while (!found_path_line(*envp))
		envp++;
	if (!envp || !(*envp))
		exit_error(0, cmd);
	cmd->cmd1_args = ft_split(argv[1], ' ');
	if (!cmd->cmd1_args)
		exit_error(1, cmd);
	cmd->cmd2_args = ft_split(argv[2], ' ');
	if (!cmd->cmd2_args)
		exit_error(2, cmd);
	path = ft_split(*envp + 5, ':');
	if (!path)
	{
		free_args(path);
		exit_error(2, cmd);
	}
	cmd->cmd1_path = init_path_cmd(path, cmd->cmd1_args[0]);
	if (!cmd->cmd1_path)
		exit_error(3, cmd);
	cmd->cmd2_path = init_path_cmd(path, cmd->cmd2_args[0]);
	if (!cmd->cmd2_path)
		exit_error(4, cmd);
	free_args(path);
}
