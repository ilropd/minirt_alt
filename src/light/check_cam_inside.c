/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cam_inside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:34:22 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 21:51:00 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_calc.h"

void	cam_inside_sphere(t_scene *scene, t_item *item)
{
	t_sphere	*sphere;
	double		dist;

	if (!item || !item->type.sp)
		return ;
	sphere = item->type.sp;
	dist = sqrt(pow(sphere->cam_sphere.x, 2)
			+ pow(sphere->cam_sphere.y, 2)
			+ pow(sphere->cam_sphere.z, 2));
	if (dist <= sphere->radius && light_inside_sphere(scene, sphere) == 0)
		scene->cam.is_inside = 1;
}

static int	is_perpendicular(t_scene *sc, t_cylinder *cy)
{
	t_vector	axis;
	t_vector	closest_point;
	double		dp;
	double		t;
	double		coord[3];

	axis = vector_sub_dir(&cy->top_cap, &cy->bottom_cap);
	dp = vector_dot_prod(&axis, &cy->cam_cylinder);
	t = dp / (pow(axis.x, 2) + pow(axis.y, 2) + pow(axis.z, 2));
	if (t >= 0.0 && t <= 1.0)
	{
		closest_point.x = cy->bottom_cap.x + t * axis.x;
		closest_point.y = cy->bottom_cap.y + t * axis.y;
		closest_point.z = cy->bottom_cap.z + t * axis.z;
		coord[0] = sc->cam.center.x - closest_point.x;
		coord[1] = sc->cam.center.y - closest_point.y;
		coord[2] = sc->cam.center.z - closest_point.z;
		if ((pow(coord[0], 2) + pow(coord[1], 2) + pow(coord[2], 2))
			<= pow(cy->radius, 2))
			return (1);
	}
	return (0);
}

void	cam_inside_cylinder(t_scene *scene, t_item *item)
{
	t_cylinder	*cylinder;

	if (!item || !item->type.cy)
		return ;
	cylinder = item->type.cy;
	if (is_perpendicular(scene, cylinder) == 1
		&& light_inside_cylinder(scene, cylinder) == 0)
		scene->cam.is_inside = 1;
}
