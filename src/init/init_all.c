/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:27:04 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/23 15:14:53 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	init_all(t_scene *scene)
{
	int	i;

	i = 0;
	if (!scene->table)
		return (printf("%s%s", ERROR, TBL_ERR), 1);
	if (ft_strcmp(scene->table[0], "A") == 0 && ft_strlen(scene->table[0]) == 1)
		i = init_ambient(scene);
	else if (ft_strcmp(scene->table[0], "L") == 0 && ft_strlen(scene->table[0]) == 1)
		i = init_light(scene);
	else if (ft_strcmp(scene->table[0], "C") == 0 && ft_strlen(scene->table[0]) == 1)
		i = init_camera(scene);
/*	else if (ft_strcmp(scene->table[0], "sp") == 0 && ft_strlen(scene->table[0]) == 2)
		i = init_sphere(table, scene);
	else if (ft_strcmp(scene->table[0], "pl") == 0 && ft_strlen(scene->table[0]) == 2)
		i = init_plane(table, scene);
	else if (ft_strcmp(scene->table[0], "cy") == 0 && ft_strlen(scene->table[0]) == 2)
		i = init_cylinder(table, scene);*/
	else
		return (printf("%s%s", ERROR, ARGS_SC), 1);
	return (i);	
}
