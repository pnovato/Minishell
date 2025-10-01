/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:47:06 by pnovato-          #+#    #+#             */
/*   Updated: 2024/10/27 19:47:06 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1 = (const unsigned char *)s1;
	const unsigned char	*ptr2 = (const unsigned char *)s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			if (ptr1[i] > ptr2[i])
				return (1);
			return (-1);
		}
		i++;
	}
	return (0);
}
