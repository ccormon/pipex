/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:43:13 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/04 20:47:53 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_input(t_pipex *data, char *lim_eol)
{
	char	*buffer;

	ft_putstr_fd("> ", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	if (!buffer || ft_strcmp(buffer, lim_eol))
	{
		free(buffer);
		exit_pipex(data, 0, 5);
	}
	while (buffer && !ft_strcmp(buffer, lim_eol))
	{
		ft_putstr_fd(buffer, data->in_fd);
		free(buffer);
		ft_putstr_fd("> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	if (!buffer)
	{
		free(buffer);
		exit_pipex(data, 0, 6);
	}
	free(buffer);
}

void	open_files_hd(t_pipex *data, int argc, char **argv)
{
	char	*lim_eol;

	data->in_fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->in_fd == -1)
	{
		error_msg(TMP_FILE, 2);
		exit_pipex(data, 0, 4);
	}
	lim_eol = ft_strjoin(argv[1], "\n");
	read_input(data, lim_eol);
	free(lim_eol);
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->out_fd == -1)
	{
		error_msg(argv[argc - 1], 2);
		exit_pipex(data, 0, 7);
	}
}

void	init_pipex_hd(t_pipex *data, int argc, char **argv, char **envp)
{
	open_files_hd(data, argc, argv);
}