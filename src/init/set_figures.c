/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_figures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:55:33 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/26 16:55:37 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere(t_item *obj, t_sphere *sphere)
{
	obj->type.sp = sphere;
	obj->free_obj = free_sphere;
}

void	set_plane(t_item *obj, t_plane *plane)
{
	obj->type.pl = plane;
	obj->free_obj = free_plane;
}

void	set_cylinder(t_item *obj, t_cylinder *cylinder)
{
	obj->type.cy = cylinder;
	obj->free_obj = free_cylinder;
}
