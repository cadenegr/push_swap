/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_stack_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:54:58 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 13:52:40 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	sa(t_s *a, t_g *g)
{
	int	temp;

	if (a->top >= 1)
	{
		temp = a->s[a->top];
		a->s[a->top] = a->s[a->top - 1];
		a->s[a->top - 1] = temp;
		ft_printf("sa\n");
		g->moves++;
	}
	else
		return ;
}

void	ra(t_s *a, t_g *g)
{
	int	a_top_element;
	int	i;

	if (a->top < 1)
		return ;
	i = a->top;
	a_top_element = a->s[a->top];
	while (i > 0)
	{
		a->s[i] = a->s[i - 1];
		i--;
	}
	a->s[0] = a_top_element;
	ft_printf("ra\n");
	g->moves++;
}

void	rra(t_s *a, t_g *g)
{
	int	bottom_element;
	int	i;

	if (a->top < 1)
		return ;
	i = 0;
	bottom_element = a->s[0];
	while (i < a->top)
	{
		a->s[i] = a->s[i + 1];
		i++;
	}
	a->s[a->top] = bottom_element;
	ft_printf("rra\n");
	g->moves++;
}

void	pb(t_s *a, t_s *b, t_g *g)
{
	push(b->s, &b->top, a->s[a->top]);
	pop(a->s, &a->top);
	ft_printf("pb\n");
	g->moves++;
}
