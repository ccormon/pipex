/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:55:19 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/04 19:46:17 by ccormon          ###   ########.fr       */
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

void	error_msg(char *obj, int code)
{
	char	*msg;

	if (code == 1)
	{
		msg = ft_strjoin(obj, " : bad open\n");
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	if (code == 2)
	{
		msg = ft_strjoin(obj, " : invalid command\n");
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	free(msg);
}

void	exit_pipex(t_pipex *data, size_t cmd_no, int code)
{
	size_t	i;

	free_split(data->paths);
	i = 0;
	while (i < cmd_no)
	{
		free(data->cmd[i].path);
		free_split(data->cmd[i++].args);
	}
	free(data->cmd);
	if (code == 0 || code > 1)
	{
		free(data->pid_child);
		close(data->in_fd);
		if (code == 0 || code > 2)
			close(data->out_fd);
	}
	if (code != 0)
		exit(EXIT_FAILURE);
}
