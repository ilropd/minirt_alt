/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:36:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/25 13:31:30 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_INTERSECTION_H
# define PLANE_INTERSECTION_H

# include "minirt.h"

void	plane_intersection(t_item *item, t_ray *ray);
//void	plane_intersection(t_plane *plane, t_ray *ray);

#endif
