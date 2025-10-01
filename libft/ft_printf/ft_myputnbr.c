/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:59:41 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 16:42:49 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_myputnbr(int var)
{
	int	count;

	count = 0;
	if (var == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (var < 0)
	{
		count += ft_myputchar('-');
		var = -var;
	}
	if (var > 9)
	{
		count += ft_myputnbr(var / 10);
	}
	count += ft_myputchar((var % 10) + '0');
	return (count);
}
