/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:58:17 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 15:57:50 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//sorting reception, according to array size
void	sort(t_g *g, t_s *a, t_s *b)
{
	if (g->size < 1)
		return ;
	else if (is_it_sorted(a) == true)
		return ;
	else if (g->size < 4)
		just_sort(g, a);
	else if (g->size < 6)
		sort_small(g, a, b);
	else if (g->size < 121)
		four(g, a, b);
	else
		eight(g, a, b);
	b->top = -1;
}

// //simple sort algorithm for 3 or 2 size stack.
void	just_sort(t_g *g, t_s *a)
{
	if (is_it_sorted(a) == true)
		return ;
	if (a->top == 1)
		sa(a, g);
	else
		sort_three(g, a);
}

//sort for up to 7 stack size.
void	sort_small(t_g *g, t_s *a, t_s *b)
{
	divide(g, a, b);
	just_sort(g, a);
	sort_to_a(g, b, a);
}

//sort for up to 120 stack size
void	four(t_g *g, t_s *a, t_s *b)
{
	divide_four(g, a, b, 1);
	divide_four(g, a, b, 2);
	push_rest_of_div_four(g, a, b);
	sort_if_div_four(g, b, a);
}

//sort for over 120 tack size
void	eight(t_g *g, t_s *a, t_s *b)
{
	divide_four(g, a, b, 1);
	divide_four(g, a, b, 2);
	push_rest_of_div_four(g, a, b);
	divide_eight(g, a, b, 4);
	divide_four(g, a, b, 8);
	push_rest_of_div_four(g, a, b);
	divide_eight(g, a, b, 8);
	divide_four(g, a, b, 16);
	push_rest_of_div_four(g, a, b);
	sort_if_div_four(g, b, a);
}
