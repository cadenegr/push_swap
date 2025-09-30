/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:57:16 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:16:15 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
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

    // Create a new node
    t_list *newNode = ft_lstnew("New Node");

    // Add the new node at the front of the list
    ft_lstadd_front(&node1, newNode);

    // Print the updated list
    t_list *current = node1;
    while (current) {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/