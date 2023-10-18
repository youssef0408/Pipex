/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:37:12 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/17 21:30:40 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(int code,char *msg)
{
	printf("\033[31m Error:(%s) %s",ft_itoa(code),msg);
	exit(EXIT_FAILURE);
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
