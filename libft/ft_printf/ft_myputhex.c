/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:28:15 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 20:00:31 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_myputhex(unsigned long var)
{
	char	*hex;
	int		count;

	hex = NULL;
	count = 0;
	hex = "0123456789abcdef";
	if (var > 15)
		count += ft_myputhex(var / 16);
	count += ft_myputchar(hex[var % 16]);
	return (count);
}
