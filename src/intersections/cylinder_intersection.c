/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/29 16:23:59 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"
/*
void	cylinder_intersection(t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	t_sp_vars	var;
	int			color;

	cylinder = item->type.cy;
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray) - pow(vector_dot_prod(&ray->v_ray, &cylinder->orient), 2);
	var.b = 2 * (vector_dot_prod(&ray->v_ray, &cylinder->cam_cylinder) - (vector_dot_prod(&ray->v_ray, &cylinder->orient) * vector_dot_prod(&cylinder->cam_cylinder, &cylinder->orient)));
	var.c = vector_dot_prod(&cylinder->cam_cylinder, &cylinder->cam_cylinder) - pow(vector_dot_prod(&cylinder->cam_cylinder, &cylinder->orient), 2) - pow(cylinder->radius, 2);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 || var.dist2 > 0)
        {
			color = (cylinder->color[0] << 16) | (cylinder->color[1] << 8) | cylinder->color[2];
			if (var.dist1 <= var.dist2)
				check_ray(ray, color, var.dist1);
			else
				check_ray(ray, color, var.dist2);
		}
	}
}
*/
static float	cy_body(t_cylinder *cylinder, t_ray *ray);
static void	cy_caps(t_cylinder *cylinder, t_ray *ray, double *d_caps);

void	cylinder_intersection(t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	double		dist_min;
	double		d_body;
	double		d_caps;
	int			color;

	cylinder = item->type.cy;
	d_body = cy_body(cylinder, ray);
	d_caps = MAXFLOAT;
	cy_caps(cylinder, ray, &d_caps);
	dist_min = fmin(d_body, d_caps);
	if (dist_min < MAXFLOAT)
	{
		color = (cylinder->color[0] << 16) | (cylinder->color[1] << 8) | cylinder->color[2];
		check_ray(ray, color, dist_min);
	}
}

static int	cy_limit(t_cylinder *cylinder, t_ray *ray, double dist)
{
	t_vector	point;
	double		h;

	point = *vector_add(&ray->ray_orgn, vector_mult(&ray->v_ray, dist));
	h = vector_dot_prod(vector_sub(&point, &cylinder->bottom_cap), &cylinder->orient);
	return (h >= 0 && h <= cylinder->height);
}

static void cy_caps(t_cylinder *cylinder, t_ray *ray, double *d_caps)
{
    double      denom;
    double      dist_bottom;
    double      dist_top;
    double      dist_to_center;
    t_vector    point;

    denom = vector_dot_prod(&ray->v_ray, &cylinder->orient);

    if (fabs(denom) > 1e-6)
    {
        dist_bottom = vector_dot_prod(vector_sub(&cylinder->bottom_cap, &ray->ray_orgn), &cylinder->orient) / denom;
        if (dist_bottom > 0)
        {
            point = *vector_add(&ray->ray_orgn, vector_mult(&ray->v_ray, dist_bottom));
            dist_to_center = vector_len(vector_sub(&cylinder->bottom_cap, &point));
            if (dist_to_center <= cylinder->radius)
                *d_caps = dist_bottom;
        }
        dist_top = vector_dot_prod(vector_sub(&cylinder->top_cap, &ray->ray_orgn), &cylinder->orient) / denom;
        if (dist_top > 0)
        {
            point = *vector_add(&ray->ray_orgn, vector_mult(&ray->v_ray, dist_top));
            dist_to_center = vector_len(vector_sub(&cylinder->top_cap, &point));
            if (dist_to_center <= cylinder->radius && dist_top < *d_caps)
                *d_caps = dist_top;
        }
    }
}

static float	cy_body(t_cylinder *cylinder, t_ray *ray)
{
	t_sp_vars	var;
	float		dist_min_body;

	dist_min_body = MAXFLOAT;
	var.a = vector_dot_prod(&ray->v_ray, &ray->v_ray) - pow(vector_dot_prod(&ray->v_ray, &cylinder->orient), 2);
	var.b = 2 * (vector_dot_prod(&ray->v_ray, &cylinder->cam_cylinder) - (vector_dot_prod(&ray->v_ray, &cylinder->orient) * vector_dot_prod(&cylinder->cam_cylinder, &cylinder->orient)));
	var.c = vector_dot_prod(&cylinder->cam_cylinder, &cylinder->cam_cylinder) - pow(vector_dot_prod(&cylinder->cam_cylinder, &cylinder->orient), 2) - pow(cylinder->radius, 2);
	var.discr = (var.b * var.b) - (4 * var.a * var.c);
	if (var.discr > 0)
	{
		var.dist1 = (-var.b + sqrtf(var.discr)) / (2 * var.a);
		var.dist2 = (-var.b - sqrtf(var.discr)) / (2 * var.a);
		if (var.dist1 > 0 && cy_limit(cylinder, ray, var.dist1))
			dist_min_body = var.dist1;
		if (var.dist2 > 0 && cy_limit(cylinder, ray, var.dist2))
			dist_min_body = fmin(var.dist1, var.dist2);
	}
	return (dist_min_body);
}
