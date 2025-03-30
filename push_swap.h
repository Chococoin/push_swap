/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:33:47 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/31 01:41:11 by glugo-mu         ###   ########.fr       */
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

typedef struct s_positions
{
	int	pos_a;
	int	pos_b;
	int	len_a;
	int	len_b;
}	t_positions;

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
void	sa(t_node **stack_a, int to_print);
void	sb(t_node **stack_b, int to_print);
void	ss(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack_a, int to_print);
void	rb(t_node **stack_b, int to_print);
void	rr(t_node **stack_a, t_node **stack_b);
void	rra(t_node **stack_a, int to_print);
void	rrb(t_node **stack_b, int to_print);
void	rrr(t_node **stack_a, t_node **stack_b);
int		get_position(t_node *stack, int value);
int		find_position_in_b(t_node *stack_b, int value);
int		get_min_index(t_node *stack);
void	push_swap(t_node **stack_a, t_node **stack_b);
void	sort_two(t_node **stack_a);
void	sort_five(t_node **stack_a, t_node **stack_b);
void	sort_three(t_node **stack_a);
int		get_max_value(t_node *stack);
t_cost	calc_cost(t_node *stack_a, t_node *stack_b, int value);
void	calculate_costs(t_cost *cost, t_positions *positions);
void	calculate_rb_rrb(t_cost *cost, int pos_b, int len_b);
void	calculate_ra_rra(t_cost *cost, int pos_a, int len_a);
void	calculate_common_cost(t_cost *cost);
int		find_cheapest(t_node *stack_a, t_node *stack_b);
void	execute_rotations(t_node **stack_a, t_node **stack_b, int value);
void	perform_rotations_rr(t_node **stack_a, t_node **stack_b, t_cost *cost);
void	perform_rotations(t_node **stack_a, t_node **stack_b, t_cost *cost);
void	perform_rot_single(t_node **stack_a, t_node **stack_b, t_cost *cost);
void	turk_sort(t_node **stack_a, t_node **stack_b);
void	push_min_to_b(t_node **stack_a, t_node **stack_b);
void	align_stack_b(t_node **stack_b);

#endif
