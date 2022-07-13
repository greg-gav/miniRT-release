/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 15:30:21 by cowen             #+#    #+#             */
/*   Updated: 2022/01/19 15:56:45 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	main_parse(int argc, char **argv, t_scene *scene)
{
	int				fd;
	char			*buff;
	static t_static	values;

	values = (t_static){};
	parse_error_msg(check_arguments(argc, argv), NULL, NULL, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		parse_error_msg(ERR_FD, NULL, NULL, NULL);
	buff = NULL;
	while (values.i++ == 0 || buff)
	{
		buff = get_next_line(fd);
		if (buff && buff[0] != '\n')
			parsing_elements(buff, scene, &values);
		if (buff)
			free(buff);
	}
	close(fd);
	if (values.camera != 1 || values.ambient != 1 || values.l_cap != 1)
		parse_error_msg(ELEM_PARS, scene, &values, NULL);
}

int	check_identificator(const char *buff, t_static *value)
{
	if (!ft_strncmp(buff, "A", 1) && !ft_isspace(buff[1]) && ++(value->ambient))
		return (AMBIENT_C);
	if (!ft_strncmp(buff, "C", 1) && !ft_isspace(buff[1]) && ++(value->camera))
		return (CAMERA_C);
	if (!ft_strncmp(buff, "L", 1) && !ft_isspace(buff[1]) && ++(value->l_cap))
		return (LIGHT_C);
	if (!ft_strncmp(buff, "l", 1) && !ft_isspace(buff[1]))
		return (LIGHT_C);
	if (!ft_strncmp(buff, "sp", 2) && !ft_isspace(buff[2]))
		return (SPHERE_C);
	if (!ft_strncmp(buff, "pl", 2) && !ft_isspace(buff[2]))
		return (PLANE_C);
	if (!ft_strncmp(buff, "cy", 2) && !ft_isspace(buff[2]))
		return (CYLINDER_C);
	if (!ft_strncmp(buff, "co", 2) && !ft_isspace(buff[2]))
		return (CONUS_C);
	return (ELEM_ERROR_C);
}

void	parsing_elements(char *buff, t_scene *scene, t_static *value)
{
	t_val_error	temp;

	temp = (t_val_error){};
	temp.check_value = check_identificator(buff, value);
	new_buff(buff);
	temp.buff = buff;
	value->buff = buff;
	if (check_string(buff + 2))
		parse_error_msg(INC_SYMBOLS, scene, value, NULL);
	if (temp.check_value == ELEM_ERROR_C)
		parse_error_msg(ELEM_ERROR_C, scene, value, NULL);
	if (temp.check_value == AMBIENT_C)
		ambient_filling(buff, scene, temp);
	if (temp.check_value == CAMERA_C)
		camera_filling(buff, scene, temp);
	if (temp.check_value == LIGHT_C)
		light_filling(buff, scene, temp);
	if (temp.check_value == PLANE_C)
		plane_filling(buff, scene, temp);
	if (temp.check_value == SPHERE_C)
		sphere_filling(buff, scene, temp);
	if (temp.check_value == CYLINDER_C)
		cylinder_filling(buff, scene, temp);
	if (temp.check_value == CONUS_C)
		cone_filling(buff, scene, temp);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
			i++;
		i--;
		while (i >= 0 && tokens[i])
		{
			free(tokens[i]);
			i--;
		}
		free(tokens);
	}
}

void	free_structs(t_scene *scene, char *buff)
{
	if (buff)
		free(buff);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->lights)
		ft_lst_free(scene->lights);
	if (scene->objects)
		ft_objects_free(scene->objects);
}
