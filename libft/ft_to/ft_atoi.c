/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:18:13 by ccormon           #+#    #+#             */
/*   Updated: 2024/02/29 13:31:14 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\r'
		|| c == '\v')
		return (true);
	return (false);
}

int	ft_atoi(const char *nptr)
{
	unsigned long long	nb;
	int					sign;
	size_t				i;

	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	sign = 1;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		nb = nb * 10 + nptr[i++] - '0';
		if ((sign == -1 && nb > (unsigned long long)INT_MAX + 1)
			|| (sign == 1 && nb > (unsigned long long)INT_MAX))
			return (0);
	}
	return (sign * nb);
}
