/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:18:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/01 16:31:37 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane_intersection.h"

static void	get_pl_normal(t_ray *ray, t_plane *pl, double dist)
{
	vector_set(&ray->hit_p, (ray->ray_orgn.x + ray->v_ray.x * dist),
		(ray->ray_orgn.y + ray->v_ray.y * dist),
		(ray->ray_orgn.z + ray->v_ray.z * dist));
	ray->normal = pl->orient;
	vector_normalize(&ray->normal);
}

void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	int		color;
	float	denom;
	double	dist;
	t_plane	*plane;

	plane = item->type.pl;
	denom = vector_dot_prod(&ray->v_ray, &plane->orient);
	if (fabs(denom) >= 1e-6)
	{
		dist = (vector_dot_prod(&plane->center, &plane->orient)
				- vector_dot_prod(&plane->cam_plane, &plane->orient)) / denom;
		if (dist > 0)
		{
			get_pl_normal(ray, plane, dist);
			color = light_calc(scene, ray, plane->color);
			check_ray(ray, color, dist, PL);
		}
	}
}
