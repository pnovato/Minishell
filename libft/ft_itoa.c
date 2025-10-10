/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:41:32 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/13 13:09:22 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	n_or_p(int n)
{
	if (n >= 0)
		return (0);
	return (1);
}

int	count_numbers(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	long			x;
	int				neg;
	int				size_string;

	x = n;
	neg = n_or_p(x);
	if (neg == 1)
		x = x * -1;
	size_string = count_numbers(x);
	ptr = malloc(sizeof(char) * (neg + size_string + 1));
	if (!ptr)
		return (NULL);
	if (neg == 1)
		ptr[0] = '-';
	ptr[size_string + neg] = '\0';
	while (size_string > 0)
	{
		ptr[(size_string - 1) + neg] = (x % 10) + '0';
		x = x / 10;
		size_string--;
	}
	return (ptr);
}
