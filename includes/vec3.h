/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:04:42 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:57:30 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

t_vec3			vec3_create(float x, float y, float z);
t_vec3			vec3_substract(t_vec3 a, t_vec3 b);
void			vec3_normalize(t_vec3 *v);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
float			vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec3			vec3_multiply(t_vec3 a, double b);
t_vec3			vec3_cross_product(t_vec3 a, t_vec3 b);
float			vec3_len(t_vec3 vector);
float			vec3_len2(t_vec3 v);
double			vec3_dist(t_vec3 vec1, t_vec3 vec2);

#endif