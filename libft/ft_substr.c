/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:27:01 by utygett           #+#    #+#             */
/*   Updated: 2022/01/16 16:16:17 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		p = ft_calloc(ft_strlen(s + start) + 1, sizeof(*p));
	else
		p = ft_calloc(len + 1, sizeof(*p));
	if (p == 0)
		return (NULL);
	while (*(s + start) && len > 0)
	{	
		*(p + i) = *(s + start);
		s++;
		i++;
		len --;
	}
	return (p);
}
