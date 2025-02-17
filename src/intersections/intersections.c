/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:12:55 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 19:39:06 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

static void	is_cam_inside(t_scene *scene)
{
	t_item	*current_item;

	current_item = scene->objs;
	while (current_item && (scene->cam.is_inside != 1))
	{
		if (!current_item->inside)
        {
            current_item = current_item->next;
            continue	;
        }
		current_item->inside(scene, current_item);
		current_item = current_item->next;
	}
}

void	get_intersections(t_scene *scene, t_ray *ray)
{
	t_item	*current_item;

	current_item = scene->objs;
	ray->hit = 0;
	ray->dot_color = DEFAULT_COLOR;
	ray->dist_curr = MAXFLOAT;
	is_cam_inside(scene);
	while (current_item)
	{
		current_item->intersect(scene, current_item, ray);
		current_item = current_item->next;
	}
}

void	check_ray(t_ray *ray, int color, double dist, t_type_id id)
{
	if (ray->hit == 0)
	{
		ray->hit = 1;
		ray->dot_color = color;
		ray->dist_curr = dist;
	}
	else
	{
		if (dist < ray->dist_curr)
		{
			ray->dot_color = color;
			ray->dist_curr = dist;
		}
		else if (dist == ray->dist_curr)
		{
			if (id != ray->id)
			{
				ray->dot_color = average_colors(color, ray->dot_color);
				ray->id = id;
			}
			else
				ray->dot_color = color;
		}
	}
}
