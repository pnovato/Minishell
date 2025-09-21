/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:36:15 by pnovato-          #+#    #+#             */
/*   Updated: 2024/10/30 15:49:21 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*ptr;
	char				*ptr_dest;
	size_t				i;

	ptr = (const unsigned char *)src;
	ptr_dest = (char *)dest;
	i = 0;
	if (!ptr && !ptr_dest)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr[i];
		i++;
	}
	return (dest);
}
