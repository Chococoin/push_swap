/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:43:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 17:20:00 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *compress_values(t_node *stack, int size)
{
	int     *sorted_arr;
	int     *tmp_values;
	t_node  *cur;
	int     i;

	tmp_values = malloc(sizeof(int) * size);
	if (!tmp_values)
		return (NULL);
	cur = stack;
	i = 0;
	while (cur)
	{
		tmp_values[i++] = cur->value;
		cur = cur->next;
	}

	sorted_arr = malloc(sizeof(int) * size);
	if (!sorted_arr)
	{
		free(tmp_values);
		return (NULL);
	}
	for (int k = 0; k < size; k++)
		sorted_arr[k] = tmp_values[k];

	for (int a = 0; a < size - 1; a++)
	{
		for (int b = a + 1; b < size; b++)
		{
			if (sorted_arr[a] > sorted_arr[b])
			{
				int aux = sorted_arr[a];
				sorted_arr[a] = sorted_arr[b];
				sorted_arr[b] = aux;
			}
		}
	}

	cur = stack;
	while (cur)
	{
		int idx = 0;
		while (sorted_arr[idx] != cur->value)
			idx++;
		cur->value = idx;
		cur = cur->next;
	}
	free(tmp_values);
	return (sorted_arr);
}

int get_max_bits(t_node *stack)
{
	int max = 0;
	t_node *tmp = stack;
	while (tmp)
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	int bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return bits;
}

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
	int	min_index = get_min_index(*stack_a);
	int	len = stack_length(*stack_a);

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
		int	moves = len - min_index;
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

void	radix_sort(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	bits;
	int	size;
	int	i;

	bits = get_max_bits(*stack_a);
	size = stack_length(*stack_a);
	i = 0;
	while ( i < bits)
	{
		int moves = size;
		while (moves--)
		{
			int top_val = (*stack_a)->value;
			if (((top_val >> i) & 1) == 0)
				pb(stack_a, stack_b, move_count);
			else
				ra(stack_a, 1, move_count);
		}
		while (*stack_b)
			pa(stack_a, stack_b, move_count);
		i++;
	}
}

void restore_values(t_node *stack, int *sorted_arr)
{
	while (stack)
	{
		int index = stack->value;
		stack->value = sorted_arr[index];
		stack = stack->next;
	}
}

void	push_swap(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int size;
	int *sorted_arr;

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
	{
		sorted_arr = compress_values(*stack_a, size);
		if (!sorted_arr)
			print_error();
		radix_sort(stack_a, stack_b, move_count);
		restore_values(*stack_a, sorted_arr);
		free(sorted_arr);
	}
}
