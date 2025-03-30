/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:43:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 19:28:15 by glugo-mu         ###   ########.fr       */
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

void	sort_five(t_node **stack_a, t_node **stack_b)
{
	while (stack_length(*stack_a) > 3)
		push_min_to_b(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b);
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
