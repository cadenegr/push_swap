/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:04:14 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:12:37 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		aux;

	aux = 0;
	while (lst)
	{
		lst = lst->next;
		aux++;
	}
	return (aux);
}

/*
#include <stdio.h>
int main(void) {
    // Create a linked list with three nodes
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Set the next pointers to create the linked list
    node1->next = node2;
    node2->next = node3;

    // Call the ft_lstsize function to get the size of the list
    int size = ft_lstsize(node1);

    printf("Size of the list: %d\n", size);

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/