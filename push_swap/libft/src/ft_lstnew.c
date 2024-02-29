/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:47:34 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:12:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*aux;

	aux = (t_list *)malloc(sizeof(t_list));
	if (!aux)
		return (NULL);
	aux->content = content;
	aux->next = NULL;
	return (aux);
}
/*
#include <stdio.h>
int main(void) {
    // Create a test content
    int value = 42;

    // Call the ft_lstnew function
    t_list *node = ft_lstnew(&value);

    // Check if the node was successfully created
    if (node != NULL) {
        printf("Node created successfully.\n");
        printf("Content: %d\n", *(int *)node->content);
    } else {
        printf("Failed to create a node.\n");
    }

    // Free the memory allocated for the node
    free(node);

    return 0;
}*/