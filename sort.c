/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:43:23 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/16 23:49:00 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*copy_values(t_node *stack, int size)
{
	int		*arr;
	t_node	*cur;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		print_error();
	i = 0;
	cur = stack;
	while (i < size && cur)
	{
		arr[i] = cur->value;
		i++;
		cur = cur->next;
	}
	return (arr);
}

void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	*copy_and_sort(t_node *stack, int size)
{
	int	*arr;

	arr = copy_values(stack, size);
	bubble_sort(arr, size);
	return (arr);
}

void	compress_stack(t_node *stack, int *sorted)
{
	t_node	*cur;
	int		idx;

	cur = stack;
	while (cur)
	{
		idx = 0;
		while (sorted[idx] != cur->value)
			idx++;
		cur->value = idx;
		cur = cur->next;
	}
}

int	*compress_values(t_node *stack, int size)
{
	int	*sorted;

	sorted = copy_and_sort(stack, size);
	compress_stack(stack, sorted);
	return (sorted);
}

int	get_max_bits(t_node *stack)
{
	int		max;
	int		bits;
	t_node	*tmp;

	max = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
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

void	radix_sort(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	bits;
	int	size;
	int	i;
	int	moves;
	int	top_val;

	bits = get_max_bits(*stack_a);
	size = stack_length(*stack_a);
	i = 0;
	while (i < bits)
	{
		moves = size;
		while (moves--)
		{
			top_val = (*stack_a)->value;
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

void	restore_values(t_node *stack, int *sorted_arr)
{
	int	index;

	while (stack)
	{
		index = stack->value;
		stack->value = sorted_arr[index];
		stack = stack->next;
	}
}

int	find_pivot(t_node *stack, int len)
{
	int	*sorted;
	int	pivot;

	sorted = copy_and_sort(stack, len);
	pivot = sorted[len / 2];
	free(sorted);
	return (pivot);
}

void	quicksort_a(t_node **stack_a, t_node **stack_b, int len, int *move_count)
{
	int	pivot; 
	int	pushed;
	int	rotated;
	int	i;
	
	if (len <= 3)
	{
		if (len == 2)
			sort_two(stack_a, move_count);
		else if (len == 3)
			sort_three(stack_a, move_count);
		return;
	}
	pivot = find_pivot(*stack_a, len);
	pushed = 0; rotated = 0; i = 0;
	while (i < len)
	{
		if ((*stack_a)->value < pivot)
		{
			pb(stack_a, stack_b, move_count);
			pushed++;
		}
		else
		{
			ra(stack_a, 1, move_count);
			rotated++;
		}
		i++;
	}
	i = 0;
	while (i < rotated)
	{
		rra(stack_a, 1, move_count);
		i++;
	}
	quicksort_a(stack_a, stack_b, len - pushed, move_count);
	quicksort_b(stack_a, stack_b, pushed, move_count);
	i = 0;
	while (i < pushed)
	{
		pa(stack_a, stack_b, move_count);
		i++;
	}
}

void quicksort_b(t_node **stack_a, t_node **stack_b, int len, int *move_count)
{
	int	pivot;
	int	pushed; 
	int	rotated;
	int	i;

	if (len <= 3)
	{
		while (len > 0)
		{
			pa(stack_a, stack_b, move_count);
			len--;
		}
		return;
	}
	pivot = find_pivot(*stack_b, len);
	pushed = 0; rotated = 0; i = 0;
	while (i < len)
	{
		if ((*stack_b)->value >= pivot)
		{
			pa(stack_a, stack_b, move_count);
			pushed++;
		}
		else
		{
			rb(stack_b, 1, move_count);
			rotated++;
		}
		i++;
	}
	i = 0;
	while (i < rotated)
	{
		rrb(stack_b, 1, move_count);
		i++;
	}
	quicksort_a(stack_a, stack_b, pushed, move_count);
	quicksort_b(stack_a, stack_b, len - pushed, move_count);
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

int	get_index_of_value(t_node *stack, int value)
{
	int	idx;

	idx = 0;
	while (stack)
	{
		if (stack->value == value)
			return (idx);
		idx++;
		stack = stack->next;
	}
	return (-1);
}

void	chunks_push(t_node **stack_a, t_node **stack_b, int *move_count,
		int size, int number_of_chunks)
{
	int	chunk_size;
	int	current_chunk;
	int	pushed_count;

	chunk_size = size / number_of_chunks;
	current_chunk = 1;
	pushed_count = 0;
	while (*stack_a)
	{
		if ((*stack_a)->value < current_chunk * chunk_size)
		{
			pb(stack_a, stack_b, move_count);
			pushed_count++;
			if (*stack_b && ((*stack_b)->value < current_chunk * chunk_size
				- (chunk_size / 2)))
				rb(stack_b, 1, move_count);
		}
		else
			ra(stack_a, 1, move_count);
		if (pushed_count >= current_chunk * chunk_size && current_chunk
			< number_of_chunks)
			current_chunk++;
	}
}

void	chunks_reassemble(t_node **stack_a, t_node **stack_b, int *move_count)
{
	int	max;
	int	idx;
	int	len_b;

	while (*stack_b)
	{
		max = get_max_value(*stack_b);
		idx = get_index_of_value(*stack_b, max);
		len_b = stack_length(*stack_b);
		if (idx <= len_b / 2)
		{
			while ((*stack_b)->value != max)
				rb(stack_b, 1, move_count);
		}
		else
		{
			while ((*stack_b)->value != max)
				rrb(stack_b, 1, move_count);
		}
		pa(stack_a, stack_b, move_count);
	}
}

int	has_value_in_range(t_node *stack, int low, int high)
{
    while (stack)
    {
        if (stack->value >= low && stack->value < high)
            return (1);
        stack = stack->next;
    }
    return (0);
}

int	index_of_first_in_range(t_node *stack, int low, int high)
{
    int idx;

    idx = 0;
    while (stack)
    {
        if (stack->value >= low && stack->value < high)
            return (idx);
        idx++;
        stack = stack->next;
    }
    return (-1);
}

void	push_chunk(t_node **stack_a, t_node **stack_b, int *move_count, int low, int high)
{
    int idx;
    int len;

    while (has_value_in_range(*stack_a, low, high))
    {
        len = stack_length(*stack_a);
        idx = index_of_first_in_range(*stack_a, low, high);
        if (idx == -1)
            break;
        if (idx <= len / 2)
        {
            while (idx-- > 0)
                ra(stack_a, 1, move_count);
        }
        else
        {
            idx = len - index_of_first_in_range(*stack_a, low, high);
            while (idx-- > 0)
                rra(stack_a, 1, move_count);
        }
        pb(stack_a, stack_b, move_count);
    }
}

void	chunks_sort(t_node **stack_a, t_node **stack_b, int *move_count)
{
    int size;
    int chunk_count;
    int chunk_size;
    int current_chunk;
    int low_bound;
    int high_bound;

    size = stack_length(*stack_a);
    if (size <= 5)
    {
        if (size == 2)
            sort_two(stack_a, move_count);
        else if (size == 3)
            sort_three(stack_a, move_count);
        else
            sort_five(stack_a, stack_b, move_count);
        return;
    }
    // Para 100 números, probamos con 5 chunks; para mayor tamaño, ajustar según corresponda.
    if (size <= 100)
        chunk_count = 5;
    else
        chunk_count = 15;
    chunk_size = size / chunk_count;
    current_chunk = 0;
    while (current_chunk < chunk_count)
    {
        low_bound = current_chunk * chunk_size;
        if (current_chunk == chunk_count - 1)
            high_bound = size;  // Último chunk toma todo lo restante.
        else
            high_bound = (current_chunk + 1) * chunk_size;
        push_chunk(stack_a, stack_b, move_count, low_bound, high_bound);
        current_chunk++;
    }
    // Si quedaron elementos en A (por alguna razón), empújalos a B
    while (stack_length(*stack_a) > 0)
        pb(stack_a, stack_b, move_count);
    // Reensamblado: mover de B a A en orden (extrayendo el máximo cada vez)
    while (stack_length(*stack_b) > 0)
    {
        int max, idx, len_b;
        max = get_max_value(*stack_b);
        idx = get_index_of_value(*stack_b, max);
        len_b = stack_length(*stack_b);
        if (idx <= len_b / 2)
        {
            while ((*stack_b)->value != max)
                rb(stack_b, 1, move_count);
        }
        else
        {
            while ((*stack_b)->value != max)
                rrb(stack_b, 1, move_count);
        }
        pa(stack_a, stack_b, move_count);
    }
}