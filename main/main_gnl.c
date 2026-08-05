#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		number;

	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 40;

	number = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Línea %d: [%s]", number, line);
		free(line);
		number++;
		line = get_next_line(fd);
	}
	printf("get_next_line devuelve NULL\n");
	if (fd > 2)
		close(fd);
	return (0);
}
