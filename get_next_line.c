/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/10 17:15:25 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_till_newline(int fd, char **remainder)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;
	char		*new_remainder;

	line = NULL;
	if (*remainder)
	{
		line = extract_line(*remainder, line);
		if (ft_strchr(*remainder, '\n'))
		{
			new_remainder = get_remainder(*remainder);
			free(*remainder);
			*remainder = new_remainder;
			return (line);
		}
		free(*remainder);
		*remainder = NULL;
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (bytes_read == 0)
	{
		free(line);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	while (!ft_strchr(buffer, '\n'))
	{
		line = extract_line(buffer, line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || BUFFER_SIZE <= 0)
			return (NULL);
		if (bytes_read == 0)
			return (line);
		buffer[bytes_read] = '\0';
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
		rest = ft_strdup(newline_pos + 1);
		return (rest);
	}
	return (NULL);
}

char	*extract_line(char *buffer, char *line)
{
	char	*newline_pos;
	char	*temp_line;
	char	*temp_buffer;

	if (!line)
		line = ft_strdup("");
	temp_buffer = ft_strdup(buffer);
	newline_pos = ft_strchr(temp_buffer, '\n');
	if (newline_pos && *temp_buffer != '\n')
		*(newline_pos + 1) = '\0';
	temp_line = ft_strdup(line);
	free(line);
	line = ft_strjoin(temp_line, temp_buffer);
	free(temp_line);
	free(temp_buffer);
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

// int	main(void)
// {
// 	int	fd;

// 	fd = open("empty.txt", O_RDONLY);
// 	printf("1:%s", get_next_line(fd));
// 	printf("2:%s", get_next_line(fd));
// 	printf("3:%s", get_next_line(fd));
// 	printf("4:%s", get_next_line(fd));
// 	printf("5:%s", get_next_line(fd));
// 	printf("6:%s", get_next_line(fd));
// 	return (0);
// }
