/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:43:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 17:14:03 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two(t_node **stack_a, int *move_count)
{
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1, move_count);
}

void	sort_three(t_node **stack_a, int *move_count)
{
	int	first;
	int	second;
	int	third;

	first = (*stack_a)->value;
	second = (*stack_a)->next->value;
	third = (*stack_a)->next->next->value;
	if (first > second && first < third)
		sa(stack_a, 1, move_count);
	else if (first > second && second > third)
	{
		sa(stack_a, 1, move_count);
		rra(stack_a, 1, move_count);
	}
	else if (first > second && second < third)
		ra(stack_a, 1, move_count);
	else if (first < second && first > third)
		rra(stack_a, 1, move_count);
	else if (first < second && second > third)
	{
		sa(stack_a, 1, move_count);
		ra(stack_a, 1, move_count);
	}
}

int	get_min_index(t_node *stack)
{
	int	min;
	int	index;
	int	min_index;

	min = stack->value;
	index = 0;
	min_index = 0;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_index = index;
		}
		index++;
		stack = stack->next;
	}
	return (min_index);
}

static void	push_min_to_b(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	min_index;
	int	len;
	int	moves;

	min_index = get_min_index(*stack_a);
	len = stack_length(*stack_a);
	if (min_index == 0)
		pb(stack_a, stack_b, move_count);
	else if (min_index <= len / 2)
	{
		while (min_index-- > 0)
			ra(stack_a, 1, move_count);
		pb(stack_a, stack_b, move_count);
	}
	else
	{
		moves = len - min_index;
		while (moves-- > 0)
			rra(stack_a, 1, move_count);
		pb(stack_a, stack_b, move_count);
	}
}

void	sort_five(t_node **stack_a, t_node **stack_b, int *move_count)
{
	while (stack_length(*stack_a) > 3)
		push_min_to_b(stack_a, stack_b, move_count);
	sort_three(stack_a, move_count);
	while (*stack_b)
		pa(stack_a, stack_b, move_count);
}

int	get_max_value(t_node *stack)
{
	int	max;

	max = stack->value;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}
