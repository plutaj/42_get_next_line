/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/12 19:42:17 by jpluta           ###   ########.fr       */
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
		line = extract_line(*remainder, line); // 55\0
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
	bytes_read = read(fd, buffer, BUFFER_SIZE); // buffer =  \ndopa\0
	if (bytes_read == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (bytes_read == 0)
	{
		free(line);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	while (!ft_strchr(buffer, '\n')) // oa\n55\0
	{
		line = extract_line(buffer, line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || BUFFER_SIZE <= 0)
			return (NULL);
		if (bytes_read == 0)
			return (line);
		buffer[bytes_read] = '\0';
	}
	line = extract_line(buffer, line); // line = 55\ndopa\0
	if (ft_strchr(buffer, '\n'))  // buffer =  \ndopa\0
		*remainder = get_remainder(buffer); // remainder = dopa\0
	return (line);
}

char	*get_remainder(char *buffer)
{
	// printf("%s", buffer);
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

char	*extract_line(char *buffer, char *line) //   buffer =  \ndopa\0
{												//   line	= 55\0
	char	*newline_pos;
	char	*temp_line;
	char	*temp_buffer;

	temp_line = NULL;
	if (!line)
		line = ft_strdup("");
	temp_buffer = ft_strdup(buffer);  // temp_buffer = \ndopa\0
	newline_pos = ft_strchr(temp_buffer, '\n');   // pointer na index 0
	if (newline_pos && ((*temp_buffer != '\n') || BUFFER_SIZE > 1))
		*(newline_pos + 1) = '\0'; // toto nezbehne
	temp_line = ft_strdup(line); // 55\0
	free(line);
	line = ft_strjoin(temp_line, temp_buffer); // maybe switch params // line = 55\ndopa\0
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

int	main(void)
{
	int	fd;

	fd = open("empty.txt", O_RDONLY);
	printf("1:%s", get_next_line(fd));
	printf("2:%s", get_next_line(fd));
	printf("3:%s", get_next_line(fd));
	printf("4:%s", get_next_line(fd));
	printf("5:%s", get_next_line(fd));
	printf("6:%s", get_next_line(fd));
	return (0);
}
