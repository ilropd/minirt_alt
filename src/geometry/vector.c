/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:45:09 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 18:42:25 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*new_vector(double x, double y, double z)
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
	{
		printf("%s%s", ERROR, MEM);
		exit(1);
	}
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

double	vector_len(t_vector *vec)
{
	return (sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z)));
}

void	vector_normalize(t_vector *vec)
{
	double	len;

	len = vector_len(vec);
	vec->x /= len;
	vec->y /= len;
	vec->z /= len;
}
