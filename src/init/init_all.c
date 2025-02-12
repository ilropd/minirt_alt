/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:27:04 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/12 17:05:58 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	figures(t_scene *scene)
{
	if (ft_strcmp(scene->table[0], "sp") == 0)
		return (init_sphere(scene));
	else if (ft_strcmp(scene->table[0], "pl") == 0)
		return (init_plane(scene));
	else if (ft_strcmp(scene->table[0], "cy") == 0)
		return (init_cylinder(scene));
	return (1);
}

static int	unique(t_scene *scene)
{
	if (ft_strcmp(scene->table[0], "A") == 0)
		return (init_ambient(scene));
	else if (ft_strcmp(scene->table[0], "L") == 0)
		return (init_light(scene));
	else if (ft_strcmp(scene->table[0], "C") == 0)
		return (init_camera(scene));
	return (1);
}

int	init_all(t_scene *scene)
{
	int	i;

	i = 0;
	if (!scene->table)
		return (printf("%s%s", ERROR, TBL_ERR), 1);
	if (ft_strlen(scene->table[0]) == 1)
		i = unique(scene);
	else if (ft_strlen(scene->table[0]) == 2)
		i = figures(scene);
	else
		return (printf("%s%s", ERROR, ARGS_SC), 1);
	return (i);
}
