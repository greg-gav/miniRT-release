/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:05:08 by bteak             #+#    #+#             */
/*   Updated: 2022/01/13 18:58:32 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_light
{
	t_vec3		position;
	float		intensity;
	t_color_r	color;
}				t_light;

t_light		*light_create(t_vec3 pos, float intensity, t_color_r color);

#endif