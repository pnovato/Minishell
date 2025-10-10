/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnovato- <pnovato-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:41:09 by pnovato-          #+#    #+#             */
/*   Updated: 2024/11/22 19:48:15 by pnovato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_myputstr(const char *var);
int	ft_myputnptr(long unsigned int var);
int	ft_myputchar(char c);
int	ft_myputnbr(int var);
int	ft_myputhex(unsigned long var);
int	ft_myputhex_upper(unsigned long var);
int	ft_myputnbr_u(unsigned int var);
int	ft_condition(va_list args, char s);
int	ft_printf(const char *format, ...);

#endif
