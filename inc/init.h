/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:19:36 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 15:17:53 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minirt.h"
# include "structures_scene.h"
# include "structures_objects.h"

/* init_all.c */
int		init_all(t_scene *scene);
void	update_cam_vectors(t_scene *scene);

/* init_figures.c */
int		init_cylinder(t_scene *scene);
int		init_plane(t_scene *scene);
int		init_sphere(t_scene *scene);

/* set_figures.c */
void	set_sphere(t_item *obj, t_sphere *sphere);
void	set_plane(t_item *obj, t_plane *plane);
void	set_cylinder(t_item *obj, t_cylinder *cylinder);

/* init_unique.c */
int		init_camera(t_scene *scene);
int		init_light(t_scene *scene);
int		init_ambient(t_scene *scene);

/* update_cam_vectors.c */
void	update_sphere(t_scene *sc, t_item *item);
void	update_plane(t_scene *sc, t_item *item);
void	update_cylinder(t_scene *sc, t_item *item);
#endif
