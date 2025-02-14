/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:05:53 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 17:16:39 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_set(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	vector_set_table(t_vector *vec, t_scene *scene, int start)
{
	double	x;
	double	y;
	double	z;

	x = ft_atof(scene->table[start]);
	y = ft_atof(scene->table[start + 1]);
	z = ft_atof(scene->table[start + 2]);
	vector_set(vec, x, y, z);
}

void	vector_set_vparam(t_vector *vec, t_param_id param,
						const t_vector *vec1, const t_vector *vec2)
{
	t_vector	res;

	if (param == ADD)
		res = vector_add_dir(vec1, vec2);
	else if (param == SUB)
		res = vector_sub_dir(vec1, vec2);
	vector_set(vec, res.x, res.y, res.z);
}

void	vector_set_sparam(t_vector *vec, t_param_id param,
						const t_vector *vec1, double num)
{
	t_vector	res;

	if (param == MULT)
		res = vector_mult_dir(vec1, num);
	vector_set(vec, res.x, res.y, res.z);
}
