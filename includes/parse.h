/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:40:21 by cowen             #+#    #+#             */
/*   Updated: 2022/01/18 14:22:50 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define AMBIENT_C 10
# define CAMERA_C 20
# define LIGHT_C 30
# define SPHERE_C 40
# define PLANE_C 50
# define CYLINDER_C 60
# define CONUS_C 70

/* Main parse errors */
# define ERR_ARGC 1
# define ERR_EXT 2
# define ERR_FD 3
# define OK 0
# define ERROR -1
# define CHECK_MALLOC 99
# define MALLOC_FAIL 9

/* Camera, Ambient and Light */
# define ELEM_PARS 4
# define AMB_ERROR 5
# define CAM_ERROR 6
# define LIG_ERROR 7
# define RAT_ERROR 15

/* Common parse */
# define INC_SYMBOLS 8
# define ELEM_ERROR_C 11
# define MUCH_ELEMS 16

/* Stof error */
# define DOT_VALUE 12
# define TRP_VALUE 13
# define ONE_VALUE 14
# define COO_ERROR 19

/* Color error */
# define COL_ERROR 17
# define TRP_VALUE_COL 22

/* POV error */
# define POV_ERROR 18

/* Albedro error */
# define ALB_ERROR 21

typedef struct s_static
{
	int		camera;
	int		ambient;
	int		l_cap;
	int		i;
	char	*buff;
}	t_static;

typedef struct s_val_error
{
	int			check_value;
	float		f_value;
	int			i_value;
	int			err_value;
	int			flag;
	int			r;
	int			g;
	int			b;
	int			colour;
	float		x_f;
	float		y_f;
	float		z_f;
	char		*buff;
}	t_val_error;

typedef struct s_temp_obj
{
	t_vec3		center;
	t_vec3		orientation;
	float		radius;
	float		height;
	t_color_r	color;

}	t_temp_obj;

#endif