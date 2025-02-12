/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:56:14 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/12 13:21:24 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_INTERSECTION_H
# define CYLINDER_INTERSECTION_H

# include "minirt.h"

void	cylinder_intersection(t_scene *scene, t_item *item, t_ray *ray);
double	cylinder_sh_intersection(t_item *item, t_ray *ray);

#endif
