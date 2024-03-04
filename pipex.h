/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/04 20:35:19 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft/libft.h"

# define TMP_FILE "tmp"

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_pipex
{
	bool	here_doc;
	t_cmd	*cmd;
	size_t	nb_cmd;
	char	**paths;
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2][2];
	int		*pid_child;
}	t_pipex;

void	pipex(t_pipex *data, char **envp);
void	ft_pipe(t_pipex *data, size_t cmd_no);
void	exec_cmd(t_pipex *data, char **envp, size_t cmd_no);
// init_pipex
void	init_pipex(t_pipex *data, int argc, char **argv, char **envp);
bool	found_path_line(char *str);
char	*ft_strjoin_path(char *path, char *cmd);
char	*ft_which(char *cmd, char **paths);
void	open_files(t_pipex *data, int argc, char **argv);
// init_pipex_hd
// exit_pipex
void	exit_pipex(t_pipex *data, size_t cmd_no, int code);
void	free_split(char **split);
void	error_msg(char *obj, int code);

#endif
