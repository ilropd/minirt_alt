/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:18:10 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/19 12:50:46 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "minirt.h"

/* intersections.c */
void	get_intersections(t_scene *scene, t_ray *ray);
void	check_ray(t_ray *ray, int color, double dist, t_type_id id);

/* cylinder_intersection.c */
void	cylinder_intersection(t_scene *scene, t_item *item, t_ray *ray);
double	cylinder_sh_intersection(t_item *item, t_ray *ray);

/* cylinder_body.c */
double	cy_body(t_cylinder *cy, t_ray *ray);
double	cy_sh_body(t_cylinder *cy, t_ray *ray);

/* cylinder_caps.c */
void	cy_caps(t_cylinder *cy, t_ray *ray, double *d_caps);

/* plane_intersection.h */
void	plane_intersection(t_scene *scene, t_item *item, t_ray *ray);
double	plane_sh_intersection(t_item *item, t_ray *ray);

/* sphere_intersection.c */
void	sphere_intersection(t_scene *scene, t_item *item, t_ray *ray);
double	sphere_sh_intersection(t_item *item, t_ray *ray);

#endif
