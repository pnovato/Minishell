/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputnbr_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:24:45 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 19:18:00 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_myputnbr_u(unsigned int var)
{
	int	count;

	count = 0;
	if (var > 9)
		count += ft_myputnbr_u(var / 10);
	count += ft_myputchar((var % 10) + '0');
	return (count);
}
