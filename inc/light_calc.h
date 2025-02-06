/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:17:31 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/01 14:02:40 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_CALC_H
# define LIGHT_CALC_H

# include "minirt.h"

int	light_calc(t_scene *scene, t_ray *ray, unsigned int color[3]);

#endif
