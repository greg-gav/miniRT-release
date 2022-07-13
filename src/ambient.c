/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:26:45 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 12:50:27 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ambient_filling(char *buff, t_scene *scene, t_val_error temp)
{
	t_ambient	*ambient;
	char		**tokens;

	ambient = malloc(sizeof(t_ambient));
	parse_error_msg(CHECK_MALLOC, scene, ambient, NULL);
	scene->ambient = ambient;
	tokens = ft_split(buff, ' ');
	count_tokens(3, temp, scene, tokens);
	amb_ratio_filling(temp, scene, tokens, 1);
	amb_color_filling(temp, scene, tokens, 2);
	free_tokens(tokens);
}

void	amb_ratio_filling(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	if (tok[pos])
	{
		buff = tmp.buff;
		tmp = ft_stof(tok[pos]);
		tmp.buff = buff;
		if (tmp.f_value < 0 || tmp.f_value > 1)
			tmp.err_value = RAT_ERROR;
		parse_error_msg(tmp.err_value, scene, &tmp, tok);
		scene->ambient->intensity = tmp.f_value;
	}
}

void	amb_color_filling(t_val_error tmp, t_scene *scene, char **tok, int pos)
{
	char	*buff;

	if (tok[pos])
	{
		buff = tmp.buff;
		tmp = parsing_color(tok[pos]);
		tmp.buff = buff;
		parse_error_msg(tmp.err_value, scene, &tmp, tok);
		scene->ambient->color = int_to_color(tmp.colour);
	}
}
