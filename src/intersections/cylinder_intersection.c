/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 20:14:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"

static void	cy_caps(t_cylinder *cy, t_ray *ray, double *d_caps)
{
	double		denom;
	double		dist_bottom;
	double		dist_top;
	double		dist_to_center;
	t_vector	*point;
	t_vector	*temp;

	denom = vector_dot_prod(&ray->v_ray, &cy->orient);
	if (fabs(denom) > 1e-6)
	{
		temp = vector_sub(&cy->bottom_cap, &ray->ray_orgn);
		dist_bottom = vector_dot_prod(temp, &cy->orient) / denom;
		free(temp);
		if (dist_bottom > 0)
		{
			temp = vector_mult(&ray->v_ray, dist_bottom);
			point = vector_add(&ray->ray_orgn, temp);
			free(temp);
			temp = vector_sub(&cy->bottom_cap, point);
			dist_to_center = vector_len(temp);
			free(temp);
			if (dist_to_center <= cy->radius)
			{
				ray->cap_hit = -1;
				*d_caps = dist_bottom;
			}
			free(point);
		}
		temp = vector_sub(&cy->top_cap, &ray->ray_orgn);
		dist_top = vector_dot_prod(temp, &cy->orient) / denom;
		free(temp);
		if (dist_top > 0)
		{
			temp = vector_mult(&ray->v_ray, dist_top);
			point = vector_add(&ray->ray_orgn, temp);
			free(temp);
			temp = vector_sub(&cy->top_cap, point);
			dist_to_center = vector_len(temp);
			free(temp);
			if (dist_to_center <= cy->radius && dist_top < *d_caps)
			{
				ray->cap_hit = 1;
				*d_caps = dist_top;
			}
			free(point);
		}
	}
}

static int	cy_limit(t_cylinder *cylinder, t_ray *ray, double dist)
{
	t_vector	*point;
	t_vector	*temp;
	double		h;

	temp = vector_mult(&ray->v_ray, dist);
	point = vector_add(&ray->ray_orgn, temp);
	free(temp);
	temp = vector_sub(point, &cylinder->bottom_cap);
	h = vector_dot_prod(temp, &cylinder->orient);
	free(temp);
	free(point);
	return (h >= 0 && h <= cylinder->height);
}

static float	cy_body(t_cylinder *cy, t_ray *ray)
{
	t_sp_vars	var;
	float		dist_min_body;

	dist_min_body = MAXFLOAT;
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray)
		- pow(vector_dot_prod(&ray->v_ray, &cy->orient), 2);
	var.b = 2 * (vector_dot_prod(&ray->v_ray, &cy->cam_cylinder)
			- (vector_dot_prod(&ray->v_ray, &cy->orient)
				* vector_dot_prod(&cy->cam_cylinder, &cy->orient)));
	var.c = vector_dot_prod(&cy->cam_cylinder, &cy->cam_cylinder)
		- pow(vector_dot_prod(&cy->cam_cylinder, &cy->orient), 2)
		- pow(cy->radius, 2);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 && cy_limit(cy, ray, var.dist1))
			dist_min_body = var.dist1;
		if (var.dist2 > 0 && cy_limit(cy, ray, var.dist2))
			dist_min_body = fmin(var.dist1, var.dist2);
	}
	return (dist_min_body);
}

static void get_cy_normal(t_ray *ray, t_cylinder *cy, double dist)
{
    t_vector    *hit_point;
    t_vector    *axis_point;
    t_vector    *temp;
    double      dl;

	vector_set(&ray->hit_p, ray->ray_orgn.x + ray->v_ray.x * dist,
			ray->ray_orgn.y + ray->v_ray.y * dist,
			ray->ray_orgn.z + ray->v_ray.z * dist);
	if (ray->cap_hit == 0)
    {
        hit_point = vector_sub(&ray->hit_p, &cy->bottom_cap);
		dl = vector_dot_prod(hit_point, &cy->orient);
		free(hit_point);
        temp = vector_mult(&cy->orient, dl);
		axis_point = vector_add(&cy->bottom_cap, temp);
        free(temp);
		vector_set(&ray->normal, ray->hit_p.x - axis_point->x,
				ray->hit_p.y - axis_point->y,
				ray->hit_p.z - axis_point->z);
		vector_normalize(&ray->normal);
        free(axis_point);
    }
    else
	{
		vector_set(&ray->normal, cy->orient.x * ray->cap_hit,
				cy->orient.y * ray->cap_hit,
				cy->orient.z * ray->cap_hit);
	}
}

void	cylinder_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	double		d_body;
	double		d_caps;
	int			color;

	cylinder = item->type.cy;
	d_body = cy_body(cylinder, ray);
	d_caps = MAXFLOAT;
	cy_caps(cylinder, ray, &d_caps);
	if (d_body < MAXFLOAT || d_caps < MAXFLOAT)
	{
		if (d_body < d_caps)
		{
			ray->cap_hit = 0;
			get_cy_normal(ray, cylinder, d_body);
		}
		else
			get_cy_normal(ray, cylinder, d_caps);
		ray->hit = 1;
		color = light_calc(scene, ray, cylinder->color);
        check_ray(ray, color, fmin(d_body, d_caps), CY);
	}
}
