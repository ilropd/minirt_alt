/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:05:12 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 14:37:15 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	right_comp_calc(t_vector *up, t_scene *scene, double ray_x)
{
	t_vector	res;
	t_vector	right;

	right = vector_cp_dir(up, &scene->cam.orient);
	res = vector_mult_dir(&right, ray_x);
	return (res);
}

static void	camray(t_scene *scene, t_ray *ray)
{
	t_vector	up;
	t_vector	right_comp;
	t_vector	up_comp;
	t_vector	hor_vert;

	if (fabs(scene->cam.orient.x) < 1e-4 && fabs(scene->cam.orient.z) < 1e-4)
		up = (t_vector){0, 0, 1};
	else if (fabs(scene->cam.orient.y) > 0.99)
		up = (t_vector){1, 0, 0};
	else
		up = (t_vector){0, 1, 0};
	right_comp = right_comp_calc(&up, scene, ray->ray_x);
	up_comp = vector_mult_dir(&up, ray->ray_y);
	hor_vert = vector_add_dir(&right_comp, &up_comp);
	ray->v_ray = vector_add_dir(&hor_vert, &scene->cam.orient);
	vector_set(&ray->ray_orgn, scene->cam.center.x, scene->cam.center.y,
		scene->cam.center.z);
	vector_normalize(&ray->v_ray);
}

static t_ray	*ray_init(t_scene *scene)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
	{
		free_all(scene);
		exit(1);
	}
	ray->v_ray = (t_vector){0, 0, 0};
	ray->ray_orgn = scene->cam.center;
	ray->normal = (t_vector){0, 0, 0};
	ray->hit_p = (t_vector){0, 0, 0};
	ray->id = NONE;
	ray->ray_x = 0.0;
	ray->ray_y = 0.0;
	ray->cap_hit = -100;
	ray->hit = 0;
	ray->dot_color = 0;
	ray->is_shadow = 0;
	ray->dist_curr = MAXFLOAT;
	return (ray);
}

void	ray_tracing(t_scene *scene)
{
	t_ray		*ray;
	t_viewport	*viewport;

	viewport = get_viewport(WIDTH, HEIGHT, scene);
	ray = ray_init(scene);
	scene->mrt.angle_y = HEIGHT / 2;
	while (scene->mrt.angle_y >= (HEIGHT / 2) * (-1))
	{
		ray->ray_y = scene->mrt.angle_y * viewport->y_pixel;
		scene->mrt.angle_x = (WIDTH / 2) * (-1);
		while (scene->mrt.angle_x <= (WIDTH / 2))
		{
			ray->ray_x = scene->mrt.angle_x * viewport->x_pixel;
			camray(scene, ray);
			get_intersections(scene, ray);
			mlx_pixel_put(scene->mrt.connection, scene->mrt.window,
				(WIDTH / 2) + scene->mrt.angle_x,
				(HEIGHT / 2) - scene->mrt.angle_y, ray->dot_color);
			scene->mrt.angle_x++;
		}
		scene->mrt.angle_y--;
	}
	free(ray);
	free(viewport);
}

t_viewport	*get_viewport(int width, int height, t_scene *scene)
{
	t_viewport	*viewport;
	double		aspect_ratio;

	viewport = malloc(sizeof(t_viewport));
	if (!viewport)
	{
		free_all(scene);
		exit(1);
	}
	aspect_ratio = width / height;
	viewport->width = (tan(scene->cam.fov_rad / 2)) * 2;
	viewport->height = viewport->width / aspect_ratio;
	viewport->x_pixel = viewport->width / width;
	viewport->y_pixel = viewport->height / height;
	return (viewport);
}
