/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:54:28 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:59:17 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H

typedef struct s_cone
{
	t_vec3	origin;
	t_vec3	orientation;
	float	radius;
	float	height;
}				t_cone;

t_cone		*cone_create(t_vec3 origin, t_vec3 orientation, float r, float h);
t_vec3		get_cone_normal(t_vec3 point, t_cone cone);

#endif