/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:00 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/02 15:39:14 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe(t_pipex *data, size_t cmd_no)
{
	if (cmd_no == 0)
	{
		pipe(data->pipe_fd[0]);

		return ;
	}
	if (cmd_no == data->nb_cmd - 1)
	{
		return ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;
	size_t	i;

	if (argc < 5)
		return (EXIT_FAILURE);
	init_pipex(&data, --argc, ++argv, envp);
	i = 0;
	while (i < argc - 3)
	{
		ft_pipe(&data, i);
		exec_cmd(&data);
		i++;
	}
	close_fd(&data);
	wait_child(&data);
	end_pipex(&data);
	return (EXIT_SUCCESS);
}
