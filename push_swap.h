/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:33:47 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/30 17:40:30 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_node
{
	int				value;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_cost
{
	int	ra_cost;
	int	rra_cost;
	int	rb_cost;
	int	rrb_cost;
	int	total;
}	t_cost;

void	print_error(void);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(char *s);
int		no_alpha_validator(char *s);
void	validate_no_dupl(char **argv);
void	validate_no_char(char **argv);
void	validate_args(char **argv);
void	free_stack(t_node *stack);
void	fill_stack_a(char **argv, t_node **stack_a);
int		stack_length(t_node *stack);
void	sa(t_node **stack_a, int to_print, int *move_count);
void	sb(t_node **stack_b, int to_print, int *move_count);
void	ss(t_node **stack_a, t_node **stack_b, int *move_count);
void	pa(t_node **stack_a, t_node **stack_b, int *move_count);
void	pb(t_node **stack_a, t_node **stack_b, int *move_count);
void	ra(t_node **stack_a, int to_print, int *move_count);
void	rb(t_node **stack_b, int to_print, int *move_count);
void	rr(t_node **stack_a, t_node **stack_b, int *move_count);
void	rra(t_node **stack_a, int to_print, int *move_count);
void	rrb(t_node **stack_b, int to_print, int *move_count);
void	rrr(t_node **stack_a, t_node **stack_b, int *move_count);
void	push_swap(t_node **stack_a, t_node **stack_b, int *move_count);
void	sort_two(t_node **stack_a, int *move_count);
void	sort_five(t_node **stack_a, t_node **stack_b, int *move_count);
void	sort_three(t_node **stack_a, int *move_count);
int		get_max_value(t_node *stack);
t_cost	calculate_cost(t_node *stack_a, t_node *stack_b, int value);
int		find_cheapest_value(t_node *stack_a, t_node *stack_b);
void	execute_rotations(t_node **stack_a, t_node **stack_b, int value, int *move_count);
void	turk_sort(t_node **stack_a, t_node **stack_b, int *move_count);

#endif
