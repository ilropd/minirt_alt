/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cam_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:44 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 16:16:09 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	update_sphere(t_scene *sc, t_item *item)
{
	t_sphere *sp;

	sp = item->type.sp;
	vector_set_vparam(&sp->cam_sphere, SUB, &sc->cam.center, &sp->center);
}

void	update_plane(t_scene *sc, t_item *item)
{
	t_plane	*pl;

	pl = item->type.pl;
	vector_set_vparam(&pl->cam_plane, SUB, &sc->cam.center, &pl->center);
}

void	update_cylinder(t_scene *sc, t_item *item)
{
	t_cylinder	*cy;

	cy = item->type.cy;
	vector_set_vparam(&cy->cam_cylinder, SUB, &sc->cam.center,
		&cy->bottom_cap);
}
