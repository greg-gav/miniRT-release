/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:33:32 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:57:37 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
}				t_sphere;

t_sphere		*sphere_create(t_vec3 center, float radius);
t_vec3			sphere_get_normal(t_vec3 point, t_sphere sphere);

#endif