/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:04:14 by cowen             #+#    #+#             */
/*   Updated: 2022/01/20 15:35:15 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <float.h>
# include <mlx.h>
# include <stdio.h>
# include "list.h"
# include "vec3.h"
# include "color.h"
# include "camera.h"
# include "matrix.h"
# include "light.h"
# include "sphere.h"
# include "ray.h"
# include "plane.h"
# include "cylinder.h"
# include "cone.h"
# include "parse.h"
# include "get_next_line.h"
# include "../libft/libft.h"

# define WINDOW_HEIGHT 700
# define WINDOW_WIDTH 800

/* mlx */
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		*image;
}				t_mlx;

/* scene */
typedef enum e_object_type
{
	NONE = 0,
	SPHERE,
	PLANE,
	LIGHT,
	CYLINDER,
	CONE
}				t_otype;

typedef enum e_material
{
	GLOSSY = 1,
	MATTE,
	GLASS,
	MIRROR,
	CHECKERB
}				t_material;

typedef struct s_object
{
	t_otype		type;
	void		*ptr;
	t_color_r	color;
	int			checkerb;
	float		albedo[6];
}				t_object;
/* 
	albedo:
	0 for diffused light
	1 for specular light
	2 for reflect color
	3 for refract color
	4 for specular exponent
	5 for refractive index
*/

typedef struct s_hit
{
	t_object	*hit_obj;
	t_ray		hit_ray;
	t_vec3		hit;
	t_vec3		hit_normal;
	int			reflect_color;
	int			refract_color;
}				t_hit;

typedef struct s_base
{
	t_vec3	x_axis;
	t_vec3	y_axis;
	t_vec3	z_axis;
}	t_base;

/* init */
int				ft_init_mlx(t_mlx *mlx);
int				ft_init_image(t_image *img, t_mlx *mlx);

/* hooks */
int				esc_key(int key, t_mlx *mlx);
int				crossclose(t_mlx *mlx, int key);

/* intersect */
int				sphere_intersect(t_ray ray, t_sphere sphere, double *t);
int				plane_intersect(t_ray ray, t_plane plane, double *t);
int				cylinder_intersect(t_ray ray, t_cylinder cylinder, double *t);
int				cone_intersect(t_ray ray, t_cone cone, double *t);
int				intersect_object(t_ray *ray, t_object *object, double *t);
t_color_r		checkerboard2(t_hit *hit_info);
t_vec3			get_object_normal(t_vec3 hit, t_object *object, t_hit *info);
int				scene_intersect(t_list *objects, t_hit *info);
int				is_in_shadow(t_list *objects, t_light *light, t_hit *info);
void			get_pixel_color(t_scene *scene, t_hit *hit_info,
					t_color_r *material, int lights_num);
void			iterate_all_lights(t_scene *scene, t_hit *hit_info,
					float ds_light[2], t_color_r ds_color[2]);

/* parsing */
t_val_error		ft_stof(char *str);
t_val_error		ft_tripple_stof(char *str);
t_val_error		e_num_parsing(char *buff, t_scene *scene);
t_val_error		parsing_color(char *str);
void			main_parse(int argc, char **argv, t_scene *scene);
void			parse_error_msg(int num_error, t_scene *scene,
					void *values, char **tokens);

/* utils */
void			new_buff(char *buff);
void			object_add_or_create(t_object *object,
					t_scene *scene, char **tokens);
int				ft_isspace(int c);
void			tripple_stof_filling_values(t_val_error *tmp,
					t_val_error *tmp2, int i);
void			ft_stof_part_two(char *str, float *a,
					float *b, t_val_error *temp);
unsigned long	ft_strlen(const char *s);
void			init_base(t_base *base, t_vec3 orientation);

/* free funcs */
void			free_structs(t_scene *scene, char *buff);
void			free_tokens(char **tokens);

/* check errors */
int				check_arguments(int argc, char **argv);
int				check_string(char *str);
void			count_tokens(int i, t_val_error temp,
					t_scene *scene, char **tokens);
void			parsing_elements(char *buff, t_scene *scene, t_static *value);

/* write errors */
void			main_errors(int n_error);
void			elements_errors(t_scene *scene, void *value);
void			common_errors(int err, t_scene *scene, void *value);
void			malloc_error(t_scene *scene,
					void *value, char **tokens);
void			stof_errors(int err, t_scene *scene,
					void *value, char **tokens);
void			too_much_tokens(int err, t_scene *scene,
					void *value, char **tokens);
void			err_objects(int err, t_scene *scene,
					void *value, char **tokens);
void			err_objects_two(int err, t_scene *scene,
					void *value, char **tokens);
void			err_objects_three(int err, t_scene *scene,
					void *value, char **tokens);

/* elements filling */
void			camera_filling(char *buff, t_scene *scene, t_val_error temp);
void			ambient_filling(char *buff, t_scene *scene, t_val_error temp);
void			light_filling(char *buff, t_scene *scene, t_val_error temp);
void			sphere_filling(char *buff, t_scene *scene, t_val_error temp);
void			cone_filling(char *buff, t_scene *scene, t_val_error temp);
void			cylinder_filling(char *buff, t_scene *scene, t_val_error temp);
void			plane_filling(char	*buff, t_scene *scene, t_val_error temp);

/* values filling */
void			pos_cam_filling(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
void			ori_cam_filling(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
void			pov_cam_filling(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
void			amb_ratio_filling(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
void			amb_color_filling(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
t_vec3			obj_coord_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
t_color_r		obj_color_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
float			obj_inten_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
float			obj_single_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
t_material		obj_albedo_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
t_vec3			obj_orient_fill(t_val_error tmp, t_scene *scene,
					char **tok, int pos);
t_object		*object_create(void *obj, t_otype type, t_color_r color,
					t_material material);

#endif