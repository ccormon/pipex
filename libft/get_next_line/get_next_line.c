/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:04:21 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/08 15:20:48 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	addtoreaded(char **readed, char *buffer)
{
	char	*temp;
	size_t	i;
	size_t	j;

	temp = malloc((ft_strlen(*readed) + ft_strlen(buffer) + 1) * sizeof(char));
	if (!temp)
		return ;
	i = 0;
	if (*readed)
	{
		while ((*readed)[i])
		{
			temp[i] = (*readed)[i];
			i++;
		}
	}
	j = 0;
	while (buffer[j])
		temp[i++] = buffer[j++];
	temp[i] = '\0';
	free(*readed);
	*readed = temp;
}

char	*addtoline(char *readed)
{
	char	*line;
	size_t	i;

	i = 0;
	while (readed[i] && readed[i] != '\n')
		i++;
	if (i == 0 && readed[i] != '\n')
		return (NULL);
	if (readed[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (readed[i] && readed[i] != '\n')
	{
		line[i] = readed[i];
		i++;
	}
	if (readed[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

void	cleanreaded(char **readed)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while ((*readed)[i] && (*readed)[i] != '\n')
		i++;
	if (!((*readed)[i]))
	{
		free(*readed);
		*readed = NULL;
		return ;
	}
	temp = malloc((ft_strlen(*readed) - i + 1) * sizeof(char));
	if (!temp)
		return ;
	i++;
	j = 0;
	while ((*readed)[i])
		temp[j++] = (*readed)[i++];
	temp[j] = '\0';
	free(*readed);
	*readed = temp;
}

ssize_t	readline(ssize_t byte_read, char *buffer, char **readed, int fd)
{
	byte_read = read(fd, buffer, BUFFER_SIZE);
	if (byte_read <= 0)
		return (byte_read);
	buffer[byte_read] = '\0';
	addtoreaded(readed, buffer);
	return (byte_read);
}

char	*get_next_line(int fd)
{
	static char	*readed = NULL;
	char		*buffer;
	char		*line;
	ssize_t		byte_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte_read = BUFFER_SIZE;
	while (byte_read == BUFFER_SIZE && !ft_strchr(readed, '\n'))
		byte_read = readline(byte_read, buffer, &readed, fd);
	free(buffer);
	if (byte_read == -1)
	{
		free(readed);
		readed = NULL;
		return (NULL);
	}
	if (!readed)
		return (NULL);
	line = addtoline(readed);
	cleanreaded(&readed);
	return (line);
}
