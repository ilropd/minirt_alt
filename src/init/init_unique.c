/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_unique.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:06:45 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/24 15:47:45 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int    init_camera(t_scene *scene)
{
    if (scene->cam.type != NULL)
	{
        return (printf("%s%s", ERROR, ARGS_NUNIQUE_C), 1);
	}
	if (check_camera(scene->table))
	{
        return (printf("%s%s", ERROR, ARGS_WCAM), 1);
	}
	scene->cam.type = scene->table[0];
	if (!scene->cam.type)
        return (printf("%s%s", ERROR, MEM_CAM ), 1);
	vector_set(&scene->cam.center, ft_atof(scene->table[1]), ft_atof(scene->table[2]), ft_atof(scene->table[3]));
	vector_set(&scene->cam.orient, ft_atof(scene->table[4]), ft_atof(scene->table[5]), ft_atof(scene->table[6]));
	scene->cam.fov = ft_atoi(scene->table[7]);
	scene->cam.fov_rad = scene->cam.fov * M_PI / 180;
	printf("Camera Initialized: Type: %s, Center: %f | %f | %f, Orientation: %f | %f | %f, FOV: %d, FOV_RAD: %f\n",
		   scene->cam.type, scene->cam.center.x, scene->cam.center.y, scene->cam.center.z, scene->cam.orient.x, scene->cam.orient.y, scene->cam.orient.z, scene->cam.fov, scene->cam.fov_rad);
	return (0);
}

int	init_ambient(t_scene *scene)
{
	if (scene->amb.type != NULL)
		return (printf("%s%s", ERROR, ARGS_NUNIQUE_A), 1);
	if (check_ambient(scene->table))
        return (printf("%s%s", ERROR, ARGS_WAMB), 1);
	scene->amb.type = scene->table[0];
	if (!scene->amb.type)
		return (printf("%s%s", ERROR, MEM_AMB), 1);
	scene->amb.ratio = ft_atof(scene->table[1]);
	scene->amb.color[0] = ft_atoi(scene->table[2]);
    scene->amb.color[1] = ft_atoi(scene->table[3]);
    scene->amb.color[2] = ft_atoi(scene->table[4]);
	printf("Ambient Light Initialized: Type: %s, Ratio: %.2f, Color: (%u, %u, %u)\n",
           scene->amb.type, scene->amb.ratio, scene->amb.color[0],
		   scene->amb.color[1], scene->amb.color[2]);
	return (0);
}

int	init_light(t_scene *scene)
{
	if (scene->light.type != NULL)
        return (printf("%s%s", ERROR, ARGS_NUNIQUE_L), 1);	
	if (check_light(scene->table))
        return (printf("%s%s", ERROR, ARGS_WLIG), 1);
	scene->light.type= scene->table[0];
	if (!scene->light.type)
        return (printf("%s%s", ERROR, MEM_LIG), 1);
	vector_set(&scene->cam.center, ft_atof(scene->table[1]), ft_atof(scene->table[2]), ft_atof(scene->table[3]));
	scene->light.brightness = ft_atof(scene->table[4]);
	scene->light.color[0] = ft_atoi(scene->table[5]);
    scene->light.color[1] = ft_atoi(scene->table[6]);
    scene->light.color[2] = ft_atoi(scene->table[7]);
	printf("Light initialized: Type: %s, Brightness: %.2f, Center: %f | %f | %f, Color: (%u, %u, %u)\n",
           scene->light.type, scene->light.brightness, scene->light.center.x, scene->light.center.y, scene->light.center.z, scene->light.color[0], scene->light.color[1], scene->light.color[2]);
	return (0);
}
