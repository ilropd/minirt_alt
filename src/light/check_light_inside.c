/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light_inside.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 21:34:26 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/25 21:27:47 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_calc.h"

int	light_inside_sphere(t_scene *scene, t_sphere *sp)
{
	t_vector	l_sp;
	double		dist;

	l_sp = vector_sub_dir(&scene->light.center, &sp->center);
	dist = sqrt(pow(l_sp.x, 2)
			+ pow(l_sp.y, 2)
			+ pow(l_sp.z, 2));
	if (dist <= sp->radius)
		return (1);
	return (0);
}

int	light_inside_cylinder(t_scene *sc, t_cylinder *cy)
{
	t_vector	axis;
	t_vector	closest_point;
	t_vector	l_cy;
	double		dp_t[2];
	double		coord[3];

	l_cy = vector_sub_dir(&sc->light.center, &cy->center);
	axis = vector_sub_dir(&cy->top_cap, &cy->bottom_cap);
	dp_t[0] = vector_dot_prod(&axis, &l_cy);
	dp_t[1] = dp_t[0] / (pow(axis.x, 2) + pow(axis.y, 2) + pow(axis.z, 2));
	if (dp_t[1] >= 0.0 && dp_t[1] <= 1.0)
	{
		closest_point.x = cy->bottom_cap.x + dp_t[1] * axis.x;
		closest_point.y = cy->bottom_cap.y + dp_t[1] * axis.y;
		closest_point.z = cy->bottom_cap.z + dp_t[1] * axis.z;
		coord[0] = sc->light.center.x - closest_point.x;
		coord[1] = sc->light.center.y - closest_point.y;
		coord[2] = sc->light.center.z - closest_point.z;
		if ((pow(coord[0], 2) + pow(coord[1], 2) + pow(coord[2], 2))
			<= pow(cy->radius, 2))
			return (1);
	}
	return (0);
}

int	light_inside_cone(t_scene *scene, t_cone *cone)
{
	t_vector	d;
	double		proj;
	double		dist;
	double		allowed_radius;

	d = vector_sub_dir(&scene->light.center, &cone->vertex);
	proj = vector_dot_prod(&d, &cone->orient);
	if (proj < 0 || proj > cone->height)
		return (0);
	dist = sqrt(vector_dot_prod(&d, &d) - proj * proj);
	allowed_radius = (proj * cone->radius) / cone->height;
	if (dist <= allowed_radius)
		return (1);
	return (0);
}
