/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:43:19 by alvmoral          #+#    #+#             */
/*   Updated: 2024/07/01 18:57:36 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2545
# endif
# define FILE_PATH "textos/ejemplo.txt"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
void	ft_lstadd_front(t_list **lst, char *content);
void	ft_lstadd_back(t_list **lst, char *content);
void	ft_lstclear(t_list **lst);
int		ft_lstsize(t_list *lst);

#endif
