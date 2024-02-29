/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:07:45 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:20:16 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aux;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = ft_lstlast(*lst);
	aux->next = new;
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

    // Create a new node to add to the end of the list
    t_list *newNode = ft_lstnew("New Node");

    // Call the ft_lstadd_back function to add the new node to the list
    ft_lstadd_back(&node1, newNode);

    // Print the updated list
    t_list *current = node1;
    while (current) {
        printf("Node content: %s\n", (char *)current->content);
        current = current->next;
    }

    // Free the memory allocated for the nodes
    free(node1);
    free(node2);
    free(node3);
    free(newNode);

    return 0;
}*/