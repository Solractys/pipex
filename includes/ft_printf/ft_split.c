/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-s <csilva-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:17:04 by csilva-s          #+#    #+#             */
/*   Updated: 2025/08/15 19:09:13 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		**ft_split(char const *s, char c);
static	char	*ft_alloc_word(char *s, char c);
static	void	free_all(char **s, int size);
static	int	word_count(char const *s, char c);

static void	free_all(char **s, int size)
{
	while (size-- > 0)
		free(s[size]);
	free(s);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			flag = 1;
			i++;
		}
		else if (s[i] != c)
		{
			i++;
			if (flag > 0)
			{
				count++;
				flag = -1;
			}
		}
	}
	return (count);
}

static char	*ft_alloc_word(char *s, char c)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	dest = (char *)ft_calloc(i + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		words;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	words = word_count(s, c);
	result = (char **)ft_calloc(sizeof(char *), words + 1);
	if (!result)
	{
		free_all(result, words);
		return (NULL);
	}
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			result[j++] = ft_alloc_word((char *)&s[i], c);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (result);
}
