/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:55:19 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/05 11:42:59 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	exit_pipex(t_pipex *data, size_t nb_cmd, int code)
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
		while (i < nb_cmd)
		{
			free_split(data->cmd[i].args);
			free(data->cmd[i++].path);
		}
	}
	if (code == 0)
		free(data->pid_child);
	if (code != 0)
		exit(EXIT_FAILURE);
}
