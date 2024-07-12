#include <fcntl.h>
#include "get_next_line_bonus.h"
#include <stdio.h>

int	ft_strncmp(char	*s1, char	*s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	else
		return (0);
}

int main(void) {
	int		fd_1;
	int		fd_2;
	char	*next_line;

	fd_1 = open("text_files/big_line_with_nl", O_RDONLY);
	fd_2 = open("ultima.txt", O_RDONLY);
 	while ((next_line = get_next_line(fd_1)) != 0)
	{
		printf("%s", next_line);
		free(next_line);
	}
 	while ((next_line = get_next_line(fd_2)) != 0)
	{
		printf("%s", next_line);
		free(next_line);
	}
	close(fd_1);
	close(fd_2);
	return (0);
}
