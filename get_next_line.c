/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:40 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/04 17:15:00 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char 		buffer[BUFFER_SIZE + 1];
	char 		*line;
	ssize_t 	bytes_read;
	char 		*newline_pos;
	char 		*temp_line;

	line = NULL;
	newline_pos = NULL;
	temp_line = NULL;
	line = check_remainder(remainder, line, temp_line);
	// if (*line != '\0')
	// 	return (line);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			return (line);
		buffer[BUFFER_SIZE] = '\0';
		newline_pos = ft_strchr(buffer, '\n');
		if (newline_pos)
		{
			*newline_pos = '\0';
			remainder = ft_strdup(newline_pos + 1);
			temp_line = ft_strdup(line);
			free(line);
			line = ft_strjoin(temp_line, buffer);
			free(temp_line);
			return (line);
		}
		else
		{
			if (*line != '\0')
			{
				temp_line = ft_strdup(line);
				free(line);
				line = ft_strjoin(temp_line, buffer);
				free(temp_line);
			}
			else
			{
				free(line);
				line = ft_strdup(buffer);
			}
		}
	}
	return (line);
}

char	*check_remainder(char *remainder, char *line, char *temp_line)
{
	char	*newline_pos;

	newline_pos = NULL;
	if (remainder)
	{
		newline_pos = ft_strchr(remainder, '\n');
		if (newline_pos)
		{
			temp_line = ft_strdup(remainder);
			*newline_pos = '\0';
			line = ft_strdup(remainder);
			free(remainder);
			remainder = ft_strdup(temp_line);
			free(temp_line);
		}
		else
		{
			line = ft_strdup(remainder);
			free(remainder);
			remainder = NULL;
		}
	}
	else
		line = ft_strdup("");
	return (line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("readme.txt", O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	// printf("%s\n", get_next_line(fd));
// 	return (0);
// }
