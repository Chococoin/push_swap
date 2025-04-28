/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:33 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/04/24 21:19:28 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	check_number_limits(const char *str)
{
	long long	n;
	int			sign;
	int			j;

	n = 0;
	sign = 1;
	j = 0;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			sign = -1;
		j++;
	}
	if (!str[j])
		print_error();
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
			print_error();
		n = n * 10 + (str[j] - '0');
		if ((sign == 1 && n > INT_MAX) || (sign == -1 && (-n) < INT_MIN))
			print_error();
		j++;
	}
}

static void	validate_range(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		check_number_limits(argv[i]);
		i++;
	}
}

static void	validate_no_dupl(char **argv)
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

static void validate_disorder(char **argv)
{
	int	i;
	int len;

	len = 0;
	i = 1;
	while (argv[i + 1])
	{
		len++;
		i++;
	}
	i = 1;
	while (argv[i + 1])
	{
		if (ft_atoi(argv[i]) < ft_atoi(argv[i + 1]))
			len--;
		i++;
	}
	if (len == 0)
		print_void();
}

void	validate_args(char **argv)
{
	validate_disorder(argv);
	validate_range(argv);
	validate_no_dupl(argv);
}
