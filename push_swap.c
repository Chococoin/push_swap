/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 16:58:56 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	*sorted_arr;
	int	size;

	size = stack_length(*stack_a);
	if (size <= 1)
		return;
	sorted_arr = compress_values(*stack_a, size);
	if (!sorted_arr)
		print_error();
	radix_sort(stack_a, stack_b, move_count);
	restore_values(*stack_a, sorted_arr);
	free(sorted_arr);
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
	print_stacks(stack_a, stack_b);
	push_swap(&stack_a, &stack_b, &move_count);
	print_stacks(stack_a, stack_b);
	printf("Total moves: %d\n", move_count);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
