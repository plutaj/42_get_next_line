/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/09 21:22:46 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_till_newline(int fd, char **remainder) //a    // 5
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1 || BUFFER_SIZE <= 0 || bytes_read == 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	if (*remainder)
	{
		line = extract_line(*remainder, line);
		if (ft_strchr(*remainder, '\n'))  // Check if remainder has a newline
		{
			char *new_remainder = get_remainder(*remainder);
			free(*remainder);  // Free old remainder
			*remainder = new_remainder;
			return (line);
		}
		free(*remainder);
	}
	while (!ft_strchr(buffer, '\n')) // && !ft_strchr(buffer, '\0')
	{
		line = extract_line(buffer, line);
		bytes_read = read(fd, buffer, BUFFER_SIZE); //b
		if (bytes_read == -1 || BUFFER_SIZE <= 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			return (line);
	}
	line = extract_line(buffer, line);
	if (ft_strchr(buffer, '\n'))
		*remainder = get_remainder(buffer);
	return (line);
}

char	*get_remainder(char *buffer)
{
	char	*newline_pos;
	char	*rest;

	newline_pos = ft_strchr(buffer, '\n');
	rest = NULL;
	if (newline_pos)
	{
		*newline_pos = '\0';
		rest = ft_strdup(newline_pos + 1);
		return (rest);
	}
	return (NULL);
}

char	*extract_line(char *buffer, char *line)
{
	char	*newline_pos;
	char	*temp_line;

	if (!line)
		line = ft_strdup("");
	temp_line = NULL;
	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos && *buffer != '\n') //&& *buffer != '\n'
		*newline_pos = '\0';
	temp_line = ft_strdup(line);
	free(line);
	line = ft_strjoin(temp_line, buffer);
	free(temp_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	line = NULL;
	line = read_till_newline(fd, &remainder);
	return (line);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return i;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	int	fd;

	fd = open("empty.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
