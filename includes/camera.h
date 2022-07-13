/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:37:49 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 22:33:35 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		orientation;
	int			fov;
}				t_camera;

typedef struct s_ambient
{
	float		intensity;
	t_color		color;
}				t_ambient;

t_camera		*camera_create(t_vec3 pos, t_vec3 rot, int fov);
t_ambient		*ambient_create(t_vec3 pos, t_vec3 rot, int fov);

#endif