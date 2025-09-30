/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:06:13 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:18:30 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	aux = lst;
	if (!aux)
		return (NULL);
	while (aux->next)
		aux = aux->next;
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

    // Call the ft_lstlast function to get the last node in the list
    t_list *lastNode = ft_lstlast(node1);

    // Print the content of the last node
    printf("Last node: %s\n", (char *)lastNode->content);

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/