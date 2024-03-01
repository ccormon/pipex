/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:55:00 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/01 13:35:32 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	found_path_line(char *str)
{
	if (!str || ft_strlen(str) < 5)
		return (false);
	if (*str == 'P' && *(str + 1) == 'A' && *(str + 2) == 'T'
		&& *(str + 3) == 'H' && *(str + 4) == '=')
		return (true);
	return (false);
}

void	init_pipex(t_pipex *data, int argc, char **argv, char **envp)
{
	data->argc = argc - 1;
	data->argv = argv + 1;
	data->envp = envp;
	while (!found_path_line(*envp))
		envp++;
	data->path = ft_split(*envp + 5, ':');
	if (!data->path)
		exit(EXIT_FAILURE);
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

int	pipex(int fd_in, char **args, char **envp)
{
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
	{
		ft_printf("Invalid number of arguments.\n");
		return (EXIT_FAILURE);
	}
	init_pipex(&data, argc, argv, envp);

	return (EXIT_SUCCESS);
}
