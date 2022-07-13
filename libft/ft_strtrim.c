/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:12:53 by utygett           #+#    #+#             */
/*   Updated: 2022/01/16 16:16:15 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		j;
	int		i;

	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (j && (ft_strchr(set, *(s1 + j - 1))))
		j--;
	if (!j)
		return (ft_calloc(1, 1));
	i = 0;
	while (ft_strchr(set, *(s1 + i)))
		i++;
	return (ft_substr(s1, i, j - i));
}
