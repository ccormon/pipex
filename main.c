/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:00 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/04 20:30:46 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe(t_pipex *data, size_t cmd_no)
{
	if (cmd_no == 0)
	{
		pipe(data->pipe_fd[0]);
		data->pipe_fd[1][0] = dup(data->in_fd);
		return ;
	}
	if (cmd_no == data->nb_cmd - 1)
	{
		close(data->pipe_fd[(cmd_no + 1) % 2][1]);
		close(data->pipe_fd[cmd_no % 2][0]);
		data->pipe_fd[cmd_no % 2][1] = dup(data->out_fd);
		return ;
	}
	close(data->pipe_fd[(cmd_no + 1) % 2][1]);
	close(data->pipe_fd[cmd_no % 2][0]);
	pipe(data->pipe_fd[cmd_no % 2]);
}

void	exec_cmd(t_pipex *data, char **envp, size_t cmd_no)
{
	data->pid_child[cmd_no] = fork();
	if (data->pid_child[cmd_no] == 0)
	{
		dup2(data->pipe_fd[(cmd_no + 1) % 2][0], STDIN_FILENO);
		close(data->pipe_fd[(cmd_no + 1) % 2][0]);
		dup2(data->pipe_fd[cmd_no % 2][1], STDOUT_FILENO);
		close(data->pipe_fd[cmd_no % 2][1]);
		execve(data->cmd[cmd_no].path, data->cmd[cmd_no].args, envp);
	}
}

void	wait_childs(t_pipex *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_cmd)
		waitpid(data->pid_child[i++], NULL, 0);
}

void	pipex(t_pipex *data, char **envp)
{
	size_t	cmd_no;

	cmd_no = 0;
	while (cmd_no < data->nb_cmd)
	{
		ft_pipe(data, cmd_no);
		exec_cmd(data, envp, cmd_no);
		cmd_no++;
	}
	close(data->pipe_fd[(cmd_no + 1) % 2][1]);
	close(data->pipe_fd[cmd_no % 2][0]);
	wait_childs(data);
	exit_pipex(data, data->nb_cmd, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_putstr_fd("Wrong number of arguments.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data.here_doc = false;
	if (ft_strcmp(argv[1], "here_doc"))
		data.here_doc = true;
	if (data.here_doc && argc < 6)
	{
		ft_putstr_fd("Wrong number of arguments.\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (data.here_doc)
		init_pipex_hd(data, argc - 1, argv + 1, envp);
	else
		init_pipex(&data, argc - 1, argv + 1, envp);
	pipex(&data, envp);
	return (EXIT_SUCCESS);
}
