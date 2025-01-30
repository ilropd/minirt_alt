/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:51:29 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/30 15:57:54 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere_intersection.h"

void	sphere_intersection(t_item *item, t_ray *ray)
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
			color = rgb_to_int(sphere->color);
			if (var.dist1 <= var.dist2)
				check_ray(ray, color, var.dist1, SP);
			else
				check_ray(ray, color, var.dist2, SP);
		}
	}
}
