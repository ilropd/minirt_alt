/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:36:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/11 19:43:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_INTERSECTION_H
# define PLANE_INTERSECTION_H

# include "minirt.h"

void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray);
double		plane_sh_intersection(t_item *item, t_ray *ray);

#endif
