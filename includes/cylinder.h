/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:54:28 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:59:04 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct s_cylinder
{
	t_vec3	origin;
	t_vec3	orientation;
	float	radius;
	float	height;
}				t_cylinder;

t_cylinder		*cylinder_create(t_vec3 origin, t_vec3 orientation,
					float r, float h);
t_vec3			get_cylinder_normal(t_vec3 point, t_cylinder cylinder);

#endif