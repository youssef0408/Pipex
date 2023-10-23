/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:00:18 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/22 19:50:36 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(const char *s)
{
	int	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!n || dst == src)
		return (dst);
	if (!dst || !src)
		return (0);
	while (n > 0)
	{
		d[i] = s[i];
		n--;
		i++;
	}
	return (dst);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

bool	validation(int argc, char **argv)
{
	if (argc != 5)
	{
		error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2> \n");
		return false;
	}
		
	if (access(argv[1], O_RDONLY) < 0)
	{
		fprintf(stderr, "\nError: The file <%s> does not exist.\n\n", argv[1]);
		return false;
	}
	return true;
}
