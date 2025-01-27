/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:05:12 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/25 18:47:02 by irozhkov         ###   ########.fr       */
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
	t_vector    up;
	t_vector	right_comp;
	t_vector	up_comp;
	t_vector	hor_vert;

	up = (t_vector){0, 1, 0};
	right_comp = right_comp_calc(&up, scene, ray->ray_x);
	up_comp = vector_mult_dir(&up, ray->ray_y);
	hor_vert = vector_add_dir(&right_comp, &up_comp);
	ray->v_ray = vector_add_dir(&hor_vert, &scene->cam.orient);
	vector_set(&ray->ray_orgn, scene->cam.center.x, scene->cam.center.y, scene->cam.center.z);
	vector_normalize(&ray->v_ray);
}

void    ray_tracing(t_scene *scene)
{
	t_ray       *ray;
    t_viewport  *viewport;

    viewport = get_viewport(WIDTH, HEIGHT, scene);
    ray = malloc(sizeof(t_ray));
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
	float		aspect_ratio;

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
