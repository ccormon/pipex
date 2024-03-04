/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:00:25 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/04 19:52:54 by ccormon          ###   ########.fr       */
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

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*cmd_path;
	size_t	i;

	cmd_path = malloc((ft_strlen(path) + ft_strlen(cmd) + 2) * sizeof(char));
	i = 0;
	while (*path)
		cmd_path[i++] = *path++;
	cmd_path[i++] = '/';
	while (*cmd)
		cmd_path[i++] = *cmd++;
	cmd_path[i] = '\0';
	return (cmd_path);
}

char	*ft_which(char *cmd, char **paths)
{
	char	*cmd_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin_path(paths[i++], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	error_msg(cmd, 1);
	return (NULL);
}

void	open_files(t_pipex *data, int argc, char **argv)
{
	data->in_fd = open(argv[0], O_RDONLY);
	if (data->in_fd == -1)
	{
		error_msg(argv[0], 2);
		exit_pipex(data, data->nb_cmd, 2);
	}
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->out_fd == -1)
	{
		error_msg(argv[argc - 1], 2);
		exit_pipex(data, data->nb_cmd, 3);
	}
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	size_t	i;

	while (!found_path_line(*envp))
		envp++;
	data->paths = ft_split(*envp + 5, ':');
	data->cmd = malloc((argc - 2) * sizeof(t_cmd));
	i = 0;
	while (argv[i + 2])
	{
		data->cmd[i].args = ft_split(argv[i + 1], ' ');
		data->cmd[i].path = ft_which(data->cmd[i].args[0], data->paths);
		if (!data->cmd[i++].path)
		{
			error_msg(data->cmd->args[0], 1);
			exit_pipex(data, i, 1);
		}
	}
	data->nb_cmd = i;
	data->pid_child = malloc(data->nb_cmd * sizeof(int));
	open_files(data, argc, argv);
}

