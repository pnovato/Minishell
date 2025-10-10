/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:45:11 by pnovato-          #+#    #+#             */
/*   Updated: 2024/12/06 14:44:44 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

int	ft_condition(va_list args, char s)
{
	if (s == 'c')
		return (ft_myputchar(va_arg(args, int)));
	else if (s == 's')
		return (ft_myputstr(va_arg(args, const char *)));
	else if (s == 'p')
		return (ft_myputnptr((unsigned long)va_arg(args, void *)));
	else if (s == 'd' || s == 'i')
		return (ft_myputnbr(va_arg(args, int)));
	else if (s == 'u')
		return (ft_myputnbr_u(va_arg(args, unsigned int)));
	else if (s == 'x')
		return (ft_myputhex(va_arg(args, unsigned int)));
	else if (s == 'X')
		return (ft_myputhex_upper(va_arg(args, unsigned int)));
	else if (s == '%')
		return (ft_myputchar('%'));
	else
		return (ft_myputchar(s));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				count += ft_condition(args, *format);
		}
		else
			count += ft_myputchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}
