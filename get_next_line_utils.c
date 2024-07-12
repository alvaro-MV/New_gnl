/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:09 by alvaro            #+#    #+#             */
/*   Updated: 2024/07/12 12:59:05 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	if (s == NULL)
		return (NULL);
	c = (char) c;
	while (*s)
	{
		if (*s == c)
			return ((char *) s + 1);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	else
		return (0);
}

void    *ft_calloc(size_t count, size_t size)
{
	void    *ptr;

	if (count && size && SIZE_MAX / count < size)
			return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
			return (NULL);
	if (size > 0)
	{
		while (size--)
		{
			*(char *) ptr = 0;
			ptr++;
		}
	}
	return (ptr);
}

void	ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*list;
	t_list	*holder;
	t_list	*new_n;

	new_n = (t_list *) malloc(sizeof(t_list));
	if (new_n == NULL || !content)
	{
		ft_lstclear(lst);
		return ;
	}
	new_n->content = content;
	new_n->next = NULL;
	list = *lst;
	if (list == NULL)
		*lst = new_n;
	if (list != NULL)
	{
		while (list != NULL)
		{
			holder = list;
			list = list->next;
		}
		holder->next = new_n;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*holder;
	t_list	*list;

	if (lst)
	{
		list = *lst;
		while (list != NULL)
		{
			holder = list;
			list = list->next;
			free(holder->content);
			free(holder);
		}
	}
}

int	ft_lstsize(t_list *lst)
{
	int	contador;

	contador = 0;
	while (lst != NULL)
	{
		contador++;
		lst = lst->next;
	}
	return (contador);
}
