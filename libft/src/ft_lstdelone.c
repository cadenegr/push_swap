/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <cadenegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:09:43 by cadenegr          #+#    #+#             */
/*   Updated: 2023/07/06 10:25:48 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	(*del)(lst->content);
	lst->next = NULL;
	free(lst);
}
/*
#include <stdio.h>
void deleteNode(void *content) {
    printf("Deleting node with content: %s\n", (char *)content);
    // No need to free the content here since it's already freed in ft_lstdelone
}

int main(void) {
    // Create a node with content
    t_list *node = ft_lstnew("Node");

    // Call the ft_lstdelone function to delete the node
    ft_lstdelone(node, deleteNode);

    return 0;
}*/