/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:52:36 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/13 20:12:36 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_INTERSECTION_H
# define SPHERE_INTERSECTION_H

# include "minirt.h"

void		sphere_intersection(t_scene *scene, t_item *item, t_ray *ray);
double		sphere_sh_intersection(t_item *item, t_ray *ray);

#endif
