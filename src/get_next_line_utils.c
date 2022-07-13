/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:31:33 by bteak             #+#    #+#             */
/*   Updated: 2021/12/28 13:03:20 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *keep_str, char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!keep_str)
	{
		keep_str = (char *)malloc(sizeof(char));
		keep_str[0] = '\0';
	}
	if (!keep_str || !buff)
		return (NULL);
	str = malloc (sizeof(char) * (ft_strlen(keep_str) + ft_strlen(buff) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (keep_str[++i] != '\0')
		str[i] = keep_str[i];
	j = 0;
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	free(keep_str);
	return (str);
}
