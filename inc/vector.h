/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:38:50 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/24 14:50:25 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* vector.c */
t_vector	*new_vector(double x, double y, double z);
float		vector_len(t_vector *vec);
void		vector_set(t_vector *vec, double x, double y, double z);
void		vector_normalize(t_vector *vec);

/* vector_prod.c */
float		vector_dot_prod(t_vector *vec1, t_vector *vec2);
t_vector	*vector_cross_prod(t_vector *vec1, t_vector *vec2);

/* vector_math.c*/
t_vector	*vector_sub(t_vector *vec1, t_vector *vec2);
t_vector	*vector_add(t_vector *vec1, t_vector *vec2);
t_vector	*vector_mult(t_vector *vec, float num);
