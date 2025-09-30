/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_eight_div.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:39:13 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:06:21 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//it send from b to a, now divided in 8 blocks
void	divide_eight(t_g *g, t_s *a, t_s *b, int multiplier)
{
	int	divider;
	int	starter;
	int	count;

	count = -1;
	starter = g->size;
	divider = g->size / (multiplier * 2);
	while (b->top > (starter - divider))
	{
		if (search(b->s, b->top, g) > (starter - divider))
		{
			pa(b, a, g);
			sort_low_to_high(a, g, (divider / 2));
		}
		else
		{
			rb(b, g);
			count++;
		}
	}
	g->counter = count;
	if (count > -1)
		continue_div_eight(g, a, b, divider);
}

//it keeps goin until all of b is send to a
void	continue_div_eight(t_g *g, t_s *a, t_s *b, int divider)
{
	int	count;

	count = g->counter;
	while (count >= 0)
	{
		rrb(b, g);
		pa(b, a, g);
		count--;
	}
	send_to_a_by_blocks(g, a, b, (divider * 3));
	send_to_a_by_blocks(g, a, b, (divider * 5));
	send_to_a_by_blocks(g, a, b, (divider * 7));
	while (!is_empty(&b->top))
		pa(b, a, g);
}

//makes the division of each block sended
void	send_to_a_by_blocks(t_g *g, t_s *a, t_s *b, int divider)
{
	int	count;
	int	starter;

	count = -1;
	starter = g->size;
	while (b->top > (starter - divider))
	{
		if (search(b->s, b->top, g) > (starter - divider))
			pa(b, a, g);
		else
		{
			rb(b, g);
			count++;
		}
		if (count == (divider / 2))
			break ;
	}
	if (count < 0)
		return ;
	while (count >= 0)
	{
		rrb(b, g);
		pa(b, a, g);
		count--;
	}
}

//to know if it sends the high numbers or not
void	sort_low_to_high(t_s *a, t_g *g, int divider)
{
	if (a->top < 1)
		return ;
	if (search(a->s, a->top, g) > (g->size - divider))
		ra(a, g);
}
