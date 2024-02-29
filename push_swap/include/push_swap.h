/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:16:28 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 17:10:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define MAX_SIZE 1000
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
//local struch variables to save space on my functions.
typedef struct s_local_variables
{
	int		i;
	int		j;
	int		k;
	int		temp;
	int		length;
	int		count;
	bool	turn_on;
}t_v;
//global struct
typedef struct s_global_variables
{
	long	long_array[MAX_SIZE];
	int		original_array[MAX_SIZE];
	int		sorted_array[MAX_SIZE];
	int		temp[MAX_SIZE];
	int		size;
	int		low;
	int		high;
	int		moves;
	int		counter;
}t_g;
//my array variables for my stacks.
typedef struct s_stack
{
	int	top;
	int	s[MAX_SIZE];
}t_s;

//argument processors
int		argument_processor(int argc, char **argv, t_g *g);
void	two_arguments(char *argv, t_g *g);
int		more_arguments(int argc, char **argv, t_g *g);
void	low_high_values(t_g *g);

//error handling
bool	correct_arguments(char *argv);
bool	parameters(t_g *g);
bool	int_size(t_g *g);
bool	duplicate(t_g *g);

//stack functions
void	initialize_stack(int *top);
bool	is_full(int *top);
bool	is_empty(int *top);
void	push(int *stack, int *top, int value);
int		pop(int *stack, int *top);

//build the stacks
void	init_stacks(t_g *g, t_s *a, t_s *b);
void	build_a_stack(t_g *g, t_s *s);

//sort directors
void	sort(t_g *g, t_s *a, t_s *b);
void	just_sort(t_g *g, t_s *a);
void	sort_three(t_g *g, t_s *a);
void	sort_small(t_g *g, t_s *a, t_s *b);
void	four(t_g *g, t_s *a, t_s *b);
void	eight(t_g *g, t_s *a, t_s *b);

//allowed movement of stack functions
void	sa(t_s *a, t_g *g);
void	ra(t_s *a, t_g *g);
void	rra(t_s *a, t_g *g);
void	pb(t_s *a, t_s *b, t_g *g);
void	sb(t_s *b, t_g *g);
void	rb(t_s *b, t_g *g);
void	rrb(t_s *b, t_g *g);
void	pa(t_s *b, t_s *a, t_g *g);
void	ss(t_s *a, t_s *b, t_g *g);
void	rr(t_s *a, t_s *b, t_g *g);
void	rrr(t_s *a, t_s *b, t_g *g);

//divide in two segments
bool	is_it_sorted(t_s *a);
void	divide(t_g *g, t_s *a, t_s *b);

//divide stack in four segments
void	divide_four(t_g *g, t_s *a, t_s *b, int multiplier);
int		search(int *array, int top, t_g *g);
void	sort_high_and_low(t_g *g, t_s *b, int divider);
void	sort_to_a(t_g *g, t_s *b, t_s *a);
void	push_rest_of_div_four(t_g *g, t_s *a, t_s *b);

//divide stack in eight segments
void	divide_eight(t_g *g, t_s *a, t_s *b, int multiplier);
void	continue_div_eight(t_g *g, t_s *a, t_s *b, int divider);
void	send_to_a_by_blocks(t_g *g, t_s *a, t_s *b, int divider);
void	sort_low_to_high(t_s *a, t_g *g, int divider);
//sorting from b_stack to a
void	sort_if_div_four(t_g *g, t_s *b, t_s *a);
int		check_from_zero(t_s *b, int value);
int		check_from_top(t_s *b, int value);

//print stack function.
void	print(t_s *a, t_s *b, t_g *g);
#endif