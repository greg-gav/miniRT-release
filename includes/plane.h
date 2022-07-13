/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:54:28 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:58:00 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	orientation;
}				t_plane;

t_plane			*plane_create(t_vec3 origin, t_vec3 orientation);
t_vec3			get_plane_normal(t_vec3 point, t_plane plane);

#endif