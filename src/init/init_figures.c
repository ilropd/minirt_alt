/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:10:33 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/17 18:05:39 by jpancorb         ###   ########.fr       */
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
	vector_set_table(&sphere->center, scene, 1);
	vector_set_vparam(&sphere->cam_sphere, SUB,
		&scene->cam.center, &sphere->center);
	sphere->diameter = ft_atof(scene->table[4]);
	sphere->radius = sphere->diameter / 2;
	set_color(scene, &sphere->color, 5);
	printf("Sphere Initialized: Type: %s, Center: %f | %f | %f, Diameter: %f,"
		" Radius: %f, Color: (%u, %u, %u)\n", sphere->type, sphere->center.x,
		sphere->center.y, sphere->center.z, sphere->diameter, sphere->radius,
		sphere->color[0], sphere->color[1], sphere->color[2]);
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
	vector_set_table(&plane->center, scene, 1);
	vector_set(&plane->orient, ft_atof(scene->table[4]),
		ft_atof(scene->table[5]), ft_atof(scene->table[6]));
	vector_set_vparam(&plane->cam_plane, SUB, &scene->cam.center,
		&plane->center);
	set_color(scene, &plane->color, 7);
	printf("Plane Initialized: Type: %s, Center: %f | %f | %f, Orient:"
		" %f | %f | %f, Color: (%u, %u, %u)\n", plane->type, plane->center.x,
		plane->center.y, plane->center.z, plane->orient.x, plane->orient.y,
		plane->orient.z, plane->color[0], plane->color[1], plane->color[2]);
	return (0);
}

static void	find_cy_caps(t_cylinder *cy)
{
	t_vector	orient_mult;
	t_vector	top;

	orient_mult = vector_mult_dir(&cy->orient, cy->height);
	top = vector_add_dir(&cy->center, &orient_mult);
	vector_set(&cy->top_cap, top.x, top.y, top.z);
	vector_set(&cy->bottom_cap, cy->center.x, cy->center.y, cy->center.z);
}

static void	print_cyllinder_init(t_cylinder *cylinder)
{
	printf("Cylinder Initialized: Type: %s, Center: %f | %f | %f,"
		" Orient: %f | %f | %f, Diameter: %f, Radius: %f, Height: %f,"
		" Color: (%u, %u, %u)\n", cylinder->type, cylinder->center.x,
		cylinder->center.y, cylinder->center.z, cylinder->orient.x,
		cylinder->orient.y, cylinder->orient.z, cylinder->diameter,
		cylinder->radius, cylinder->height, cylinder->color[0],
		cylinder->color[1], cylinder->color[2]);
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
	vector_set_table(&cylinder->center, scene, 1);
	vector_set_table(&cylinder->orient, scene, 4);
	cylinder->diameter = ft_atof(scene->table[7]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atof(scene->table[8]);
	find_cy_caps(cylinder);
	vector_set_vparam(&cylinder->cam_cylinder, SUB, &scene->cam.center,
		&cylinder->bottom_cap);
	set_color(scene, &cylinder->color, 9);
	print_cyllinder_init(cylinder);
	return (0);
}
