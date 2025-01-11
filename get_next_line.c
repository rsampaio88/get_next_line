/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsampaio <rsampaio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:34:35 by rsampaio          #+#    #+#             */
/*   Updated: 2025/01/11 21:36:59 by rsampaio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line(t_list *lista)
{
	int		i;
	t_list	*temp;

	temp = ft_lstlast(lista);
	if (!temp)
		return (0);
	i = 0;
	while (temp->content[i])
	{
		if (temp->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	read_line(t_list **lista, int fd)
{
	t_list	*node;
	int		readed;

	readed = 0;
	while (!new_line(*lista))
	{
		node = ft_lstnew(NULL);
		node->content = ft_calloc(sizeof(char *), BUFFER_SIZE + 1);
		if (!node->content)
		{
			free(node);
			return ;
		}
		readed = read(fd, node->content, BUFFER_SIZE);
		if (readed == 0 || readed == -1)
		{
			free(node->content);
			free(node);
			return ;
		}
		node->content[BUFFER_SIZE] = '\0';
		ft_lstadd_back(lista, node);
	}
}

void	make_line(t_list *lista, char **line)
{
	size_t	lenght;
	size_t	i;
	t_list	*temp;

	lenght = 0;
	temp = lista;
	while (temp)
	{
		lenght++;
		temp = temp->next;
	}
	if (!lenght)
		return ;
	*line = malloc(sizeof(**line) * ((lenght * BUFFER_SIZE) + 1));
	if (!*line)
		return ;
	lenght = 0;
	while (lista)
	{
		i = 0;
		while (i < BUFFER_SIZE && lista->content[i] != '\n')
			(*line)[lenght++] = lista->content[i++];
		lista = lista->next;
	}
	(*line)[lenght] = '\0';
}

void	treat_line(t_list **lista)
{
	t_list	*final_node;
	t_list	*temp;
	char	*last_content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_lstlast(*lista);
	if (!temp || !temp->content)
		return ;
	last_content = temp->content;
	ft_lstclear(lista);
	while (last_content[j] != '\0')
	{
		while (last_content[j] != '\n')
			j++;
		last_content[i++] = last_content[j++];
	}
	last_content[i] = '\0';
	final_node = ft_lstnew(last_content);
	ft_lstadd_back(lista, final_node);
}

char	*get_next_line(int fd)
{
	static t_list	*lista;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&lista, fd);
	if (!lista)
		return (NULL);
	make_line(lista, &line);
	treat_line(&lista);
	return (line);
}
