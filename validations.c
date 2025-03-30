/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:33 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 20:23:39 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
