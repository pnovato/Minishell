/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:14:45 by pnovato-          #+#    #+#             */
/*   Updated: 2024/10/25 13:14:45 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	unsigned char		*ptr_dest;

	ptr = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		while (n--)
			ptr_dest[n] = ptr[n];
	}
	else
	{
		while (n--)
			*ptr_dest++ = *ptr++;
	}
	return (dest);
}
