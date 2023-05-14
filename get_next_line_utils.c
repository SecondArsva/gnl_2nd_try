/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:33:38 by davidga2          #+#    #+#             */
/*   Updated: 2023/05/09 03:33:57 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *) malloc(count * size);
	if (!ptr)
		return (0);
	while (i < (count * size))
	{
		((char *) ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	character;

	i = 0;
	character = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == character)
			return ((char *) &s[i]);
		i++;
	}
	if (character == '\0')
		return ((char *) &s[i]);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*new_ptr;

	j = 0;
	if (!s)
		return (0);
	if (start < ft_strlen(s))
	{
		if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
		new_ptr = ft_calloc(len + 1, sizeof(char));
		if (!new_ptr)
			return (0);
		while (s[start] != '\0' && j < len)
		{
			new_ptr[j] = s[start + j];
			j++;
		}
		new_ptr[j] = '\0';
		return (new_ptr);
	}
	new_ptr = ft_calloc(1, sizeof(char));
	if (!new_ptr)
		return (0);
	return (new_ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new_ptr;
	size_t	i;
	size_t	j;

	new_ptr = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!new_ptr)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_ptr[i + j] = s2[j];
		j++;
	}
	return (new_ptr);
}
