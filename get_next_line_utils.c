/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsampaio <rsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:59:22 by rsampaio          #+#    #+#             */
/*   Updated: 2025/01/11 21:17:14 by rsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//creates new nodes, receives the content, and returns the node
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

//returns the last node of the list
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

//deletes the list and free each node
void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

//adds the node on the end of the list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*ptr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (new == NULL)
		return ;
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

//alocates memory and every bytes inicialized with 0
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *) malloc(nmemb * size);
	if (dst == NULL)
		return (NULL);
	while (i < (nmemb * size))
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}

