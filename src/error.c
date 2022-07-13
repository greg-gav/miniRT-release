/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:11:05 by cowen             #+#    #+#             */
/*   Updated: 2022/01/16 18:14:04 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	main_errors(int n_error)
{
	write(2, "Error\n", 6);
	if (n_error == ERR_ARGC)
		write(2, "Incorrect amount of arguments\n", 30);
	if (n_error == ERR_EXT)
		write(2, "Incorrect type of file. Should be *.rt\n", 39);
	if (n_error == ERR_FD)
		write(2, "Can't open file descriptor.\n", 28);
	exit(n_error);
}

void	elements_errors(t_scene *scene, void *value)
{
	int			i;
	t_static	*values;

	values = (t_static *) value;
	i = AMB_ERROR;
	write(2, "Error\n", 6);
	if (values->ambient != 1)
		write(2, "Must be one ambient light(A - element)\n", 39);
	if (values->camera != 1)
	{
		i = CAM_ERROR;
		write(2, "Must be one camera (C - element)\n", 33);
	}
	if (values->l_cap > 1)
	{
		i = LIG_ERROR;
		write(2, "Must be only one main light (L - element)\n", 42);
		write(2, "If you want use external lights - use little \"l\" ", 50);
		write(2, "(l - element)\n", 14);
	}
	if (values->l_cap == 0)
		write(2, "Must be one main light (L - element)\n", 37);
	free_structs(scene, NULL);
	exit (i);
}

void	common_errors(int err, t_scene *scene, void *value)
{
	t_static	*values;

	values = (t_static *) value;
	write(2, "Error\n", 6);
	if (err == INC_SYMBOLS)
	{
		write(2, "Incorrect symbols in string #", 28);
		ft_putnbr_fd(values->i, 2);
		write(2, "\n", 1);
	}
	if (err == ELEM_ERROR_C)
	{
		write(2, "Incorrect identificator in string #", 34);
		ft_putnbr_fd(values->i, 2);
		write(2, "\n", 1);
	}
	free_structs(scene, values->buff);
	exit (err);
}

void	err_objects(int err, t_scene *scene, void *value, char **tokens)
{
	t_val_error	*temp;

	temp = (t_val_error *) value;
	write(2, "Error\n", 6);
	if (err == POV_ERROR)
	{
		write(2, "FOV : Horizontal field of view in degrees should be in ", 55);
		write(2, "range [0,180]\n", 14);
		write(2, "String with error:\n", 19);
		ft_putstr_fd(temp->buff, 2);
	}
	if (err == COL_ERROR)
	{
		write(2, "Incorrect arguments. Colour must be in range 0-255\n", 51);
		write(2, "String with error:\n", 19);
		ft_putstr_fd(temp->buff, 2);
	}
	write(2, "\n", 1);
	free_structs(scene, temp->buff);
	free_tokens(tokens);
	exit (err);
}

void	err_objects_two(int err, t_scene *scene, void *value, char **tokens)
{
	t_val_error	*temp;

	temp = (t_val_error *) value;
	write(2, "Error\n", 6);
	if (err == RAT_ERROR)
		write(2, "Ambient lighting ratio should be in range [0.0,1.0]", 52);
	if (err == COO_ERROR)
	{
		write(2, "While parsing single element - incorrect values.", 49);
		write(2, " String with error:\n", 20);
		ft_putstr_fd(temp->buff, 2);
	}
	if (err == TRP_VALUE_COL)
	{
		write(2, "Incorrect amount aguments of R-G-B values string:\n", 50);
		ft_putstr_fd(temp->buff, 2);
	}
	write(2, "\n", 1);
	free_structs(scene, temp->buff);
	free_tokens(tokens);
	exit (err);
}
