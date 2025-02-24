/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:51:29 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/19 12:50:56 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

static void	get_sp_normal(t_ray *ray, t_sphere *sp, t_sp_vars *var)
{
	double	t;

	t = fmin(var->dist1, var->dist2);
	vector_set(&ray->hit_p, (ray->ray_orgn.x + ray->v_ray.x * t),
		(ray->ray_orgn.y + ray->v_ray.y * t),
		(ray->ray_orgn.z + ray->v_ray.z * t));
	vector_set(&ray->normal, ray->hit_p.x - sp->center.x,
		ray->hit_p.y - sp->center.y,
		ray->hit_p.z - sp->center.z);
	vector_normalize(&ray->normal);
}

void	sphere_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	t_sphere	*sphere;
	t_sp_vars	var;
	int			color;

	sphere = item->type.sp;
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray);
	var.b = 2 * vector_dot_prod(&sphere->cam_sphere, &ray->v_ray);
	var.c = vector_dot_prod(&sphere->cam_sphere, &sphere->cam_sphere)
		- (sphere->radius * sphere->radius);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 || var.dist2 > 0)
		{
			ray->hit = 1;
			get_sp_normal(ray, sphere, &var);
			color = light_calc(scene, ray, sphere->color);
			check_ray(ray, color, fmin(var.dist1, var.dist2), SP);
		}
	}
}

double	sphere_sh_intersection(t_item *item, t_ray *ray)
{
	t_sphere	*sphere;
	t_vector	*temp;
	t_sp_vars	var;

	sphere = item->type.sp;
	temp = vector_sub(&ray->ray_orgn, &sphere->center);
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray);
	var.b = 2 * vector_dot_prod(temp, &ray->v_ray);
	var.c = vector_dot_prod(temp, temp) - (sphere->radius * sphere->radius);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	free(temp);
	if (var.discr < 0)
		return (MAXFLOAT);
	var.dist1 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
	var.dist2 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
	if (var.dist1 > 0 && var.dist2 > 0)
		return (fmin(var.dist1, var.dist2));
	else if ((var.dist1 > 0 || var.dist2 > 0))
		return (fmax(var.dist1, var.dist2));
	return (MAXFLOAT);
}
