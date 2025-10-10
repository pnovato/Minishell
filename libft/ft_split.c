/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:09:34 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/13 15:31:15 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count_words;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count_words);
}

char	*modified_strdup(const char *str, char c)
{
	int		n;
	int		i;
	char	*str2;

	if (!str)
		return (NULL);
	n = 0;
	while (str[n] && (char)str[n] != c)
		n++;
	str2 = malloc((n + 1) * sizeof(char));
	if (str2 == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	x;
	char			**ptr;

	i = count_word(s, c);
	ptr = malloc(sizeof(char *) * (i + 1));
	j = 0;
	x = 0;
	if (!ptr)
		return (NULL);
	while (s[j] && x < i)
	{
		while (s[j] && s[j] == c)
			j++;
		ptr[x] = modified_strdup(&s[j], c);
		if (!ptr[x++])
			return (ft_free(ptr), NULL);
		while (s[j] && s[j] != c)
			j++;
	}
	ptr[x] = NULL;
	return (ptr);
}
