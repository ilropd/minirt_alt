/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:58:28 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/25 18:51:36 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_add_dir(const t_vector *vec1, const t_vector *vec2)
{
	t_vector	res;

	res.x = vec1->x + vec2->x;
	res.y = vec1->y + vec2->y;
	res.z = vec1->z + vec2->z;
	return (res);
}

t_vector	vector_sub_dir(const t_vector *vec1, const t_vector *vec2)
{
	t_vector	res;

	res.x = vec1->x - vec2->x;
	res.y = vec1->y - vec2->y;
	res.z = vec1->z - vec2->z;
	return (res);
}

t_vector	vector_mult_dir(const t_vector *vec, float num)
{
	t_vector	res;

	res.x = vec->x * num;
	res.y = vec->y * num;
	res.z = vec->z * num;
	return (res);
}
