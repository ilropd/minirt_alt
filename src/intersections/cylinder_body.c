/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 18:23:25 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"

static int	cy_limit(t_cylinder *cylinder, t_ray *ray, double dist)
{
	t_vector	point;
	t_vector	temp;
	double		h;

	temp = vector_mult_dir(&ray->v_ray, dist);
	point = vector_add_dir(&ray->ray_orgn, &temp);
	temp = vector_sub_dir(&point, &cylinder->bottom_cap);
	h = vector_dot_prod(&temp, &cylinder->orient);
	return (h >= 0 && h <= cylinder->height);
}

double	cy_body(t_cylinder *cy, t_ray *ray)
{
	t_sp_vars	var;
	double		dist_min_body;

	dist_min_body = MAXFLOAT;
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray)
		- pow(vector_dot_prod(&ray->v_ray, &cy->orient), 2);
	var.b = 2 * (vector_dot_prod(&ray->v_ray, &cy->cam_cylinder)
			- (vector_dot_prod(&ray->v_ray, &cy->orient)
				* vector_dot_prod(&cy->cam_cylinder, &cy->orient)));
	var.c = vector_dot_prod(&cy->cam_cylinder, &cy->cam_cylinder)
		- pow(vector_dot_prod(&cy->cam_cylinder, &cy->orient), 2)
		- pow(cy->radius, 2);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 && cy_limit(cy, ray, var.dist1))
			dist_min_body = var.dist1;
		if (var.dist2 > 0 && cy_limit(cy, ray, var.dist2))
			dist_min_body = fmin(var.dist1, var.dist2);
	}
	return (dist_min_body);
}

double	cy_sh_body(t_cylinder *cy, t_ray *ray)
{
	t_sp_vars	var;
	t_vector	temp;
	double		dist_min_body;

	dist_min_body = MAXFLOAT;
	temp = vector_sub_dir(&ray->ray_orgn, &cy->bottom_cap);
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray)
		- pow(vector_dot_prod(&ray->v_ray, &cy->orient), 2);
	var.b = 2 * (vector_dot_prod(&ray->v_ray, &temp)
			- (vector_dot_prod(&ray->v_ray, &cy->orient)
				* vector_dot_prod(&temp, &cy->orient)));
	var.c = vector_dot_prod(&temp, &temp)
		- pow(vector_dot_prod(&temp, &cy->orient), 2)
		- pow(cy->radius, 2);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 && cy_limit(cy, ray, var.dist1))
			dist_min_body = var.dist1;
		if (var.dist2 > 0 && cy_limit(cy, ray, var.dist2))
			dist_min_body = fmin(var.dist1, var.dist2);
	}
	return (dist_min_body);
}
