/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:16:36 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:10:36 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light_calc.h"

static int color_calc(t_scene *scene, float intensity, unsigned int color[3])
{
	unsigned int	rgb[3];
	unsigned int	amb_rgb[3];

	amb_rgb[0] = fmin(255, scene->amb.ratio * scene->amb.color[0]
					* color[0] / 255);
	amb_rgb[1] = fmin(255, scene->amb.ratio * scene->amb.color[1]
					* color[1] / 255);
	amb_rgb[2] = fmin(255, scene->amb.ratio * scene->amb.color[2]
					* color[2] / 255);
	rgb[0] = fmin(255, intensity * scene->light.color[0]
				* color[0] / 255 + amb_rgb[0]);
	rgb[1] = fmin(255, intensity * scene->light.color[1]
				* color[1] / 255 + amb_rgb[1]);
	rgb[2] = fmin(255, intensity * scene->light.color[2]
				* color[2] / 255 + amb_rgb[2]);
	return (rgb_to_int(rgb));
}

static float diffuse_calc(t_scene *scene, t_ray *ray)
{
	float		dif_dot_spec[3];
	int			is_shadow;
	t_vector	*light_dir;
	t_vector	*view_dir;
	t_vector	*reflect_dir;
	t_vector	*temp;

	light_dir = vector_sub(&scene->light.center, &ray->hit_p);
	vector_normalize(light_dir);
	view_dir = vector_sub(&ray->ray_orgn, &ray->hit_p);
	vector_normalize(view_dir);
	dif_dot_spec[1] = vector_dot_prod(&ray->normal, light_dir);
	temp = vector_mult(&ray->normal, 2 * dif_dot_spec[1]);
	reflect_dir = vector_sub(temp, light_dir);
	vector_normalize(reflect_dir);
	free(temp);	
	is_shadow = shadow_calc(scene, ray);
	if (is_shadow == 1)
	{
		dif_dot_spec[0] = 0;
		dif_dot_spec[2] = 0;
	}
	else
	{
		dif_dot_spec[0] = fmax(0, dif_dot_spec[1]);
		dif_dot_spec[2] = pow(fmax(0, vector_dot_prod(view_dir, reflect_dir)), SPEC);
	}
//	dif_dot_spec[0] = fmax(0, dif_dot_spec[1]);
//	dif_dot_spec[2] = pow(fmax(0, vector_dot_prod(view_dir, reflect_dir)), SPEC);
	free(light_dir);
	free(view_dir);
	free(reflect_dir);
	return (scene->light.brightness * (dif_dot_spec[0] + dif_dot_spec[2]));
}

int	light_calc(t_scene *scene, t_ray *ray, unsigned int color[3])
{
	float	intensity;

	intensity = diffuse_calc(scene, ray);
	return (color_calc(scene, intensity, color));
}
