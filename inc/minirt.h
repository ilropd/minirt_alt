/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:34:32 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/06 16:20:21 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h> 
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

# include "libft.h"
# include "mlx.h"
# include "X11/keysym.h"

# include "check.h"
# include "colors.h"
# include "err.h"
# include "init.h"
# include "parsing.h"
//# include "plane.h"
//# include "structures.h"
# include "structures_objects.h"
# include "structures_scene.h"
# include "utils.h"
# include "vector.h"

# include "intersections.h"
# include "sphere_intersection.h"
# include "plane_intersection.h"
# include "cylinder_intersection.h"

# include "light_calc.h"
# include "shadow_calc.h"

/* render_init */
int		render_init(t_scene *scene);
void	events(t_scene *scene);

/* ray_tracing.c */
void		ray_tracing(t_scene *scene);
t_viewport	*get_viewport(int width, int height, t_scene *scene);

/* key_handler */
int	destroy_handler(t_scene *scene);
int	key_handler(int key, t_scene *scene);
//int	mouse_handler(int button, int x, int y,  t_mrt *mrt);

#endif
