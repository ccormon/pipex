/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:00:25 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/09 15:30:37 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	found_path_line(char *str)
{
	if (!str || !(*str) || ft_strlen(str) < 5)
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

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin_path(paths[i++], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

void	open_files(t_pipex *data, int argc, char **argv)
{
	data->in_fd = open(argv[0], O_RDONLY);
	if (data->in_fd == -1)
	{
		perror(argv[0]);
		exit_pipex(data, 1);
	}
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->out_fd == -1)
	{
		perror(argv[argc - 1]);
		exit_pipex(data, 2);
	}
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	size_t	i;

	if (data->here_doc)
		open_files_hd(data, argc, argv++);
	else
		open_files(data, argc, argv);
	while (envp && *envp && !found_path_line(*envp))
		envp++;
	if (!envp || !(*envp))
		exit_pipex(data, 2);
	data->nb_cmd = argc - 2 - data->here_doc;
	data->cmd = malloc(data->nb_cmd * sizeof(t_cmd));
	data->paths = ft_split(*envp + 5, ':');
	i = 0;
	while (argv[i + 2])
	{
		data->cmd[i].args = ft_split(argv[i + 1], ' ');
		if (!data->cmd[i].args)
			data->cmd[i].path = NULL;
		else
			data->cmd[i].path = ft_which(data->cmd[i].args[0], data->paths);
		i++;
	}
	data->pid_child = malloc(data->nb_cmd * sizeof(int));
}
