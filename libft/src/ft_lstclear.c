/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:10:19 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:28:53 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nxt;
	t_list	*aux;

	aux = *lst;
	while (aux)
	{
		nxt = aux->next;
		ft_lstdelone(aux, del);
		aux = nxt;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
// Function to delete a node's content
void deleteNode(void *content) {
    printf("Deleting node with content: %s\n", (char *)content);
}

int main(void) {
    // Create a linked list with three nodes
    t_list *node1 = ft_lstnew("Node 1");
    t_list *node2 = ft_lstnew("Node 2");
    t_list *node3 = ft_lstnew("Node 3");

    // Set the next pointers to create the linked list
    node1->next = node2;
    node2->next = node3;

    // Call ft_lstclear to delete all nodes
    ft_lstclear(&node1, deleteNode);

    // The list should be empty after clearing
    printf("After clearing, node1 is: %p\n", (void *)node1);
    printf("After clearing, node2 is: %p\n", (void *)node2);
    printf("After clearing, node3 is: %p\n", (void *)node3);

    return 0;
}*/