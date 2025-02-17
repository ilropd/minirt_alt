/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:56:14 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 18:06:55 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_INTERSECTION_H
# define CYLINDER_INTERSECTION_H

# include "minirt.h"

/* cylinder_intersection.c */
void	cylinder_intersection(t_scene *scene, t_item *item, t_ray *ray);
double	cylinder_sh_intersection(t_item *item, t_ray *ray);

/* cylinder_body.c */
double	cy_body(t_cylinder *cy, t_ray *ray);
double	cy_sh_body(t_cylinder *cy, t_ray *ray);

/* cylinder_caps.c */
void	cy_caps(t_cylinder *cy, t_ray *ray, double *d_caps);

#endif
