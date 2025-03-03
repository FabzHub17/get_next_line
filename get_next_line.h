#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

char	*get_next_line(int fd);
char	*read_to_buffer(int fd, char *stash);
char	*extract_line(char *stash);
char	*update_buffer(char *stash);

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*join_and_free(char *stash, char *buffer);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
#endif
