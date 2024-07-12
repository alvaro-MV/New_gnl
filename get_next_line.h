/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:43:19 by alvmoral          #+#    #+#             */
/*   Updated: 2024/07/12 14:00:07 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(char *s1);
int		get_lst_from_reads(int fd, t_list **lst);
char	*fill_buffers(t_list *lst, char *return_buffer, char *after_eol);
char	*ft_strchr(char *s, int c);
void	ft_lstadd_back(t_list **lst, char *content);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);

#endif
