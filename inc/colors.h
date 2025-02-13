/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/13 13:52:09 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "minirt.h"

/* colors.c */
int		average_colors(int col1, int col2);
int		rgb_to_int(unsigned int color[3]);
void	set_color(t_scene *scene, void *obj_color, int start);

#endif
