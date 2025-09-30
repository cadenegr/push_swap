/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:41:08 by cadenegr          #+#    #+#             */
/*   Updated: 2024/02/14 14:19:39 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

//stack array initializer, makes the "top" size -1
void	initialize_stack(int *top)
{
	*top = -1;
}

//if the size of the stack is reached it returns true
bool	is_full(int *top)
{
	return (*top == MAX_SIZE - 1);
}

//if the stack size is still -1, returns true
bool	is_empty(int *top)
{
	return (*top == -1);
}

//adds a value into the stack, the value is always at the end of the array
void	push(int *stack, int *top, int value)
{
	if (is_full(top))
	{
		ft_printf ("Stack is full. Cannt push in stack :%d.\n", value);
		return ;
	}
	stack[++(*top)] = value;
}

//makes the array one size shorter. 
int	pop(int *stack, int *top)
{
	if (is_empty(top))
	{
		ft_printf ("Stack is empty. Connot pop.\n");
		return (-1);
	}
	return (stack[(*top)--]);
}
