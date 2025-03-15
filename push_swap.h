/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:33:47 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/03/15 17:01:24 by glugo-mu         ###   ########.fr       */
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
void	print_stacks(t_node *stack_a, t_node *stack_b);
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
int		*compress_values(t_node *stack, int size);
int		get_max_bits(t_node *stack);
void	radix_sort(t_node **stack_a, t_node **stack_b, int *move_count);
void	restore_values(t_node *stack, int *sorted_arr);
void	push_swap(t_node **stack_a, t_node **stack_b, int *move_count);

#endif
