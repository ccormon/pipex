/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:55:19 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/08 15:44:09 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": invalid command\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	exit_pipex(t_pipex *data, int code)
{
	size_t	i;

	if (data->here_doc)
		unlink(TMP_FILE);
	if (code == 0 || code >= 2)
		close (data->in_fd);
	if (code == 0 || code >= 3)
	{
		close (data->out_fd);
		free_split(data->paths);
		i = 0;
		while (i < data->nb_cmd)
		{
			free_split(data->cmd[i].args);
			free(data->cmd[i++].path);
		}
		free(data->cmd);
		free(data->pid_child);
	}
	if (code == 127)
		exit(127);
	if (code != 0)
		exit(EXIT_FAILURE);
}
