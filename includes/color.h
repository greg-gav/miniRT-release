/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:36:25 by bteak             #+#    #+#             */
/*   Updated: 2022/01/20 15:25:30 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define COLOR_L_BLUE 11393254
# define COLOR_GREEN 25600
# define COLOR_WOOD 4731426
# define COLOR_WHITE 16777215
# define COLOR_GLASS 10073036
# define COLOR_D_BLUE 330288
# define COLOR_BACKGROUND 0

typedef struct s_color
{
	unsigned char	t;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct s_color_r
{
	float	r;
	float	g;
	float	b;
	float	a;
}				t_color_r;

t_color			int_to_color(int c);
int				color_to_int(t_color color);
t_color_r		from_color_to_r(t_color c);
t_color_r		from_int_to_r(int c);
int				color_r_to_int(t_color_r c);
t_color_r		color_r_multiply(t_color_r a, t_color_r b);
t_color_r		color_r_multiply_val(t_color_r c, float value);
t_color_r		color_r_add(t_color_r a, t_color_r b);
t_color_r		color_r_substract(t_color_r a, t_color_r b);
t_color_r		color_r_mix(t_color_r a, t_color_r b, float t);
t_color_r		color_r_light(t_color_r a, t_color_r b);

#endif