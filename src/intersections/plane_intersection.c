/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:18:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/03/03 21:31:44 by jpancorb         ###   ########.fr       */
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

static void	set_uv(t_plane *pl, t_vector *u, t_vector *v)
{
	t_vector	arbitrary;

	if (fabs(pl->orient.y) < 0.999)
		arbitrary = (t_vector){0, 1, 0};
	else
		arbitrary = (t_vector){1, 0, 0};
	vector_cross(&pl->orient, &arbitrary, u);
	vector_normalize(u);
	vector_cross(&pl->orient, u, v);
	vector_normalize(v);
}

static int	get_checker_color(t_plane *pl, t_vector hit_p)
{
	t_vector	diff;
	t_vector	u;
	t_vector	v;
	double		local_u;
	double		local_v;

	diff = vector_sub_dir(&hit_p, &pl->center);
	set_uv(pl, &u, &v);
	local_u = vector_dot_prod(&diff, &u);
	local_v = vector_dot_prod(&diff, &v);
	if ((((int)floor(local_u / 20.0)) + ((int)floor(local_v / 20.0))) % 2 == 0)
		return ((pl->color[0] << 16) | (pl->color[1] << 8) | (pl->color[2]));
	else
		return (0x707070);
}

void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	int				color;
	double			denom;
	double			dist;
	t_plane			*plane;
	unsigned int	checker_color[3];

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
			color = get_checker_color(plane, ray->hit_p);
			checker_color[0] = (color >> 16) & 0xFF;
			checker_color[1] = (color >> 8) & 0xFF;
			checker_color[2] = color & 0xFF;
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
