/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:45:09 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 16:24:49 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*new_vector(double x, double y, double z)
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
		exit(1);
//		malloc_err(); // TODO
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

float	vector_len(t_vector *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

void	vector_normalize(t_vector *vec)
{
	float	len;

	len = vector_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}
