/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:23:53 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:59:55 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_atoi(char *s)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t' || *s == '\v')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			result = result * 10 + (*s - '0');
		s++;
	}
	return (result * sign);
}
