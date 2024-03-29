/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:43:13 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/09 15:25:06 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_input(t_pipex *data, char *lim_eol)
{
	char	*buffer;

	ft_putstr_fd("> ", STDOUT_FILENO);
	buffer = get_next_line(STDIN_FILENO);
	while (buffer && !ft_strcmp(buffer, lim_eol))
	{
		ft_putstr_fd(buffer, data->in_fd);
		free(buffer);
		ft_putstr_fd("> ", STDOUT_FILENO);
		buffer = get_next_line(STDIN_FILENO);
	}
	free(buffer);
}

void	open_files_hd(t_pipex *data, int argc, char **argv)
{
	char	*lim_eol;

	data->in_fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->in_fd == -1)
	{
		perror(TMP_FILE);
		exit_pipex(data, 1);
	}
	lim_eol = ft_strjoin(argv[1], "\n");
	read_input(data, lim_eol);
	free(lim_eol);
	close(data->in_fd);
	data->in_fd = open(TMP_FILE, O_RDONLY);
	if (data->in_fd == -1)
	{
		perror(TMP_FILE);
		exit_pipex(data, 1);
	}
	data->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->out_fd == -1)
	{
		perror(argv[argc - 1]);
		exit_pipex(data, 2);
	}
}
