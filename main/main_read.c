#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define READ_SIZE 4

int	main(int argc, char **argv)
{
	int		fd;
	int		bytes_read;
	int		number;
	char	buffer[READ_SIZE + 1];

	if (argc == 1)
		fd = 0;
	else
		fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error al abrir el archivo\n");
		return (1);
	}
	number = 1;
	bytes_read = read(fd, buffer, READ_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		printf("read bloque %d, %d bytes: [%s]\n",
			number, bytes_read, buffer);
		number++;
		bytes_read = read(fd, buffer, READ_SIZE);
	}
	printf("read devuelve %d\n", bytes_read);
	if (fd != 0)
		close(fd);
	return (0);
}
