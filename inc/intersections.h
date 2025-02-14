/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:18:10 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/13 20:10:43 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "minirt.h"

void	get_intersections(t_scene *scene, t_ray *ray);
void	check_ray(t_ray *ray, int color, float dist, t_type_id id);

#endif
