/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:52:10 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/18 16:53:30 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*ft_cut_str(const char *str, char c)
{
	int		i;
	int		word_len;
	char	*new;

	i = 0;
	word_len = 0;
	while (str[i] == c)
		i++;
	while (str[i + word_len] != c && str[i + word_len] != '\0')
		word_len++;
	new = malloc(sizeof(char) * (word_len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void	*ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = ft_cut_str(s, c);
			if (!tab[i])
				return (ft_free(tab, i - 1));
			i++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s == NULL)
		return (0);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
