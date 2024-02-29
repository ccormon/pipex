/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:35:13 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/17 17:00:01 by ccormon          ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
}	t_cmd;

typedef struct s_pipex
{
	char	**argv;
	char	**envp;
	int		pipe_end[2];
	int		in_fd;
	int		out_fd;
}	t_pipex;

// libft
char	**ft_split(char const *s, char c);
char	*ft_strjoin_path(char *s1, char *s2);
size_t	ft_strlen(const char *s);
// init_path
void	init_path(t_cmd *cmd, char **argv, char **envp);
bool	found_path_line(char *str);
char	*init_path_cmd(char **path, char *cmd_argv);
// pipex
void	pipex(t_cmd *cmd, char **argv, char **envp);
void	exec_child1(t_cmd *cmd, t_pipex *data);
void	exec_child2(t_cmd *cmd, t_pipex *data);
// errors
void	exit_error(int code, t_cmd *cmd);
void	free_args(char **args);

#endif
