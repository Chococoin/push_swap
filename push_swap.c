/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 15:39:20 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int size;

	size = stack_length(*stack_a);
	if (size <= 1)
		return;
	if (size == 2)
		sort_two(stack_a, move_count);
	else if (size == 3)
		sort_three(stack_a, move_count);
	else if (size <= 5)
		sort_five(stack_a, stack_b, move_count);
	else
		turk_sort(stack_a, stack_b, move_count);;
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		move_count;

	stack_a = NULL;
	stack_b = NULL;
	move_count = 0;
	if (argc == 1)
		return (0);
	validate_args(argv);
	fill_stack_a(argv, &stack_a);
	push_swap(&stack_a, &stack_b, &move_count);
	printf("Total moves: %d\n", move_count);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
