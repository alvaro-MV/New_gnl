/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:37:34 by alvmoral          #+#    #+#             */
/*   Updated: 2024/06/21 19:30:01 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	if (n > 0)
	{
		while (n--)
		{
			*(char *) s = 0;
			s++;
		}
	}
}

char	*ft_strdup(char *s1, char c)
{
	char	*ptr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s1[len] && s1[len] != c)
		len++;
	ptr = (char *) malloc(sizeof(char) * (len + 2));
	ft_bzero(ptr, len + 2);
	if (ptr == NULL)
		return (NULL);
	while (i < (len + 1))
	{
		ptr[i] = s1[i];
		i++;
	}
	if (s1[len] != c && len > 0)
		ptr[len] = c;
	return (ptr);
}

int	get_lst_from_reads(int fd, t_list **lst)
{
	char	read_buffer[BUFFER_SIZE];
	t_list	*last_node;
	int		bytes_read;
	int		eol_present;

	bytes_read = 1;
	ft_bzero(read_buffer, BUFFER_SIZE);
	last_node = *lst;
	while (bytes_read)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (0);
		else if (bytes_read < 0)
			return (0);
		read_buffer[bytes_read] = '\0';
		ft_lstadd_back(lst, ft_strdup(read_buffer, '\0'));
		eol_present = ft_strchr(read_buffer, '\n') != NULL;
		if (eol_present)
			break ;
		last_node = last_node->next;
	}
	return (bytes_read);
}

void	fill_buffers(t_list *lst, char *return_buffer, char *after_eol)
{
	t_list	*first_node;
	char	*lst_content;
	int		i;

	if (lst == NULL)
		return ;
	i = 0;
	first_node = lst;
	while (lst)
	{
		lst_content = lst->content;
		while (*lst_content && *lst_content != '\n')
			return_buffer[i++] = *lst_content++;
		return_buffer[i] = '\n';
		if (*lst_content++ == '\n')
			break ;
		lst = lst->next;
	}
	i = 0;
	while (*lst_content)
		after_eol[i++] = *lst_content++;
	after_eol[i] = '\0';
	ft_lstclear(&first_node);
}

char	*get_next_line(int fd)
{
	static char	after_eol[FD_SETSIZE][BUFFER_SIZE];
	char		*return_buffer;
	t_list		*lst;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	lst = NULL;
	bytes_read = 1;
	if (after_eol[fd] != NULL)
		ft_lstadd_front(&lst, ft_strdup(after_eol[fd], '\0'));
	if (ft_strchr(after_eol[fd], '\n') == NULL)
		bytes_read = get_lst_from_reads(fd, &lst);
	return_buffer = (char *) malloc(BUFFER_SIZE * ft_lstsize(lst) + 2);
	ft_bzero(return_buffer, BUFFER_SIZE * (ft_lstsize(lst) - 1) + 2);
	fill_buffers(lst, return_buffer, after_eol[fd]);
	if (bytes_read == 0)
		after_eol[fd][0] = '\0';
	if (return_buffer[0] == '\n' && bytes_read == 0)
	{
		free(return_buffer);
		return (NULL);
	}
	return (return_buffer);
}
