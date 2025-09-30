/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_four_div.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:34:07 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:06:54 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//sort b to a in small
void	sort_to_a(t_g *g, t_s *b, t_s *a)
{
	int		i;

	i = 1;
	while (!is_empty(&b->top))
	{
		if (g->sorted_array[i] == b->s[b->top])
		{
			pa(b, a, g);
			i--;
		}
		else
			rb(b, g);
	}
}

//sort b to a big
void	sort_if_div_four(t_g *g, t_s *b, t_s *a)
{
	int		i;

	i = g->size - 1;
	while (!is_empty(&b->top))
	{
		if (g->sorted_array[i] == b->s[b->top])
		{
			pa(b, a, g);
			i--;
		}
		else
		{
			if (check_from_zero(b, g->sorted_array[i])
				< check_from_top(b, g->sorted_array[i]))
				rrb(b, g);
			else
				rb(b, g);
		}
	}
}

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
