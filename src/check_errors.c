/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:46:07 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 14:17:23 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		return (ERR_ARGC);
	while (argv[1][i])
	{
		if (argv[1][i] == '.')
		{
			if (argv[1][i + 1] == 'r' && argv[1][i + 2] == 't'
				&& argv[1][i + 3] == '\0')
				return (OK);
		}
		i++;
	}
	return (ERR_EXT);
}

void	parse_error_msg(int err, t_scene *scene, void *value, char **tokens)
{
	if (err == ERR_ARGC || err == ERR_EXT || err == ERR_FD)
		main_errors(err);
	if (err == ELEM_PARS)
		elements_errors(scene, value);
	if (err == INC_SYMBOLS || err == ELEM_ERROR_C)
		common_errors(err, scene, value);
	if (err == CHECK_MALLOC)
		malloc_error(scene, value, tokens);
	if (err == DOT_VALUE || err == TRP_VALUE || err == ONE_VALUE)
		stof_errors(err, scene, value, tokens);
	if (err == MUCH_ELEMS)
		too_much_tokens(err, scene, value, tokens);
	if (err == COL_ERROR || err == POV_ERROR)
		err_objects(err, scene, value, tokens);
	if (err == RAT_ERROR || err == COO_ERROR || err == TRP_VALUE_COL)
		err_objects_two(err, scene, value, tokens);
	if (err == ALB_ERROR)
		err_objects_three(err, scene, value, tokens);
}

void	count_tokens(int i, t_val_error temp, t_scene *scene, char **tokens)
{
	int		y;
	char	*buff;

	y = 0;
	buff = temp.buff;
	while (tokens[y])
		y++;
	if (y != i && (!ft_strncmp(buff, "A", 1) || !ft_strncmp(buff, "C", 1)
			|| !ft_strncmp(buff, "L", 1) || !ft_strncmp(buff, "l", 1)))
		parse_error_msg(MUCH_ELEMS, scene, buff, tokens);
	else if (((!ft_strncmp(buff, "sp", 2) || !ft_strncmp(buff, "pl", 2)
				|| !ft_strncmp(buff, "cy", 2) || !ft_strncmp(buff, "co", 2)))
		&& (y != i && y + 1 != i))
		parse_error_msg(MUCH_ELEMS, scene, buff, tokens);
}
