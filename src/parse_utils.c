/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:38:03 by cowen             #+#    #+#             */
/*   Updated: 2022/01/19 16:04:49 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_buff(char *buff)
{
	int	i;
	int	t;

	t = 0;
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		if (!ft_isspace(buff[i]))
		{
			buff[t] = ' ';
			t++;
			while (!ft_isspace(buff[i]))
				i++;
		}
		else
		{
			buff[t] = buff[i];
			i++;
			t++;
		}
	}
	buff[t] = '\0';
}

int	check_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(9 <= str[i] && str[i] <= 13) && !(str[i] == ' ')
			&& !(str[i] == '.') && !(str[i] == ',') && !(str[i] == '-')
			&& !('0' <= str[i]
				&& str[i] <= '9'))
			return (INC_SYMBOLS);
		i++;
	}
	return (OK);
}

int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (OK);
	return (ERROR);
}

unsigned long	ft_strlen(const char *s)
{
	const char	*str;

	if (!s)
		return (0);
	str = s;
	--str;
	while (*(++str))
		;
	return (str - s);
}

void	ft_objects_free(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		if (((t_object *)((*lst)->content))->ptr)
			free(((t_object *)((*lst)->content))->ptr);
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}
