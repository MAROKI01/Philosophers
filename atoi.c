/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:46:47 by ntahadou          #+#    #+#             */
/*   Updated: 2025/04/21 16:58:23 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	sum;
	int		digit;

	sign = 1;
	sum = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		sum = sum * 10 + digit;
		if (sum * sign > INT_MAX || sum * sign < INT_MIN)
			return (sum * sign);
		str++;
	}
	return (sum * sign);
}
