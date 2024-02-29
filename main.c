/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:00 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/29 18:38:24 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	cmd;

	if (argc < 5)
	{
		ft_printf("Invalid number of arguments.\n");
		return (EXIT_FAILURE);
	}
	if (!init_pipex(&cmd, argc, argv, envp))
		return (EXIT_FAILURE);
	if (!pipex(&cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	pipex(t_pipex *cmd)
{
	size_t	i;

	i = 1;
	while (i < cmd->argc - 2)
	{
		if (pipe(cmd->fd_pipe) == -1)
			return (false);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (false);
		if (cmd->pid == 0)
			exec_child(cmd);
		close(cmd->fd_pipe[0]);
		cmd->wr_pipe = cmd->fd_pipe[1];
		//close(cmd->fd_pipe[1]);
		waitpid(cmd->pid, NULL, 0);
		i++;
	}
	exec_last_child(cmd);
}

bool	init_pipex(t_pipex *cmd, int argc, char **argv, char **envp)
{
	cmd->argc = argc - 1;
	cmd->argv = argv + 1;
	while (!found_path_line(*envp))
		envp++;
	cmd->path = ft_split(*envp + 5, ':');
	if (!cmd->path)
		return (false);
	return (true);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*s;
	size_t	i;

	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	i = 0;
	while (*s1)
		s[i++] = *s1++;
	s[i++] = '/';
	while (*s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

bool	found_path_line(char *str)
{
	if (!str || ft_strlen(str) < 5)
		return (false);
	if (*str == 'P' && *(str + 1) == 'A' && *(str + 2) == 'T'
		&& *(str + 3) == 'H' && *(str + 4) == '=')
		return (true);
	return (false);
}
