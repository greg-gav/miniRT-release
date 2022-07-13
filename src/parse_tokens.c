/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:49:01 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 16:53:17 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_val_error	ft_stof(char *str)
{
	float		a;
	float		b;
	t_val_error	temp;
	int			minus;

	minus = 1;
	temp = (t_val_error){};
	a = 0;
	b = 0;
	if (str)
	{
		if (*str == '-')
		{
			str++;
			minus = -1;
		}	
		ft_stof_part_two(str, &a, &b, &temp);
		if (temp.flag > 1)
		{
			temp.err_value = DOT_VALUE;
			return (temp);
		}
		temp.f_value = (a + b) * minus;
	}
	return (temp);
}

void	ft_stof_part_two(char *str, float *a, float *b, t_val_error *temp)
{
	float	tempv;
	int		del;

	del = 10;
	tempv = 0;
	while (('0' <= *str && *str <= '9') || *str == '.')
	{
		if (*str == '.')
			temp->flag++;
		if (('0' <= *str && *str <= '9') && temp->flag == 0)
			*a = *a * 10 + (*str - '0');
		if (('0' <= *str && *str <= '9') && temp->flag == 1)
		{
			tempv = (((*str - '0') + tempv) / del);
			*b += tempv;
			del *= 10;
		}
		str++;
	}
	if (*str != ' ' && *str != '\0' && *str != '\n')
		temp->err_value = COO_ERROR;
}

t_val_error	parsing_color(char *str)
{
	t_val_error	tmp;

	tmp = (t_val_error){};
	if (str)
	{
		tmp = ft_tripple_stof(str);
		tmp.r = tmp.x_f;
		tmp.g = tmp.y_f;
		tmp.b = tmp.z_f;
		if (tmp.err_value != OK)
		{
			if (tmp.err_value == TRP_VALUE)
				tmp.err_value = TRP_VALUE_COL;
			return (tmp);
		}
		if (tmp.r < 0 || tmp.r > 255 || tmp.g < 0 || tmp.g > 255 || tmp.b < 0
			|| tmp.b > 255)
			tmp.err_value = COL_ERROR;
		tmp.colour = (tmp.r * 65536) + (tmp.g * 256) + (tmp.b);
	}
	return (tmp);
}

t_val_error	ft_tripple_stof(char *str)
{
	t_val_error	temp;
	t_val_error	temp2;
	int			i;
	char		**sub_tokens;

	temp = (t_val_error){};
	i = 0;
	if (str)
	{
		sub_tokens = ft_split(str, ',');
		while (sub_tokens[i] && !temp.err_value)
		{
			temp2 = ft_stof(sub_tokens[i]);
			tripple_stof_filling_values(&temp, &temp2, i);
			i++;
		}
		if (i != 3)
			temp.err_value = TRP_VALUE;
		free_tokens(sub_tokens);
	}
	return (temp);
}

void	tripple_stof_filling_values(t_val_error *tmp, t_val_error *tmp2, int i)
{
	if (i == 0)
		tmp->x_f = tmp2->f_value;
	if (i == 1)
		tmp->y_f = tmp2->f_value;
	if (i == 2)
		tmp->z_f = tmp2->f_value;
	tmp->err_value = tmp2->err_value;
}
