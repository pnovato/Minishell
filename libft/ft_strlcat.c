/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:08:59 by pnovato-          #+#    #+#             */
/*   Updated: 2024/10/26 12:08:59 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	c;

	len_dst = ft_strlen(dst);
	c = 0;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	while (src[c] && (len_dst + c) < (size - 1))
	{
		dst[len_dst + c] = src[c];
		c++;
	}
	dst[len_dst + c] = '\0';
	return (len_dst + ft_strlen(src));
}
