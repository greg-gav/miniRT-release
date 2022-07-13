/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:31:22 by bteak             #+#    #+#             */
/*   Updated: 2021/12/28 13:09:26 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_keep_str(int fd, char *keep_str)
{
	int		rd;
	char	*buff;

	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rd = 1;
	while (rd != 0 && !ft_strchr_gnl(keep_str, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd] = '\0';
		keep_str = ft_strjoin_gnl(keep_str, buff);
	}
	free(buff);
	return (keep_str);
}

char	*ft_get_line(char *keep_str)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!keep_str[i])
		return (NULL);
	while (keep_str[i] && keep_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (keep_str[i] && keep_str[i] != '\n')
	{
		str[i] = keep_str[i];
		i++;
	}
	if (keep_str[i] == '\n')
	{
		str[i] = keep_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_update_keep_str(char *keep_str)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (keep_str[i] && keep_str[i] != '\n')
		i++;
	if (!keep_str[i])
	{
		free (keep_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(keep_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (keep_str[i])
		str[j++] = keep_str[i++];
	str[j] = '\0';
	free(keep_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*keep_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep_str = ft_keep_str(fd, keep_str);
	if (!keep_str)
		return (NULL);
	line = ft_get_line(keep_str);
	keep_str = ft_update_keep_str(keep_str);
	return (line);
}
