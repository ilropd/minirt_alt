/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_figures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:55:33 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 15:25:15 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere(t_item *obj, t_sphere *sphere)
{
	obj->id = SP;
	obj->type.sp = sphere;
	obj->free_obj = free_sphere;
	obj->update_cam = update_sphere;
	obj->intersect = sphere_intersection;
	obj->inside = cam_inside_sphere;
	obj->shadows = sphere_sh_intersection;
}

void	set_plane(t_item *obj, t_plane *plane)
{
	obj->id = PL;
	obj->type.pl = plane;
	obj->free_obj = free_plane;
	obj->update_cam = update_plane;
	obj->intersect = plane_intersection;
	obj->shadows = plane_sh_intersection;
}

void	set_cylinder(t_item *obj, t_cylinder *cylinder)
{
	obj->id = CY;
	obj->type.cy = cylinder;
	obj->free_obj = free_cylinder;
	obj->update_cam = update_cylinder;
	obj->intersect = cylinder_intersection;
	obj->inside = cam_inside_cylinder;
	obj->shadows = cylinder_sh_intersection;
}
