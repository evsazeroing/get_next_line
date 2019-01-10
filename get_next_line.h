#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "libft/libft.h"

# define BUFF_SIZE 35

typedef struct		s_file
{
	char		*data;
	int		fd;
	struct s_file	*next;
}			t_file;

int			get_next_line(const int fd, char **line);

#endif
