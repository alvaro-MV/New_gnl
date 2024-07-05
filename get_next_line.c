/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:37:28 by alvmoral          #+#    #+#             */
/*   Updated: 2024/07/05 18:23:01 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/* char	*ft_strdup(char *s1, char c)
{
	char	*ptr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (s1[len] && s1[len] != c)
		len++;
	ptr = (char *) malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, len + 2);
	while (i < (len + 1))
	{
		ptr[i] = s1[i];
		i++;
	}
	if (s1[len] != c && len > 0)
		ptr[len] = c;
	return (ptr);
}*/
void    *ft_memcpy(void *dst, const void *src, size_t n)
{
        unsigned char   *ptrdst;
        unsigned char   *ptrsrc;
        size_t                  i;

        if (dst == NULL && src == NULL)
                return (NULL);
        ptrdst = (unsigned char *) dst;
        ptrsrc = (unsigned char *) src;
        i = 0;
        while (n--)
        {
                ptrdst[i] = ptrsrc[i];
                i++;
        }
        return (ptrdst);
}

char    *ft_strdup(const char *s1)
{
        char    *ptr;
        int             len;

        len = 0;
        while (s1[len])
                len++;
        ptr = (char *) malloc(len + 1);
        if (ptr == NULL)
                return (NULL);
        ft_memcpy(ptr, s1, len + 1);
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
		if (bytes_read == 0 || bytes_read < 0)
			return (0);
		read_buffer[bytes_read] = '\0';
		//printf("%s\n-------------\n", read_buffer);
		ft_lstadd_back(&last_node, ft_strdup(read_buffer));
		eol_present = (ft_strchr(read_buffer, '\n') != NULL);
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
		if (*lst_content == '\n')
		{
			return_buffer[i++] = *lst_content++;
			break ;
		}
		lst = lst->next;
	}
	return_buffer[i] = '\0';
	//printf("return_buffer: %s", return_buffer);
	i = 0;
	while (*lst_content)
		after_eol[i++] = *lst_content++;
	after_eol[i] = '\0';
	//printf("after_eol: %s\n", after_eol);
	ft_lstclear(&first_node);
}

char	*get_next_line(int fd)
{
	static char	after_eol[BUFFER_SIZE];
	char		*return_buffer;
	t_list		*lst;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	lst = NULL;
	bytes_read = 1;
	ft_lstadd_front(&lst, ft_strdup(after_eol));
	if (ft_strchr(after_eol, '\n') == NULL)
		bytes_read = get_lst_from_reads(fd, &lst);
	return_buffer = (char *) malloc(BUFFER_SIZE * ft_lstsize(lst) + 1);
	ft_bzero(return_buffer, BUFFER_SIZE * (ft_lstsize(lst) - 1) + 1);
	fill_buffers(lst, return_buffer, after_eol);
	if (bytes_read == 0)
		after_eol[0] = '\0';
	if (return_buffer[0] == '\0' && bytes_read <= 0)
	{
		free(return_buffer);
		return (NULL);
	}
	return (return_buffer);
}
