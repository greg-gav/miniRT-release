/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_filling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 17:18:47 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 17:23:28 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	obj_inten_fill(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	buff = tmp.buff;
	tmp = ft_stof(tok[pos]);
	tmp.buff = buff;
	if (tmp.f_value < 0 || tmp.f_value > 1)
		tmp.err_value = RAT_ERROR;
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	return (tmp.f_value);
}

float	obj_single_fill(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	buff = tmp.buff;
	tmp = ft_stof(tok[pos]);
	tmp.buff = buff;
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	return (tmp.f_value);
}

t_vec3	obj_coord_fill(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	t_vec3	position;
	char	*buff;

	buff = tmp.buff;
	tmp = ft_tripple_stof(tok[pos]);
	tmp.buff = buff;
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	position = vec3_create(tmp.x_f, tmp.y_f, tmp.z_f);
	return (position);
}
