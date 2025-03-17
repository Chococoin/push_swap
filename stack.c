/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:34:19 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/16 12:30:16 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_stack_a(char **argv, t_node **stack_a)
{
	int		i;
	t_node	*new_node;
	t_node	*tail;

	i = 1;
	tail = NULL;
	while (argv[i])
	{
		new_node = malloc(sizeof(t_node));
		if (!new_node)
			print_error();
		new_node->value = ft_atoi(argv[i]);
		new_node->prev = tail;
		new_node->next = NULL;
		if (!*stack_a)
			*stack_a = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
}

int	stack_length(t_node *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

void	free_stack(t_node *stack)
{
	t_node	*tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}
