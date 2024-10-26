/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/24 15:47:53 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_all(t_scene *scene)
{
	/* add free for mxl with if condition */
	t_item	*temp;

	if (scene->table)
		free_parsing_table(scene->table);
	while (scene->objs)
	{
		temp = scene->objs;
		temp->free_obj(&temp->type);
		scene->objs = temp->next;
		free(temp);
	}
}

void	free_sphere(t_obj *obj)
{
	if (obj->sp)
		free(obj->sp);
}

void	free_plane(t_obj *obj)
{
	if (obj->pl)
		free(obj->pl);
}

void	free_cylinder(t_obj *obj)
{
	if (obj->cy)
		free(obj->cy);
}
