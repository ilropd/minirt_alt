/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:36:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:38:54 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_INTERSECTION_H
# define PLANE_INTERSECTION_H

# include "minirt.h"

void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray);
int		plane_sh_intersection(t_item *item, t_ray *ray);

#endif
