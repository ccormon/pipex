/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:26:23 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/07 11:06:46 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s1)
		return (false);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (true);
	return (false);
}
