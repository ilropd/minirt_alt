/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:38:12 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/19 12:55:23 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

/* render.c */
int			destroy_handler(t_scene *scene);
int			key_handler(int key, t_scene *scene);
void		events(t_scene *scene);
int			render_init(t_scene *scene);

/* ray_tracing.c */
void		ray_tracing(t_scene *scene);
t_viewport	*get_viewport(int width, int height, t_scene *scene);

#endif
