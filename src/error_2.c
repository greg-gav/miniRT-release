/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:30:28 by cowen             #+#    #+#             */
/*   Updated: 2022/01/19 15:39:54 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	too_much_tokens(int err, t_scene *scene, void *value, char **tokens)
{
	char	*buff;

	buff = (char *) value;
	write(2, "Error\n", 6);
	write(2, "Incorrect amount of arguments in string:\n", 41);
	ft_putstr_fd(buff, 2);
	write(2, "\n", 1);
	free_structs(scene, buff);
	free_tokens(tokens);
	exit (err);
}

void	stof_errors(int err, t_scene *scene, void *value, char **tokens)
{
	t_val_error	*values;

	values = (t_val_error *) value;
	write(2, "Error\n", 6);
	if (err == DOT_VALUE)
	{
		write(2, "Incorrect float value in string:\n", 33);
		ft_putstr_fd(values->buff, 2);
	}
	if (err == TRP_VALUE)
	{
		write(2, "Incorrect amount of aguments X-Y-Z coordinate string:\n", 54);
		ft_putstr_fd(values->buff, 2);
	}
	if (err == ONE_VALUE)
	{
		ft_putstr_fd("3d normalized orientation vector should be", 2);
		ft_putstr_fd(" in range [-1,1] for each x,y,z axis\n", 2);
		ft_putstr_fd(values->buff, 2);
	}
	write(2, "\n", 1);
	free_structs(scene, values->buff);
	free_tokens(tokens);
	exit(err);
}

void	malloc_error(t_scene *scene, void *value, char **tokens)
{
	if (value == NULL)
	{
		free_structs(scene, NULL);
		free_tokens(tokens);
		write(2, "Error\n", 6);
		write(2, "Malloc has not been created\n", 28);
		exit (MALLOC_FAIL);
	}
}

void	err_objects_three(int err, t_scene *scene, void *value, char **tokens)
{
	t_val_error	*temp;

	temp = (t_val_error *) value;
	write(2, "Error\n", 6);
	if (err == ALB_ERROR)
	{
		write(2, "Material value (optional) should be in range 1-5 ", 48);
		write(2, "String with error:\n", 19);
		ft_putstr_fd(temp->buff, 2);
	}
	free_structs(scene, NULL);
	free_tokens(tokens);
	exit (err);
}
