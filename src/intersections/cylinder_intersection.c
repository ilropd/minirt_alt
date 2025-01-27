/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:23:56 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/25 19:07:03 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"

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

/*static float	cy_body(t_cylinder *cylinder, t_ray *ray);
static void	cy_caps(t_cylinder *cylinder, t_ray *ray, float d_caps);

void	cylinder_intersection(t_item *item, t_ray *ray)
{
	t_cylinder	*cylinder;
	float		dist_min;
	float		d_body;
	float		d_caps[2];
	int			color;


	cylinder = item->type.cy;
	d_body = cy_body(cylinder, ray);
	cy_caps(cylinder, ray, d_caps);

	dist_min = cy_closest(d_body, d_caps);
	if (dist_min < MAXFLOAT)
	{
		color = (cylinder->color[0] << 16) | (cylinder->color[1] << 8) | cylinder->color[2];
		check_ray(ray, color, dist_min);
	}
}

static int	cy_limit(t_cylinder *cylinder, t_ray *ray, float dist)
{
	t_vector	point;
	float		h;

	point = vector_add_dir(&ray->ray_orgn, vector_mult_dir(&ray->v_ray, dist));
	h = vector_dot_prod(vector_sub_dir(&point, &cylinder->center), cylinder->orient);
	return (h >= 0 && h <= cylinder->height);
}

static void	cy_caps(t_cylinder *cylinder, t_ray *ray, float d_caps)
{
    t_vector cap_centers[2] = {
        cylinder->center,
        vector_add(cylinder->center, vector_scale(cylinder->orient, cylinder->height))
    };

    for (int i = 0; i < 2; i++)
    {
        double denom = vector_dot_prod(ray->v_ray, cylinder->orient);
        t_caps[i] = MAXFLOAT;
        if (fabs(denom) > 1e-6) // Not parallel
        {
            double t = vector_dot_prod(vector_sub(cap_centers[i], ray->origin), cylinder->orient) / denom;
            if (t > 0)
            {
                t_vector point = vector_add(ray->origin, vector_scale(ray->v_ray, t));
                double dist_to_center = vector_length(vector_sub(point, cap_centers[i]));
                if (dist_to_center <= cylinder->radius)
                    t_caps[i] = t;
            }
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
}*/
