/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:35:53 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/21 10:52:40 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_g		g;
	t_s		a;
	t_s		b;

	if (argc == 1)
		return (1);
	if (!argument_processor(argc, argv, &g))
	{
		ft_printf("Error");
		return (0);
	}
	init_stacks(&g, &a, &b);
	sort(&g, &a, &b);
	return (0);
}
