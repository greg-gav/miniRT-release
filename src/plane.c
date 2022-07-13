/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 00:13:02 by bteak             #+#    #+#             */
/*   Updated: 2022/01/16 16:37:18 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	*plane_create(t_vec3 origin, t_vec3 orientation)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->origin = origin;
	plane->orientation = orientation;
	return (plane);
}

t_vec3	get_plane_normal(t_vec3 point, t_plane plane)
{
	(void) point;
	return (plane.orientation);
}

int	plane_intersect(t_ray ray, t_plane plane, double *t)
{
	double	d;
	t_vec3	p;

	d = vec3_dot_product(plane.orientation, ray.direction);
	if (fabs(d) > 1e-6)
	{
		p = vec3_substract(plane.origin, ray.origin);
		*t = vec3_dot_product(p, plane.orientation) / d;
		return (*t >= 1e-6);
	}
	return (0);
}

void	plane_filling(char	*buff, t_scene *scene, t_val_error temp)
{
	t_plane		*plane;
	t_object	*object;
	t_material	albedo;
	char		**tokens;
	t_temp_obj	tp;

	tokens = ft_split(buff, ' ');
	count_tokens(5, temp, scene, tokens);
	tp.center = obj_coord_fill(temp, scene, tokens, 1);
	tp.orientation = obj_orient_fill(temp, scene, tokens, 2);
	tp.color = obj_color_fill(temp, scene, tokens, 3);
	albedo = obj_albedo_fill(temp, scene, tokens, 4);
	plane = plane_create(tp.center, tp.orientation);
	object = object_create(plane, PLANE, tp.color, albedo);
	object_add_or_create(object, scene, tokens);
	free_tokens(tokens);
}

void	object_add_or_create(t_object *object, t_scene *scene, char **tokens)
{
	t_list	**objects;

	objects = 0;
	if (scene->objects == NULL)
	{
		objects = malloc(sizeof(t_list *));
		parse_error_msg(CHECK_MALLOC, scene, objects, tokens);
		*objects = NULL;
		scene->objects = objects;
		ft_lstadd_back(objects, ft_lstnew(object));
	}
	else
	{
		ft_lstadd_back(scene->objects, ft_lstnew(object));
	}
}
