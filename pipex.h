/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:39 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/29 18:12:29 by ccormon          ###   ########.fr       */
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

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**path;
	int		wr_pipe;
	int		fd_pipe[2];
	int		pid;
}	t_pipex;

#endif
