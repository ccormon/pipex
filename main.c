/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:34:49 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/17 16:56:34 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(int code, t_cmd *cmd)
{
	if (code == 1 || code == 2 || code == 3 || code == 4)
		free(cmd->cmd1_path);
	if (code == 2 || code == 3 || code == 4)
		free(cmd->cmd2_path);
	if (code == 3 || code == 4)
		free_args(cmd->cmd1_args);
	if (code == 4)
		free_args(cmd->cmd2_args);
	exit(2);
}

void	free_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		free(args[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	if (argc != 5)
		return (EXIT_FAILURE);
	argv++;
	init_path(&cmd, argv, envp);
	pipex(&cmd, argv, envp);
	free(cmd.cmd1_path);
	free(cmd.cmd2_path);
	free_args(cmd.cmd1_args);
	free_args(cmd.cmd2_args);
	return (EXIT_SUCCESS);
}
