/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:59:15 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 22:27:25 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cone	*cone_create(t_vec3 origin, t_vec3 orientation, float r, float h)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->origin = origin;
	cone->orientation = orientation;
	cone->radius = r;
	cone->height = h;
	return (cone);
}

t_vec3	get_cone_normal(t_vec3 point, t_cone cone)
{
	t_vec3	tmp;
	t_vec3	n;
	float	sc;

	tmp = vec3_substract(point, cone.origin);
	sc = vec3_dot_product(cone.orientation, tmp);
	if (sc != 0)
		n = vec3_substract(tmp, vec3_multiply(cone.orientation,
					vec3_len2(tmp) / sc));
	else
		n = vec3_create(0, 0, 0);
	vec3_normalize(&n);
	return (n);
}

static void	solve_eq(double sc[4], double s, double sol[2])
{
	double	d[3];
	double	det;
	double	det_sq;

	d[0] = sc[0] * sc[0] + sc[2] * sc[2] - s * sc[4] * sc[4];
	d[1] = 2 * (sc[0] * sc[1] + sc[2] * sc[3] - s * sc[4] * sc[5]);
	d[2] = sc[1] * sc[1] + sc[3] * sc[3] - s * sc[5] * sc[5];
	det = d[1] * d[1] - 4 * d[0] * d[2];
	sol[0] = -1;
	sol[1] = -1;
	if (det >= 0)
	{
		det_sq = sqrt(det);
		sol[1] = (-d[1] + det_sq) / (2 * d[0]);
		sol[0] = (-d[1] - det_sq) / (2 * d[0]);
	}
}

int	cone_intersect(t_ray ray, t_cone cone, double *t)
{
	t_base	base;
	t_vec3	origin;
	double	sc[6];
	double	ts[2];
	double	z[2];

	init_base(&base, cone.orientation);
	origin = vec3_substract(ray.origin, cone.origin);
	sc[0] = vec3_dot_product(ray.direction, base.x_axis);
	sc[1] = vec3_dot_product(origin, base.x_axis);
	sc[2] = vec3_dot_product(ray.direction, base.y_axis);
	sc[3] = vec3_dot_product(origin, base.y_axis);
	sc[4] = vec3_dot_product(ray.direction, base.z_axis);
	sc[5] = vec3_dot_product(origin, base.z_axis);
	solve_eq(sc, (cone.radius * cone.radius) / (cone.height * cone.height), ts);
	if (ts[1] > 0)
	{
		z[0] = ts[0] * sc[4] + sc[5];
		z[1] = ts[1] * sc[4] + sc[5];
		if (ts[0] > 0 && z[0] > 0 && z[0] <= cone.height)
			return (*t = ts[0]);
		else if (z[1] > 0 && z[1] <= cone.height)
			return (*t = ts[1]);
	}
	return (0);
}

void	cone_filling(char *buff, t_scene *scene, t_val_error temp)
{
	char		**tokens;
	t_object	*object;
	t_cone		*cone;
	t_material	albedo;
	t_temp_obj	tc;

	tc = (t_temp_obj){};
	tokens = ft_split(buff, ' ');
	count_tokens(7, temp, scene, tokens);
	tc.center = obj_coord_fill(temp, scene, tokens, 1);
	tc.orientation = obj_orient_fill(temp, scene, tokens, 2);
	vec3_normalize(&tc.orientation);
	tc.radius = obj_single_fill(temp, scene, tokens, 3) / 2;
	tc.height = obj_single_fill(temp, scene, tokens, 4);
	tc.color = obj_color_fill(temp, scene, tokens, 5);
	albedo = obj_albedo_fill(temp, scene, tokens, 6);
	cone = cone_create(tc.center, tc.orientation, tc.radius, tc.height);
	object = object_create(cone, CONE, tc.color, albedo);
	object_add_or_create(object, scene, tokens);
	free_tokens(tokens);
}
