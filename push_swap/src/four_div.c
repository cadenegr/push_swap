/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   four_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:21:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 18:02:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//send half and divides the half in stack b
void	divide_four(t_g *g, t_s *a, t_s *b, int multiplier)
{
	int	divider;
	int	starter;

	starter = g->size;
	divider = g->size / (multiplier * 2);
	while (a->top >= divider)
	{
		if (search(a->s, a->top, g) < (starter - divider))
		{
			pb(a, b, g);
			sort_high_and_low(g, b, (divider / 2));
		}
		else
			ra(a, g);
	}
}

//check in sorted arr, to know if high the medium or below
int	search(int *array, int top, t_g *g)
{
	int	i;

	i = 0;
	while (i < g->size)
	{
		if (array[top] == g->sorted_array[i])
			break ;
		i++;
	}
	return (i);
}

//if the value is low, it goes to the bottom of the stack
void	sort_high_and_low(t_g *g, t_s *b, int divider)
{
	if (b->top < 1)
		return ;
	if (search(b->s, b->top, g) < divider)
		rb(b, g);
}

//push the remainder of a to b
void	push_rest_of_div_four(t_g *g, t_s *a, t_s *b)
{
	while (!is_empty(&a->top))
		pb(a, b, g);
}
