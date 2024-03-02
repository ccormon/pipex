/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:00:25 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/02 15:37:02 by ccormon          ###   ########.fr       */
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
	size_t	j;

	cmd_path = malloc((ft_strlen(path) + ft_strlen(cmd) + 2) * sizeof(char));
	i = 0;
	while (path[i])
	{
		cmd_path[i] = path[i];
		i++;
	}
	cmd_path[i] = '/';
	j = 0;
	while (cmd[j])
	{
		cmd_path[i + j] = cmd[j];
		j++;
	}
	cmd_path[i + j] = '\0';
	return (cmd_path);
}

char	*ft_which(char *cmd, char **paths)
{
	char	*cmd_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin_path(paths[i++], cmd_path);
		if (access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
	}
	exit(EXIT_FAILURE);
}

void	open_files(t_pipex *data, int argc, char **argv)
{
	data->in_fd = open(argv[0], O_RDONLY);
	if (data->in_fd == -1)
		exit(EXIT_FAILURE);
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->out_fd == -1)
		exit(EXIT_FAILURE);
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	size_t	i;

	while (!found_path_line(*envp))
		envp++;
	data->paths = ft_split(*envp + 5, ':');
	data->nb_cmd = argc - 2;
	data->cmd = malloc((data->nb_cmd) * sizeof(t_cmd));
	i = 0;
	while (argv[i + 2])
	{
		data->cmd[i].args = ft_split(argv[i++ + 1], ' ');
		data->cmd[i].path = ft_which(data->cmd->args[0], data->paths);
	}
	open_files(data, argc, argv);
}

