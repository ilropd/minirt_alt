/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:38:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 17:17:08 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* vector.c */
t_vector	*new_vector(double x, double y, double z);
float		vector_len(t_vector *vec);
void		vector_normalize(t_vector *vec);

/* vector_prod.c */
float		vector_dot_prod(t_vector *vec1, t_vector *vec2);
t_vector	*vector_cross_prod(t_vector *vec1, t_vector *vec2);
t_vector	vector_cp_dir(const t_vector *vec1, const t_vector *vec2);

/* vector_math.c */
t_vector	*vector_sub(t_vector *vec1, t_vector *vec2);
t_vector	*vector_add(t_vector *vec1, t_vector *vec2);
t_vector	*vector_mult(t_vector *vec, float num);

/* vector_math_dir.c */
t_vector	vector_add_dir(const t_vector *vec1, const t_vector *vec2);
t_vector	vector_sub_dir(const t_vector *vec1, const t_vector *vec2);
t_vector	vector_mult_dir(const t_vector *vec, float num);

/* vector_set.c */
void		vector_set(t_vector *vec, double x, double y, double z);
void	vector_set_table(t_vector *vec, t_scene *scene, int start);
void		vector_set_vparam(t_vector *vec, t_param_id param,
							const t_vector *vec1, const t_vector *vec2);
void		vector_set_sparam(t_vector *vec, t_param_id param,
							const t_vector *vec1, double num);
