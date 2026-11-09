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
	else
	{
		divide_blocks(g, a, b, how_many_blocks(g->size));
		pull_back(g, b, a);
	}
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
