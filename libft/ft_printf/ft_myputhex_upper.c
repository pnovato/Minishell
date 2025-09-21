/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputhex_upper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:49:52 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 20:05:10 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_myputhex_upper(unsigned long var)
{
	char	*hex;
	int		count;

	hex = NULL;
	count = 0;
	hex = "0123456789ABCDEF";
	if (var > 15)
		count += ft_myputhex_upper(var / 16);
	count += ft_myputchar(hex[var % 16]);
	return (count);
}
