/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:04:58 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 22:29:22 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder	*cylinder_create(t_vec3 origin, t_vec3 orientation,
							float r, float h)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->origin = origin;
	cylinder->orientation = orientation;
	cylinder->radius = r;
	cylinder->height = h;
	return (cylinder);
}

t_vec3	get_cylinder_normal(t_vec3 point, t_cylinder c)
{
	t_vec3	tmp;
	t_vec3	n;

	tmp = vec3_multiply(c.orientation,
			vec3_dot_product(vec3_substract(point, c.origin), c.orientation));
	n = vec3_substract(point, vec3_add(tmp, c.origin));
	vec3_normalize(&n);
	return (n);
}

static void	solve_eq(double sc[4], double r, double sol[2])
{
	double	d[3];
	double	det;
	double	det_sq;

	d[0] = sc[0] * sc[0] + sc[2] * sc[2];
	d[1] = 2 * (sc[0] * sc[1] + sc[2] * sc[3]);
	d[2] = sc[1] * sc[1] + sc[3] * sc[3] - r * r;
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

int	cylinder_intersect(t_ray ray, t_cylinder cylinder, double *t)
{
	t_base	base;
	t_vec3	origin;
	double	sc[6];
	double	ts[2];

	init_base(&base, cylinder.orientation);
	origin = vec3_substract(ray.origin, cylinder.origin);
	sc[0] = vec3_dot_product(ray.direction, base.x_axis);
	sc[1] = vec3_dot_product(origin, base.x_axis);
	sc[2] = vec3_dot_product(ray.direction, base.y_axis);
	sc[3] = vec3_dot_product(origin, base.y_axis);
	solve_eq(sc, cylinder.radius, ts);
	if (ts[1] > 0)
	{
		sc[4] = vec3_dot_product(ray.direction, base.z_axis);
		sc[5] = vec3_dot_product(origin, base.z_axis);
		if (ts[0] > 0 && fabs(ts[0] * sc[4] + sc[5]) <= cylinder.height / 2)
			return (*t = ts[0]);
		else if (fabs(ts[1] * sc[4] + sc[5]) <= cylinder.height / 2)
			return (*t = ts[1]);
	}
	return (0);
}

void	cylinder_filling(char *buff, t_scene *scene, t_val_error temp)
{
	t_cylinder	*cylinder;
	t_object	*object;
	t_material	albedo;
	char		**tokens;
	t_temp_obj	tc;

	tokens = ft_split(buff, ' ');
	count_tokens(7, temp, scene, tokens);
	tc.center = obj_coord_fill(temp, scene, tokens, 1);
	tc.orientation = obj_orient_fill(temp, scene, tokens, 2);
	vec3_normalize(&tc.orientation);
	tc.radius = obj_single_fill(temp, scene, tokens, 3) / 2;
	tc.height = obj_single_fill(temp, scene, tokens, 4);
	tc.color = obj_color_fill(temp, scene, tokens, 5);
	albedo = obj_albedo_fill(temp, scene, tokens, 6);
	cylinder = cylinder_create(tc.center, tc.orientation, tc.radius, tc.height);
	object = object_create(cylinder, CYLINDER, tc.color, albedo);
	object_add_or_create(object, scene, tokens);
	free_tokens(tokens);
}
