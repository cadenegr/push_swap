/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:07 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:06:54 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//checks from bottom up
int	check_from_zero(t_s *b, int value)
{
	int	i;

	i = 0;
	while (i <= b->top)
	{
		if (b->s[i] == value)
			break ;
		i++;
	}
	return (i);
}

//checks from top to bottom
int	check_from_top(t_s *b, int value)
{
	int	i;

	i = b->top;
	while (i >= 0)
	{
		if (b->s[i] == value)
			break ;
		i--;
	}
	return (b->top - i);
}

//moves needed to bring value to the top of b
static int	cost_b(t_s *b, int value)
{
	int	up;
	int	down;

	up = check_from_top(b, value);
	down = check_from_zero(b, value) + 1;
	if (down < up)
		return (down);
	return (up);
}

//rotates b the short way until value is on top
static void	bring_to_top(t_g *g, t_s *b, int value)
{
	if (check_from_zero(b, value) + 1 < check_from_top(b, value))
		while (b->s[b->top] != value)
			rrb(b, g);
	else
		while (b->s[b->top] != value)
			rb(b, g);
}

//pulls the biggest number of b back to a, one at a time.
//if the second biggest is closer, it goes first and sa fixes the order.
void	pull_back(t_g *g, t_s *b, t_s *a)
{
	int	max;
	int	second;

	while (!is_empty(&b->top))
	{
		max = g->sorted_array[b->top];
		second = max;
		if (b->top > 0)
			second = g->sorted_array[b->top - 1];
		if (b->top > 0 && cost_b(b, second) < cost_b(b, max))
		{
			bring_to_top(g, b, second);
			pa(b, a, g);
			bring_to_top(g, b, max);
			pa(b, a, g);
			sa(a, g);
		}
		else
		{
			bring_to_top(g, b, max);
			pa(b, a, g);
		}
	}
}
