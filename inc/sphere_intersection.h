/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:52:36 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:05:46 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_INTERSECTION_H
# define SPHERE_INTERSECTION_H

# include "minirt.h"

void	sphere_intersection(t_scene *scene, t_item *item, t_ray *ray);
int		sphere_sh_intersection(t_item *item, t_ray *ray);

#endif

