/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputnptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:18:11 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 19:58:34 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_myputnptr(long unsigned int var)
{
	unsigned long	addr;
	int				count;

	count = 0;
	if (!var)
		return (ft_myputstr("(nil)"));
	addr = (unsigned long)var;
	count += ft_myputstr("0x");
	count += ft_myputhex(addr);
	return (count);
}
