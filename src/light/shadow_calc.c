/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:38:54 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:09:54 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_calc.h"

static t_ray	*shadow_ray_init(t_scene *sc, t_ray *ray)
{
	t_ray		*shadow_ray;
	t_vector	*temp;

	shadow_ray = malloc(sizeof(t_ray));
	if (!shadow_ray)
	{
		free_all(sc);
		exit(1);
	}
	shadow_ray->v_ray = *vector_sub(&sc->light.center, &ray->hit_p);
	vector_normalize(&shadow_ray->v_ray);
	temp = vector_mult(&ray->normal, 1e-4);
	shadow_ray->ray_orgn = *vector_add(&ray->hit_p, temp);
	shadow_ray->normal = (t_vector){0, 0, 0};
	shadow_ray->hit_p = (t_vector){0, 0, 0};
	shadow_ray->id = NONE;
	shadow_ray->ray_x = 0.0;
	shadow_ray->ray_y = 0.0;
	shadow_ray->cap_hit = -100;
	shadow_ray->hit = 0;
	shadow_ray->dot_color = 0;
	shadow_ray->dist_curr = MAXFLOAT;
	free(temp);
	return (shadow_ray);
}

int	shadow_calc(t_scene *scene, t_ray *ray)
{
	t_ray		*shadow_ray;
	t_item		*all_objs;

	all_objs = scene->objs;
	shadow_ray = shadow_ray_init(scene, ray);
	while (all_objs)
    {
        if (all_objs->shadows(all_objs, shadow_ray) == 1)
        {
            free(shadow_ray);
            return (1);
        }
        all_objs = all_objs->next;
    }
	free(shadow_ray);
	return (0);
}
