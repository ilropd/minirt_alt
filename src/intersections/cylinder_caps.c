/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 18:53:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"

static void	check_hit(t_cylinder *cy, t_ray *ray, double *d_caps, double dist)
{
	t_vector	point;
	t_vector	temp;
	double		dist_to_center;

	if (dist > 0)
	{
		temp = vector_mult_dir(&ray->v_ray, dist);
		point = vector_add_dir(&ray->ray_orgn, &temp);
		if (ray->cap_hit == -1)
			temp = vector_sub_dir(&cy->bottom_cap, &point);
		else
			temp = vector_sub_dir(&cy->top_cap, &point);
		dist_to_center = vector_len(&temp);
		if (dist_to_center <= cy->radius && dist < *d_caps)
			*d_caps = dist;
	}
}

static void	cap_bottom(t_cylinder *cy, t_ray *ray, double *d_caps, double denom)
{
	t_vector	temp;
	double		dist_bottom;

	temp = vector_sub_dir(&cy->bottom_cap, &ray->ray_orgn);
	dist_bottom = vector_dot_prod(&temp, &cy->orient) / denom;
	ray->cap_hit = -1;
	check_hit(cy, ray, d_caps, dist_bottom);
}

static void	cap_top(t_cylinder *cy, t_ray *ray, double *d_caps, double denom)
{
	t_vector	temp;
	double		dist_top;

	temp = vector_sub_dir(&cy->top_cap, &ray->ray_orgn);
	dist_top = vector_dot_prod(&temp, &cy->orient) / denom;
	ray->cap_hit = 1;
	check_hit(cy, ray, d_caps, dist_top);
}

void	cy_caps(t_cylinder *cy, t_ray *ray, double *d_caps)
{
	double	denom;

	denom = vector_dot_prod(&ray->v_ray, &cy->orient);
	if (fabs(denom) > 1e-6)
	{
		cap_bottom(cy, ray, d_caps, denom);
		cap_top(cy, ray, d_caps, denom);
	}
}
