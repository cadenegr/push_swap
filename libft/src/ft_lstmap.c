/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:11:51 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:44:10 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)
	(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;

	if (!lst)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	aux = new;
	lst = lst->next;
	while (lst)
	{
		aux->next = ft_lstnew((*f)(lst->content));
		if (!aux->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		aux = aux->next;
		lst = lst->next;
	}
	return (new);
}
/*
#include <stdio.h>
// Function to modify the content of a node
void *modifyContent(void *content) {
    int *oldValue = (int *)content;
    int *newValue = malloc(sizeof(int));
    if (newValue == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    *newValue = (*oldValue) * 2;
    return newValue;
}

// Function to print the content of a node
void printContent(void *content) {
    printf("%d\n", *((int *)content));
}

int main(void) {
    // Create a linked list with three nodes containing integers
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    t_list *node1 = ft_lstnew(&value1);
    t_list *node2 = ft_lstnew(&value2);
    t_list *node3 = ft_lstnew(&value3);

    // Set the next pointers to create the linked list
    node1->next = node2;
    node2->next = node3;

    // Call ft_lstmap to create a new linked list with modified content
    t_list *newList = ft_lstmap(node1, modifyContent, NULL);

    // Call ft_lstiter to print the content of each node in the new list
    ft_lstiter(newList, printContent);

    // Free the memory allocated for the nodes in the original list
    ft_lstclear(&node1, NULL);

    // Free the memory allocated for the nodes in the new list
    ft_lstclear(&newList, NULL);

    return 0;
}*/