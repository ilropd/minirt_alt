/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/12/07 16:36:47 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_mlx(t_scene *scene)
{
	if (scene->mrt.img.img_ptr)
		mlx_destroy_image(scene->mrt.connection, scene->mrt.img.img_ptr);
	if (scene->mrt.window)
		mlx_destroy_window(scene->mrt.connection, scene->mrt.window);
	if (scene->mrt.connection)
	{
		mlx_destroy_display(scene->mrt.connection);
		free(scene->mrt.connection);
	}
}

void	free_all(t_scene *scene)
{
	t_item	*temp;

	if (scene == NULL)
		return ;
	free_mlx(scene);
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
