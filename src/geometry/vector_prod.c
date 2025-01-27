/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_prod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:37:17 by irozhkov          #+#    #+#             */
/*   Updated: 2024/12/15 16:07:22 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	vector_dot_prod(t_vector *vec1, t_vector *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

t_vector	*vector_cross_prod(t_vector *vec1, t_vector *vec2)
{
	t_vector	*res;
	float		x;
	float		y;
	float		z;

	x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
	y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
	z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
	res = new_vector(x, y, z);
	return (res);
}

t_vector	vector_cp_dir(const t_vector *vec1, const t_vector *vec2)
{
    t_vector	res;

	res.x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
	res.y = (vec1->z * vec2->x) - (vec1->x * vec2->z);
	res.z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
	return (res);
}

