/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:51:29 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/01 22:24:01 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere_intersection.h"

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
			get_sp_normal(ray, sphere, &var);
			color = light_calc(scene, ray, sphere->color);
			check_ray(ray, color, fmin(var.dist1, var.dist2), SP);
		}
	}
}
