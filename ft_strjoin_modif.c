/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_modif.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:28:27 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/16 16:54:41 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
