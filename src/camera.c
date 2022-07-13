/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:23:17 by bteak             #+#    #+#             */
/*   Updated: 2022/01/16 15:58:22 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	*camera_create(t_vec3 pos, t_vec3 rot, int fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->position = pos;
	rot.z = -rot.z;
	rot.x = -rot.x;
	rot.y = -rot.y;
	camera->orientation = rot;
	camera->fov = fov;
	return (camera);
}

void	camera_filling(char *buff, t_scene *scene, t_val_error temp)
{
	t_camera	*camera;
	char		**tokens;

	camera = malloc(sizeof(t_camera));
	scene->camera = camera;
	parse_error_msg(CHECK_MALLOC, scene, camera, NULL);
	tokens = ft_split(buff, ' ');
	count_tokens(4, temp, scene, tokens);
	pos_cam_filling(temp, scene, tokens, 1);
	ori_cam_filling(temp, scene, tokens, 2);
	pov_cam_filling(temp, scene, tokens, 3);
	free_tokens(tokens);
}

void	pos_cam_filling(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	buff = tmp.buff;
	tmp = ft_tripple_stof(tok[pos]);
	tmp.buff = buff;
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
	scene->camera->position.x = tmp.x_f;
	scene->camera->position.y = tmp.y_f;
	scene->camera->position.z = tmp.z_f;
}

void	ori_cam_filling(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	buff = tmp.buff;
	tmp = ft_tripple_stof(tok[pos]);
	tmp.buff = buff;
	scene->camera->orientation.x = tmp.x_f;
	scene->camera->orientation.y = tmp.y_f;
	scene->camera->orientation.z = tmp.z_f;
	if (tmp.x_f < -1 || tmp.x_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	if (tmp.y_f < -1 || tmp.y_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	if (tmp.z_f < -1 || tmp.z_f > 1)
		parse_error_msg(ONE_VALUE, scene, &tmp, tok);
	parse_error_msg(tmp.err_value, scene, &tmp, tok);
}

void	pov_cam_filling(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	tmp.i_value = ft_stof(tok[pos]).f_value;
	scene->camera->fov = tmp.i_value;
	if (tmp.i_value > 180 || tmp.i_value < 0)
		parse_error_msg(POV_ERROR, scene, &tmp, tok);
}
