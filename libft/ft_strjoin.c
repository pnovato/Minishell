/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:12:03 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/11 15:08:04 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	x;

	i = (unsigned int)ft_strlen(s1);
	j = (unsigned int)ft_strlen(s2);
	ptr = malloc(sizeof(char) * ((i + j) + 1));
	if (!ptr)
		return (NULL);
	x = 0;
	while (x < i)
	{
		ptr[x] = s1[x];
		x++;
	}
	i = 0;
	while (i < j)
	{
		ptr[x] = s2[i];
		x++;
		i++;
	}
	ptr[x] = '\0';
	return (ptr);
}
