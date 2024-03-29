/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: analexan <analexan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:44:07 by analexan          #+#    #+#             */
/*   Updated: 2023/10/25 12:49:47 by analexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!str)
		return (NULL);
	str[gnl_strlen(s1) + gnl_strlen(s2)] = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		if (s2[j] == '\n')
			break ;
		j++;
	}
	return (str);
}

int	check_buffer(char *str)
{
	int	nl;
	int	i;
	int	j;

	nl = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (nl)
			str[j++] = str[i];
		if (str[i] == '\n')
			nl = 1;
		str[i++] = 0;
	}
	return (nl);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		return (NULL);
	}
	line = NULL;
	while (*buffer != 0 || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		temp = line;
		line = ft_strjoin_gnl(temp, buffer);
		free(temp);
		if (check_buffer(buffer))
			break ;
	}
	return (line);
}
/*
#include "get_next_line_utils.c"
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c && ./a.out
#include <stdio.h>
#include <fcntl.h>
void	gnl_tester(char *file, int lcnt)
{
	int		fd;
	char	*str;
	int		i;

	i = 1;
	if (!file || lcnt < 0)
		return ;
	fd = open(file, O_RDONLY);
	while (lcnt == 0 && (str = get_next_line(fd)))
	{
		printf("%i:\"%s\"\n", i, str);
		free(str);
		i++;
	}
	while (lcnt != 0 && i <= lcnt)
	{
		str = get_next_line(fd);
		printf("%i:\"%s\"\n", i, str);
		free(str);
		i++;
	}
	close(fd);
}
int main(void)
{
	gnl_tester("lines.txt", 0);
	return (0);
}
*/
