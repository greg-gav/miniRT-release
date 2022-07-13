/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:05:22 by bteak             #+#    #+#             */
/*   Updated: 2022/01/18 14:25:28 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct s_matrix
{
	float	d[4][4];
}				t_matrix;

t_vec3			multiply_by_matrix(t_vec3 p, t_matrix m);
t_matrix		look_at(t_vec3 origin, t_vec3 cam_direction);

#endif