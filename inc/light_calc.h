/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:17:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 21:38:25 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_CALC_H
# define LIGHT_CALC_H

# include "minirt.h"

/* light_calc.c */
int		light_calc(t_scene *scene, t_ray *ray, unsigned int color[3]);

/* check_cam_inside.c */
void	cam_inside_sphere(t_scene *scene, t_item *item);
void	cam_inside_cylinder(t_scene *scene, t_item *item);

/* check_light_inside.c */
int		light_inside_sphere(t_scene *scene, t_sphere *sp);
int		light_inside_cylinder(t_scene *scene, t_cylinder *cy);
#endif
