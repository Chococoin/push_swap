/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:33 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 17:41:38 by glugo-mu         ###   ########.fr       */
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

int	no_alpha_validator(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9') && *s != '-')
			return (0);
		s++;
	}
	return (1);
}

void	validate_no_dupl(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (argv[j])
		{
			if (ft_strcmp(argv[i], argv[j]) == 0)
				print_error();
			j++;
		}
		i++;
	}
}

void	validate_no_char(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!(no_alpha_validator(argv[i])))
			print_error();
		i++;
	}
}

void	validate_args(char **argv)
{
	validate_no_dupl(argv);
	validate_no_char(argv);
}
