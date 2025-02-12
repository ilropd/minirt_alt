/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:18:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/11 19:51:21 by irozhkov         ###   ########.fr       */
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
			ray->hit = 1;
			get_pl_normal(ray, plane, dist);
			color = light_calc(scene, ray, plane->color);
			check_ray(ray, color, dist, PL);
		}
	}
}

double	plane_sh_intersection(t_item *item, t_ray *ray)
{
	t_plane 	*plane;
	t_vector	*temp;
	double		dist;
	double		denom;

	plane = item->type.pl;
	denom = vector_dot_prod(&ray->v_ray, &plane->orient);
	if (fabs(denom) < 1e-6)
		return (MAXFLOAT);
	temp = vector_sub(&ray->ray_orgn, &plane->center);
	dist = (vector_dot_prod(&plane->center, &plane->orient)
			- vector_dot_prod(temp, &plane->orient)) / denom;
	free(temp);
	if (dist < 0)
		return (MAXFLOAT);
	return (dist);
}

/*int	plane_sh_intersection(t_item *item, t_ray *ray)
{
	t_plane		*plane;
	t_vector	*temp;
	double		dist;
	double		denom;

	plane =  item->type.pl;
	denom = vector_dot_prod(&ray->v_ray, &plane->orient);
	if (fabs(denom) > 1e-6)
    {
		temp = vector_sub(&ray->ray_orgn, &plane->center);
        dist = (vector_dot_prod(&plane->center, &plane->orient)
                - vector_dot_prod(temp, &plane->orient)) / denom;
		free(temp);
		if (dist < 1e-3)
			return (0);
		return (1);
    }
	return (0);
}*/
