/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 19:00:36 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/17 16:58:46 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child1(t_cmd *cmd, t_pipex *data)
{
	data->in_fd = open(data->argv[0], O_RDONLY);
	if (data->in_fd == -1)
		exit_error(0, cmd);
	dup2(data->in_fd, STDIN_FILENO);
	close(data->in_fd);
	close(data->pipe_end[0]);
	dup2(data->pipe_end[1], STDOUT_FILENO);
	close(data->pipe_end[1]);
	execve(cmd->cmd1_path, cmd->cmd1_args, data->envp);
}

void	exec_child2(t_cmd *cmd, t_pipex *data)
{
	data->out_fd = open(data->argv[3], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->out_fd == -1)
		exit_error(0, cmd);
	dup2(data->out_fd, STDOUT_FILENO);
	close(data->out_fd);
	close(data->pipe_end[1]);
	dup2(data->pipe_end[0], STDIN_FILENO);
	close(data->pipe_end[0]);
	execve(cmd->cmd2_path, cmd->cmd2_args, data->envp);
}

void	pipex(t_cmd *cmd, char **argv, char **envp)
{
	t_pipex	data;
	int		status;
	int		child1;
	int		child2;

	data.argv = argv;
	data.envp = envp;
	if (pipe(data.pipe_end) == -1)
		exit_error(0, cmd);
	child1 = fork();
	if (child1 == -1)
		exit_error(0, cmd);
	if (child1 == 0)
		exec_child1(cmd, &data);
	child2 = fork();
	if (child2 == -1)
		exit_error(0, cmd);
	if (child2 == 0)
		exec_child2(cmd, &data);
	close(data.pipe_end[0]);
	close(data.pipe_end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
