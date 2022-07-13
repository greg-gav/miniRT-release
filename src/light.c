/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 19:21:28 by bteak             #+#    #+#             */
/*   Updated: 2022/01/16 18:56:12 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light	*light_create(t_vec3 pos, float intensity, t_color_r color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = pos;
	light->intensity = intensity;
	light->color = color;
	return (light);
}

void	light_add_or_create(t_light *light, t_scene *scene, char **tokens)
{
	t_list	**lights;

	lights = 0;
	if (scene->lights == NULL)
	{
		lights = malloc(sizeof(t_list *));
		parse_error_msg(CHECK_MALLOC, scene, lights, tokens);
		*lights = NULL;
		scene->lights = lights;
		ft_lstadd_back(lights, ft_lstnew(light));
	}
	else
		ft_lstadd_back(scene->lights, ft_lstnew(light));
}

void	light_filling(char *buff, t_scene *scene, t_val_error temp)
{
	t_vec3		position;
	t_color_r	color;
	float		intensity;
	t_light		*light;
	char		**tokens;

	tokens = ft_split(buff, ' ');
	count_tokens(4, temp, scene, tokens);
	position = obj_coord_fill(temp, scene, tokens, 1);
	intensity = obj_inten_fill(temp, scene, tokens, 2);
	color = obj_color_fill(temp, scene, tokens, 3);
	light = light_create(position, intensity, color);
	light_add_or_create(light, scene, tokens);
	free_tokens(tokens);
}
