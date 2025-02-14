/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:38:54 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/14 19:30:26 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_calc.h"

static t_vector	*set_bias(t_ray *ray)
{
	t_vector	*temp;

	if (ray->id == PL)
		temp = vector_mult(&ray->normal, PL_BIAS);
	else
		temp = vector_mult(&ray->normal, BIAS);
	return (temp);
}

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
	shadow_ray->v_ray = vector_sub_dir(&sc->light.center, &ray->hit_p);
	vector_normalize(&shadow_ray->v_ray);
	temp = set_bias(ray);
	shadow_ray->ray_orgn = vector_add_dir(&ray->hit_p, temp);
	shadow_ray->normal = (t_vector){0, 0, 0};
	shadow_ray->hit_p = (t_vector){0, 0, 0};
	shadow_ray->id = ray->id;
	shadow_ray->ray_x = 0.0;
	shadow_ray->ray_y = 0.0;
	shadow_ray->cap_hit = -100;
	shadow_ray->hit = 0;
	shadow_ray->dot_color = 0;
	shadow_ray->dist_curr = MAXFLOAT;
	free(temp);
	return (shadow_ray);
}

static double	light_dist_culc(t_scene *scene, t_ray *shadow_ray)
{
	t_vector	*light_vec;
	double		dist;

	light_vec = vector_sub(&scene->light.center, &shadow_ray->ray_orgn);
	dist = vector_len(light_vec);
	free(light_vec);
	return (dist);
}

int	shadow_calc(t_scene *scene, t_ray *ray)
{
	t_ray		*shadow_ray;
	t_item		*all_objs;
	double		light_dist;
	double		dist;

	all_objs = scene->objs;
	shadow_ray = shadow_ray_init(scene, ray);
	light_dist = light_dist_culc(scene, shadow_ray);
	while (all_objs)
	{
		dist = all_objs->shadows(all_objs, shadow_ray);
		if (dist < light_dist && dist > 1e-4)
		{
			free(shadow_ray);
			return (1);
		}
		all_objs = all_objs->next;
	}
	free(shadow_ray);
	return (0);
}
