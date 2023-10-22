/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:37:12 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/22 03:04:35 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error(char *msg)
{
	fprintf(stderr, "\nError:  %s\n", msg);
	return (EXIT_FAILURE);
}

static int	num_cases(int n)
{
	int				i;
	unsigned int	num;

	i = 1;
	num = n;
	if (n < 0)
	{
		i = 2;
		num = -n;
	}
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*tab;
	int				i;

	tab = malloc((num_cases(n)) + 1);
	if ((!tab))
		return (NULL);
	i = num_cases(n);
	num = n;
	if (n < 0)
	{
		num = -n;
		tab[0] = '-';
	}
	tab[i] = '\0';
	tab[i - 1] = '0';
	while (num > 0)
	{
		i--;
		tab[i] = num % 10 + 48;
		num /= 10;
	}
	return (tab);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s3 == NULL)
		return (0);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}
