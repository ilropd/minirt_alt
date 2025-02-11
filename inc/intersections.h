/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:18:10 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/30 15:57:26 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "minirt.h"

void	get_intersections(t_scene *scene, t_ray *ray);
void	check_ray(t_ray *ray, int color, float dist, t_type_id id);

#endif

