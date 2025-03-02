/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/02 12:54:36 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		ft_atoi(char *s, char *valid)
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
		else 
			*valid = '\0';
		s++;
	}
	return (result * sign);
}

int	validate_no_clones(char **argv) {
	int i;
	int j;
	
	i = 0;
	while (argv[i]) {
		j = i + 1;
		while (argv[j]) {
			if (strcmp(argv[i], argv[j]) == 0) {
				printf("Gotcha! %s, %s\n", argv[i], argv[j]);
				return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}

// int 	validate_no_bad_nums()
// {
	
// 	return (1);
// }

int		validate_args(int argc, char **argv)
{
	(void)argc;
	validate_no_clones(argv);
	// validate_no_bad_nums(**argv);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (!validate_args(argc, argv))
		return (1);
	return (0);
}
