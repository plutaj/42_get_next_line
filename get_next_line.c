/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/01 19:15:05 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*newline_position(char *newline_pos, char *remainder,
			char *temp_line, char *line, char *buffer);
char	*check_bytesread(ssize_t bytes_read, char *line);
char	*check_reminder(char *remainder, char *line);


char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char 		buffer[BUFFER_SIZE + 1];
	char 		*line = NULL;
	ssize_t 	bytes_read;
	char 		*newline_pos;
	char 		*temp_line;

	line = check_reminder(remainder, line);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		check_bytesread(bytes_read, line);
		if (line == NULL)
			return (NULL);
		buffer[bytes_read] = '\0';
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
			return (newline_position(newline_pos, remainder,
						temp_line, line, buffer));
		else
			line = newline_position(newline_pos, remainder,
						temp_line, line, buffer);
	}
}

char	*check_reminder(char *remainder, char *line)
{
	if (remainder)
	{
		line = ft_strdup(remainder);
		free(remainder);
		remainder = NULL;
	}
	else
		line = ft_strdup("");
	return (line);
}

char	*check_bytesread(ssize_t bytes_read, char *line)
{
	if (bytes_read < 0)
	{
		free(line);
		return (NULL);
	}
	else if (bytes_read == 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	else if (bytes_read == 0)
		return (line);
	return (line);
}

char	*newline_position(char *newline_pos, char *remainder,
			char *temp_line, char *line, char *buffer)
{
	if (newline_pos)
	{
		*newline_pos = '\0';
		remainder = ft_strdup(newline_pos + 1);
		temp_line = ft_strjoin(line, buffer);
		free(line);
		return (temp_line);
	}
	else
	{
		temp_line = ft_strjoin(line, buffer);
		free(line);
		line = temp_line;
	}
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("readme.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	return (0);
}
