/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:27:48 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 13:43:27 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_node **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}

void	sort_three(t_node **stack_a)
{
	int	first;
	int	second;
	int	third;

	first = (*stack_a)->value;
	second = (*stack_a)->next->value;
	third = (*stack_a)->next->next->value;
	if (first > second && first < third)
		sa(stack_a, 1);
	else if (first > second && second > third)
	{
		sa(stack_a, 1);
		rra(stack_a, 1);
	}
	else if (first > second && second < third)
		ra(stack_a, 1);
	else if (first < second && first > third)
		rra(stack_a, 1);
	else if (first < second && second > third)
	{
		sa(stack_a, 1);
		ra(stack_a, 1);
	}
}

void	sort_five(t_node **stack_a, t_node **stack_b)
{
	while (stack_length(*stack_a) > 3)
		push_min_to_b(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
}

void	push_swap(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = stack_length(*stack_a);
	if (size <= 1)
		return ;
	if (size == 2)
		sort_two(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size <= 5)
		sort_five(stack_a, stack_b);
	else
		turk_sort(stack_a, stack_b);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (0);
	validate_args(argv);
	fill_stack_a(argv, &stack_a);
	push_swap(&stack_a, &stack_b);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
