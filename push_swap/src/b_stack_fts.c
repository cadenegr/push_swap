/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_stack_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:55:29 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/15 13:49:23 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	sb(t_s *b, t_g *g)
{
	int	temp;

	if (b->top >= 1)
	{
		temp = b->s[b->top];
		b->s[b->top] = b->s[b->top - 1];
		b->s[b->top - 1] = temp;
		ft_printf("sb\n");
		g->moves++;
	}
	else
		return ;
}

void	rb(t_s *b, t_g *g)
{
	int	b_top_element;
	int	i;

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
	ft_printf("rb\n");
	g->moves++;
}

void	rrb(t_s *b, t_g *g)
{
	int	bottom_element;
	int	i;

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
	ft_printf("rrb\n");
	g->moves++;
}

void	pa(t_s *b, t_s *a, t_g *g)
{
	push(a->s, &a->top, b->s[b->top]);
	pop(b->s, &b->top);
	ft_printf("pa\n");
	g->moves++;
}
