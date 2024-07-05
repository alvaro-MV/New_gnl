/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvmoral <alvmoral@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:05:13 by alvmoral          #+#    #+#             */
/*   Updated: 2024/07/05 14:06:31 by alvmoral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

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

