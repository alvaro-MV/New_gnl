/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:37:28 by alvmoral          #+#    #+#             */
/*   Updated: 2024/07/08 11:52:43by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		len;
	int		i;

	if (s1 == NULL)
		return (NULL);
	len = 0;
	i = 0;
	while (s1[len])
		len++;
	ptr = (char *) malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	get_lst_from_reads(int fd, t_list **lst)
{
	char	*read_buffer;
	int		bytes_read;
	int		eol_present;

	bytes_read = 1;
	read_buffer = (char *) malloc(BUFFER_SIZE * sizeof(char) + 1);
	while (bytes_read)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read < 0)
			return (free(read_buffer), bytes_read);
		read_buffer[bytes_read] = '\0';
		ft_lstadd_back(lst, ft_strdup(read_buffer));
		if (*lst == NULL)
		{
			ft_lstclear(lst);
			return (-1);
		}
		eol_present = (ft_strchr(read_buffer, '\n') != NULL);
		if (eol_present)
			break ;
	}
	free(read_buffer);
	return (bytes_read);
}

char	*fill_return_buffer(t_list *lst, char *return_buffer, int bytes_read)
{
	t_list	*first_node;
	int		i;
	char	*lst_content;

	if (lst == NULL)
		return NULL;
	i = 0;
	first_node = lst;
	while (lst)
	{
		lst_content = lst->content;
		while (*lst_content && *lst_content != '\n')
			return_buffer[i++] = *lst_content++;
		if (*lst_content == '\n')
		{
			return_buffer[i++] = *lst_content++;
			break ;
		}
		lst = lst->next;
	}
	return_buffer[i] = '\0';
	ft_lstclear(&first_node);
	if (return_buffer[0] == '\0' && bytes_read <= 0)
		return (free(return_buffer), NULL);
	return (return_buffer);
}

char	*fill_after_eol(t_list *lst, char	*after_eol)
{
	char	*lst_content;
	//t_list	*first_node;
	t_list	*holder;
	
	free(after_eol);
	//first_node = lst;
	while (lst != NULL)
	{
		holder = lst;
		lst = lst->next;
	}
	lst_content = ft_strchr(holder->content, '\n');
	if (lst_content == NULL)
		ft_strdup("\0");
	else
		after_eol = ft_strdup(lst_content);
	//ft_lstclear(&first_node);
	return (after_eol);
}


//Cuando


//char	*fill_buffers(t_list *lst, char *return_buffer, char *after_eol)
//{
	//t_list	*first_node;
	//char	*lst_content;
	//int		i;

	//free(after_eol);
	//if (lst == NULL)
		//return NULL;
	//i = 0;
	//first_node = lst;
	//while (lst)
	//{
		//lst_content = lst->content;
		//while (*lst_content && *lst_content != '\n')
			//return_buffer[i++] = *lst_content++;
		//if (*lst_content == '\n')
		//{
			//return_buffer[i++] = *lst_content++;
			//break ;
		//}
		//lst = lst->next;
	//}
	//return_buffer[i] = '\0';
	//after_eol = ft_strdup(lst_content); //Este falta por gestionar.
	//ft_lstclear(&first_node);
	//return (after_eol);
//}

char	*get_next_line(int fd)
{
	static char	*after_eol;
	char		*return_buffer;
	t_list		*lst;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	lst = NULL;
	bytes_read = 1;
	if (after_eol != NULL)
		ft_lstadd_back(&lst, ft_strdup(after_eol)); 
	if (ft_strchr(after_eol, '\n') == NULL) 
		bytes_read = get_lst_from_reads(fd, &lst);
	if (bytes_read == -1)
		return (NULL);
	return_buffer = ft_calloc(ft_lstsize(lst) + 1, BUFFER_SIZE);
	if (return_buffer == NULL)
		return (free(after_eol), NULL);
	after_eol = fill_after_eol(lst, after_eol); 
	if (after_eol == NULL)
		return (free(return_buffer), NULL);
	return_buffer = fill_return_buffer(lst, return_buffer, bytes_read);
	if (return_buffer == NULL)
		return (free(after_eol), NULL);
	return (return_buffer);
}
