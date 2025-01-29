/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:33 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/29 16:07:24 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_sphere(t_scene *scene)
{
	t_sphere	*sphere;
	t_item		*obj;

	obj = add_obj(scene->objs, scene);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (printf("%s%s", ERROR, MEM_SP), 1);
	set_sphere(obj, sphere);
	sphere->type = scene->table[0];
	if (!sphere->type)
		return (printf("%s%s", ERROR, MEM_SP), 1);
	vector_set(&sphere->center, ft_atof(scene->table[1]), ft_atof(scene->table[2]), ft_atof(scene->table[3]));
	printf("cam x: %f, sphere x: %f\ncam y: %f, sphere y: %f\ncam z: %f, sphere z: %f\n", scene->cam.center.x, sphere->center.x, scene->cam.center.y, sphere->center.y, scene->cam.center.z, sphere->center.z);
	vector_set(&sphere->cam_sphere, scene->cam.center.x - sphere->center.x, scene->cam.center.y - sphere->center.y, scene->cam.center.z - sphere->center.z);
    sphere->diameter = ft_atof(scene->table[4]);
    sphere->radius = sphere->diameter / 2;
    sphere->color[0] = ft_atoi(scene->table[5]);
    sphere->color[1] = ft_atoi(scene->table[6]);
    sphere->color[2] = ft_atoi(scene->table[7]);
	printf("Sphere Initialized: Type: %s, Center: %f | %f | %f, Diameter: %f, Radius: %f, Color: (%u, %u, %u)\n", sphere->type, sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter, sphere->radius, sphere->color[0], sphere->color[1], sphere->color[2]);
	return (0);
}

int	init_plane(t_scene *scene)
{
	t_plane	*plane;
	t_item	*obj;

	obj = add_obj(scene->objs, scene);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (printf("%s%s", ERROR, MEM_PL), 1);
	set_plane(obj, plane);
	plane->type = scene->table[0];
	if (!plane->type)
		return (printf("%s%s", ERROR, MEM_PL), 1);
	vector_set (&plane->center, ft_atof(scene->table[1]), ft_atof(scene->table[2]), ft_atof(scene->table[3]));
    vector_set(&plane->orient, ft_atof(scene->table[4]), ft_atof(scene->table[5]), ft_atof(scene->table[6]));
	vector_set(&plane->cam_plane, scene->cam.center.x - plane->center.x, scene->cam.center.y - plane->center.y, scene->cam.center.z - plane->center.z);
    plane->color[0] = ft_atoi(scene->table[7]);
    plane->color[1] = ft_atoi(scene->table[8]);
    plane->color[2] = ft_atoi(scene->table[9]);
	printf("Plane Initialized: Type: %s, Center: %f | %f | %f, Orient: %f | %f | %f, Color: (%u, %u, %u)\n", plane->type, plane->center.x, plane->center.y, plane->center.z, plane->orient.x, plane->orient.y, plane->orient.z, plane->color[0], plane->color[1], plane->color[2]);
    return (0);
}

static void find_cy_caps(t_cylinder *cy)
{
	t_vector	*orient_mult;
	t_vector	*top;
//	t_vector	*bottom;

//	orient_mult = vector_mult(&cy->orient, (cy->height / 2));
	orient_mult = vector_mult(&cy->orient, cy->height);
	top = vector_add(&cy->center, orient_mult);
//	bottom = vector_sub(orient_mult, &cy->center);
	vector_set(&cy->top_cap, top->x, top->y, top->z);
	vector_set(&cy->bottom_cap, cy->center.x, cy->center.y, cy->center.z);
//	printf("CAPS: btm: %f | %f |%f --- top: %f | %f | %f\n", cy->bottom_cap.x, cy->bottom_cap.y, cy->bottom_cap.z, top->x, top->y, top->z);
	free(orient_mult);
	free(top);
//	free(bottom);
}

int	init_cylinder(t_scene *scene)
{
	t_cylinder	*cylinder;
	t_item		*obj;

	obj = add_obj(scene->objs, scene);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (printf("%s%s", ERROR, MEM_CY), 1);
	set_cylinder(obj, cylinder);
	cylinder->type = scene->table[0];
	if (!cylinder->type)
		return (printf("%s%s", ERROR, MEM_CY), 1);
	vector_set(&cylinder->center, ft_atof(scene->table[1]), ft_atof(scene->table[2]), ft_atof(scene->table[3]));
    vector_set(&cylinder->orient, ft_atof(scene->table[4]), ft_atof(scene->table[5]), ft_atof(scene->table[6]));
//	vector_set(&cylinder->cam_cylinder, scene->cam.center.x - cylinder->center.x, scene->cam.center.y - cylinder->center.y, scene->cam.center.z - cylinder->center.z);
    cylinder->diameter = ft_atof(scene->table[7]);
	cylinder->radius = cylinder->diameter / 2;
    cylinder->height = ft_atof(scene->table[8]);
	find_cy_caps(cylinder);
	vector_set(&cylinder->cam_cylinder, scene->cam.center.x - cylinder->bottom_cap.x, scene->cam.center.y - cylinder->bottom_cap.y, scene->cam.center.z - cylinder->bottom_cap.z);
    cylinder->color[0] = ft_atoi(scene->table[9]);
    cylinder->color[1] = ft_atoi(scene->table[10]);
    cylinder->color[2] = ft_atoi(scene->table[11]);
	printf("Cylinder Initialized: Type: %s, Center: %f | %f | %f, Orient: %f | %f | %f, Diameter: %f, Radius: %f, Height: %f, Color: (%u, %u, %u)\n", cylinder->type, cylinder->center.x, cylinder->center.y, cylinder->center.z, cylinder->orient.x, cylinder->orient.y, cylinder->orient.z, cylinder->diameter, cylinder->radius, cylinder->height, cylinder->color[0], cylinder->color[1], cylinder->color[2]);
	return (0);
}
