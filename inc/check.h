/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:06 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/22 16:15:11 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H

# include "structures_objects.h"
# include "structures_scene.h"

/* checker_ambient.c */
int	check_ambient(char **table);

/* checker.c */
int	arg_counter(char **table);
int	check_digit(const char *str, char type);
int	check_digit_cycle(char **table, char type, int start, int num_args);

/* checker_camera.c */
int	check_camera(char **table);

/* checker_cylinder.c */
int	check_cylinder(char **table);

/* checker_plane.c */
int	check_plane(char **table);

/* checker_sphere.c */
int	check_sphere(char **table);

/* checker_light.c */
int	check_light(char **table);

/* check_limits.c */
int	check_rgb_limit(char **table, int start, int num_args);
int	check_degree_limit(char **table, int start, int num_args);
int	check_ratio_limit(char **table, int start, int num_args);
int	check_vector_limit(char **table, int start, int num_args);
int	check_zerof_limit(char **table, int start, int num_args);

#endif
