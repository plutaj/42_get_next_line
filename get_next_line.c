/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/20 18:18:50 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_remainder(char **remainder)
{
	char	*line;
	char	*newline_pos;
	char	*new_remainder;

	line = NULL;
	newline_pos = NULL;
	new_remainder = NULL;
	line = extract_line(*remainder, line);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		new_remainder = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = new_remainder;
		return (line);
	}
	free(*remainder);
	*remainder = NULL;
	return (line);
}

char	*read_till_newline(int fd, char **remainder)
{
	char	*buffer;
	char	*line;
	ssize_t	bytes_read;

	line = NULL;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (*remainder)
	{
		if (ft_strchr(*remainder, '\n'))
		{
			line = process_remainder(remainder);
			free (buffer);
			return (line);
		}
		line = process_remainder(remainder);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		line = extract_line(buffer, line);
		if (ft_strchr(buffer, '\n'))
		{
			*remainder = get_remainder(buffer);
			break ;
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read == 0)
	{
		if (line && *line == '\0')
		{
			free(line);
			return (NULL);
		}
	}
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

	temp_line = NULL;
	if (!line)
		line = ft_strdup("");
	temp_buffer = ft_strdup(buffer);
	newline_pos = ft_strchr(temp_buffer, '\n');
	if (newline_pos)
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
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_till_newline(fd, &remainder);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*s;

// 	s = NULL;
// 	fd = open("empty.txt", O_RDONLY);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free(s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free(s);

// 	close(fd);
// 	// printf("7:%s", get_next_line(fd));
// 	// printf("8:%s", get_next_line(fd));
// 	// printf("9:%s", get_next_line(fd));
// 	// printf("10:%s", get_next_line(fd));
// 	// printf("11:%s", get_next_line(fd));
// 	// printf("12:%s", get_next_line(fd));
// 	// printf("13:%s", get_next_line(fd));
// 	return (0);
// }
