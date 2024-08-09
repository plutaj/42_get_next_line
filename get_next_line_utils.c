/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:23:43 by jpluta            #+#    #+#             */
/*   Updated: 2024/08/09 17:45:31 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	char *dest;
	unsigned int i;

	dest = (char *)malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;

	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t i;
	char *str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *smn;
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	smn = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!smn)
		return (NULL);
	while (s1[j])
		smn[i++] = s1[j++];
	j = 0;
	while (s2[j])
		smn[i++] = s2[j++];
	smn[i] = '\0';
	return (smn);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	a;

	i = 0;
	a = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return ((char *)&s[i]);
		i++;
	}
	if (a == '\0')
		return ((char *)&s[i]);
	return (0);
}
