/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlessa-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:13:34 by mlessa-s          #+#    #+#             */
/*   Updated: 2024/08/13 22:46:04 by mlessa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
/*
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	main()
{
	char	test1[] = "ABCD";
	char	test2[] = "AbCD";
	printf("%d", ft_strcmp(test1, test2));
	return (0);
}*/
