/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:32:47 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 17:05:12 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*stack_a = NULL;
	t_node	*stack_b = NULL;
	int		move_count = 0;

	if (argc == 1)
		return (0);
	validate_args(argv);
	fill_stack_a(argv, &stack_a);
	print_stacks(stack_a, stack_b);
	push_swap(&stack_a, &stack_b, &move_count);
	print_stacks(stack_a, stack_b);
	printf("Total moves: %d\n", move_count);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
