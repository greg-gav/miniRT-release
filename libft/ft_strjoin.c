/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:37:17 by utygett           #+#    #+#             */
/*   Updated: 2022/01/16 16:16:03 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(*str) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (*s1)
	{
		*(str + i) = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		*(str + i) = *s2;
		s2++;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
