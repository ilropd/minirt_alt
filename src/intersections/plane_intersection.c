/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:18:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/25 13:31:04 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane_intersection.h"

void	plane_intersection(t_item *item, t_ray *ray)
{
	int		color;
	float	denom;
	float	dist;
	t_plane	*plane;

	plane = item->type.pl;
	denom = vector_dot_prod(&ray->v_ray, &plane->orient);
	if (fabs(denom) >= 1e-6)
	{
		dist = (vector_dot_prod(&plane->center, &plane->orient) - vector_dot_prod(&plane->cam_plane, &plane->orient)) / denom;
		if (dist > 0)
		{
			color = ((plane->color[0] << 16) | (plane->color[1] << 8) | plane->color[2]);
//			printf("r: %d, g: %d, b: %d\n", plane->color[0], plane->color[1], plane->color[2]);
			check_ray(ray, color, dist);
		}
	}
}
