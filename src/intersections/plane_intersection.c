/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:18:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/03/03 20:02:50 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

static void	get_pl_normal(t_ray *ray, t_plane *pl, double dist)
{
	vector_set(&ray->hit_p, (ray->ray_orgn.x + ray->v_ray.x * dist),
		(ray->ray_orgn.y + ray->v_ray.y * dist),
		(ray->ray_orgn.z + ray->v_ray.z * dist));
	ray->normal = pl->orient;
	vector_normalize(&ray->normal);
}

static int	get_checker_color(t_plane *pl, t_vector hit_p)
{
	t_vector	diff;
	t_vector	u;
	t_vector	v;
	t_vector	arbitrary;
	double		local_u;
	double		local_v;
	double		tile_size;
	int			tile_u;
	int			tile_v;

	diff = vector_sub_dir(&hit_p, &pl->center);

	if (fabs(pl->orient.y) < 0.999)
		arbitrary = (t_vector){0, 1, 0};
	else
		arbitrary = (t_vector){1, 0, 0};

	vector_cross(&pl->orient, &arbitrary, &u);
	vector_normalize(&u);
	vector_cross(&pl->orient, &u, &v);
	vector_normalize(&v);

	local_u = vector_dot_prod(&diff, &u);
	local_v = vector_dot_prod(&diff, &v);

	tile_size = 60.0;
	tile_u = (int)floor(local_u / tile_size);
	tile_v = (int)floor(local_v / tile_size);

	if (((tile_u + tile_v) % 2) == 0)
		return ((pl->color[0] << 16) | (pl->color[1] << 8) | (pl->color[2]));
	else
		return (0x000000);
}

void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	int		color;
	double	denom;
	double	dist;
	t_plane	*plane;

	plane = item->type.pl;
	denom = vector_dot_prod(&ray->v_ray, &plane->orient);
	if (fabs(denom) >= 1e-6)
	{
		dist = (vector_dot_prod(&plane->center, &plane->orient)
				- vector_dot_prod(&ray->ray_orgn, &plane->orient)) / denom;
		if (dist > 0)
		{
			ray->hit = 1;
			get_pl_normal(ray, plane, dist);
			int base_color = get_checker_color(plane, ray->hit_p);
			unsigned int checker_color[3];
			checker_color[0] = (base_color >> 16) & 0xFF;  // Rojo
			checker_color[1] = (base_color >> 8) & 0xFF;   // Verde
			checker_color[2] = base_color & 0xFF;          // Azul
			color = light_calc(scene, ray, checker_color);
			check_ray(ray, color, dist, PL);
		}
	}
}

double	plane_sh_intersection(t_item *item, t_ray *ray)
{
	t_plane		*plane;
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

