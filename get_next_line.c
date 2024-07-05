#include "get_next_line.h"

char	*ft_strjoin(char const *old, char const *new)
{
	char	*ptr;
	size_t	l1;
	size_t	l2;
	size_t	lt;

	l1 = ft_strlen(old);
	l2 = ft_strlen(new);
	lt = l1 + l2;
	ptr = (char *) malloc(lt * sizeof(char) + 1);
	if (ptr == NULL)
		return (NULL);
	while (*old)
		*ptr++ = *old++;
	while (*new)
		*ptr++ = *new++;
	*ptr = '\0';
    free(old);
	return (ptr - lt);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;
    int     i;

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
	return (ptr);
}

void    get_array_from_reads(int fd, char *leftovers)
{
    char    *read_buffer;
    int     bytes_read;
    
    bytes_read = 1;
    while(bytes_read > 0)
    {
        bytes_read  = read(fd, read_buffer, BUFFER_SIZE);
        ft_strjoin();
    }
    return (bytes_read);
}

char    *get_next_line(int fd)
{
    char        *return_buffer;
    static char *leftovers;
    int         bytes_read;

    if (!leftovers)
    {
        leftovers = (char *) malloc(1);
		leftovers[0] = '\0';
    }

}