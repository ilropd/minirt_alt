/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/19 12:46:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

static void	get_cy_normal(t_ray *ray, t_cylinder *cy, double dist)
{
	t_vector	hit_point;
	t_vector	axis_point;
	t_vector	temp;
	double		dl;

	vector_set(&ray->hit_p, ray->ray_orgn.x + ray->v_ray.x * dist,
		ray->ray_orgn.y + ray->v_ray.y * dist,
		ray->ray_orgn.z + ray->v_ray.z * dist);
	if (ray->cap_hit == 0)
	{
		hit_point = vector_sub_dir(&ray->hit_p, &cy->bottom_cap);
		dl = vector_dot_prod(&hit_point, &cy->orient);
		temp = vector_mult_dir(&cy->orient, dl);
		axis_point = vector_add_dir(&cy->bottom_cap, &temp);
		vector_set_vparam(&ray->normal, SUB, &ray->hit_p, &axis_point);
		vector_normalize(&ray->normal);
	}
	else
		vector_set_sparam(&ray->normal, MULT, &cy->orient, ray->cap_hit);
}

void	cylinder_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	double		d_body;
	double		d_caps;
	int			color;

	cylinder = item->type.cy;
	d_body = cy_body(cylinder, ray);
	d_caps = MAXFLOAT;
	cy_caps(cylinder, ray, &d_caps);
	if (d_body < MAXFLOAT || d_caps < MAXFLOAT)
	{
		if (d_body < d_caps)
		{
			ray->cap_hit = 0;
			get_cy_normal(ray, cylinder, d_body);
		}
		else
			get_cy_normal(ray, cylinder, d_caps);
		ray->hit = 1;
		color = light_calc(scene, ray, cylinder->color);
		check_ray(ray, color, fmin(d_body, d_caps), CY);
	}
}

double	cylinder_sh_intersection(t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	double		d_body;
	double		d_caps;

	cylinder = item->type.cy;
	d_body = MAXFLOAT;
	d_body = cy_sh_body(cylinder, ray);
	d_caps = MAXFLOAT;
	cy_caps(cylinder, ray, &d_caps);
	if (d_body < MAXFLOAT || d_caps < MAXFLOAT)
		return (fmin(d_body, d_caps));
	return (MAXFLOAT);
}
