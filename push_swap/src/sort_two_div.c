/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two_div.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:22:24 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 16:12:10 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//is it sorted?
bool	is_it_sorted(t_s *a)
{
	int	i;
	int	j;

	i = a->top;
	j = 0;
	while (i > 0)
	{
		if (i != 0 && (a->s[i] < a->s[i - 1]))
		{
			i--;
			j++;
		}
		else
			return (false);
	}
	return (true);
}

//sort for three
void	sort_three(t_g *g, t_s *a)
{
	if (is_it_sorted(a) == true)
		return ;
	else if (a->s[a->top] == g->sorted_array[g->size - 3])
	{
		rra(a, g);
		sa(a, g);
	}
	else if (a->s[a->top] == g->sorted_array[g->size - 2]
		&& a->s[a->top] < a->s[a->top - 1])
		rra(a, g);
	else if (a->s[a->top] == g->sorted_array[g->size - 2]
		&& a->s[a->top] > a->s[a->top - 1])
		sa(a, g);
	else if (a->s[a->top] == g->sorted_array[g->size - 1]
		&& a->s[a->top - 1] > g->sorted_array[g->size - 3])
	{
		sa(a, g);
		rra(a, g);
	}
	else
	{
		rra(a, g);
		rra(a, g);
	}
}

//divide in two segments
void	divide(t_g *g, t_s *a, t_s *b)
{
	int	middle_point;
	int	i;

	middle_point = 2;
	while (!is_empty(&a->top))
	{
		i = 0;
		while (i < g->size)
		{
			if (a->s[a->top] == g->sorted_array[i])
				break ;
			i++;
		}
		if (i < middle_point)
			pb(a, b, g);
		else
			ra(a, g);
		if (a->top == 2)
			break ;
	}
}
