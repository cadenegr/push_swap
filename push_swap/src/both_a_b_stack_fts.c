/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_a_b_stack_fts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:56:11 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 13:53:02 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	ss(t_s *a, t_s *b, t_g *g)
{
	int	temp;

	if (a->top >= 1)
	{
		temp = a->s[a->top];
		a->s[a->top] = a->s[a->top - 1];
		a->s[a->top - 1] = temp;
	}
	if (b->top >= 1)
	{
		temp = b->s[b->top];
		b->s[b->top] = b->s[b->top - 1];
		b->s[b->top - 1] = temp;
		ft_printf("ss\n");
		g->moves++;
	}
	else
		return ;
}

void	rr(t_s *a, t_s *b, t_g *g)
{
	int	a_top_element;
	int	b_top_element;
	int	i;

	i = a->top;
	a_top_element = a->s[a->top];
	while (i > 0)
	{
		a->s[i] = a->s[i - 1];
		i--;
	}
	a->s[0] = a_top_element;
	if (b->top < 1)
		return ;
	i = b->top;
	b_top_element = b->s[b->top];
	while (i > 0)
	{
		b->s[i] = b->s[i - 1];
		i--;
	}
	b->s[0] = b_top_element;
	ft_printf("rr\n");
	g->moves++;
}

void	rrr(t_s *a, t_s *b, t_g *g)
{
	int	bottom_element;
	int	i;

	i = 0;
	bottom_element = a->s[0];
	while (i < a->top)
	{
		a->s[i] = a->s[i + 1];
		i++;
	}
	a->s[a->top] = bottom_element;
	if (b->top < 1)
		return ;
	i = 0;
	bottom_element = b->s[0];
	while (i < b->top)
	{
		b->s[i] = b->s[i + 1];
		i++;
	}
	b->s[b->top] = bottom_element;
	ft_printf("rrr\n");
	g->moves++;
}
