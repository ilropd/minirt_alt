/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_figures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:55:33 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:37:49 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere(t_item *obj, t_sphere *sphere)
{
	obj->id = SP;
	obj->type.sp = sphere;
	obj->free_obj = free_sphere;
	obj->intersect = sphere_intersection;
	obj->shadows = sphere_sh_intersection;
}

void	set_plane(t_item *obj, t_plane *plane)
{
	obj->id = PL;
	obj->type.pl = plane;
	obj->free_obj = free_plane;
	obj->intersect = plane_intersection;
	obj->shadows = plane_sh_intersection;
}

void	set_cylinder(t_item *obj, t_cylinder *cylinder)
{
	obj->id = CY;
	obj->type.cy = cylinder;
	obj->free_obj = free_cylinder;
	obj->intersect = cylinder_intersection;
}
