/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:38:07 by davidga2          #+#    #+#             */
/*   Updated: 2023/05/09 18:01:17 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char **ptr)
{	
	if (!*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

static char	*ft_clear_stash(char *stash)
{
	char	*ptr;
	size_t	pos;
	char	*cleaned_stash;

	ptr = ft_strchr(stash, '\n');
	pos = ft_strlen(stash) - ft_strlen(ptr) + 1;
	cleaned_stash = ft_substr(stash, pos, -1);
	ft_free(&stash);
	if (!cleaned_stash)
		return (0);
	return (cleaned_stash);
}

static char	*ft_make_this_line(char *stash)
{
	char	*ptr;
	ssize_t	pos;
	char	*total_line;

	ptr = ft_strchr(stash, '\n');
	pos = -1;
	if (ft_strchr(stash, '\n'))
		pos = ft_strlen(stash) - ft_strlen(ptr) + 1;
	total_line = ft_substr(stash, 0, pos);
	if (!total_line)
		return (0);
	return (total_line);
}

static char	*ft_read_file(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_return;
	char	*aux;

	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	while (!ft_strchr(stash, '\n'))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (ft_free(&stash), NULL);
		read_return = read(fd, buffer, BUFFER_SIZE);
		aux = stash;
		stash = ft_strjoin_gnl(stash, buffer);
		ft_free(&aux);
		if (!stash)
			return (ft_free(&buffer), NULL);
		ft_free(&buffer);
		if (read_return == 0 && ft_strlen(stash))
			return (aux = ft_substr(stash, 0, -1), ft_free(&stash), aux);
		if (read_return <= 0)
			return (ft_free(&stash), NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (0);
	line = ft_make_this_line(stash);
	if (!line)
		return (ft_free(&stash), NULL);
	if (ft_strchr(stash, '\n'))
	{
		stash = ft_clear_stash(stash);
		if (!stash)
			return (ft_free(&line), NULL);
	}
	else
		ft_free(&stash);
	return (line);
}
/*
int main(void)
{
	int		fd = open("hola.txt", O_RDONLY);
	char	*line;
//	char	str[1];

//	str[0] = '\0';
//	line = str;
//	while (line)
//	{
//		line = get_next_line(fd);
//		write(1, line, ft_strlen(line));
//	}
	
	printf("%s", line = get_next_line(fd));

	close(fd);
//	system("leaks a.out");
	return (0);
}*/
