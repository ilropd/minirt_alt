/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:09:38 by jpancorb          #+#    #+#             */
/*   Updated: 2025/02/25 21:45:55 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"

static void	get_cone_normal(t_ray *ray, t_cone *cone, double dist)
{
	t_vector	hit_point;
	t_vector	m;
	t_vector	grad;
	double		theta;
	double		cos2;
	double		m_dot_A;

	vector_set(&hit_point,
		ray->ray_orgn.x + ray->v_ray.x * dist,
		ray->ray_orgn.y + ray->v_ray.y * dist,
		ray->ray_orgn.z + ray->v_ray.z * dist);
	vector_set(&ray->hit_p, hit_point.x, hit_point.y, hit_point.z);
	m = vector_sub_dir(&hit_point, &cone->vertex);
	theta = cone->angle * M_PI / 180.0;
	cos2 = cos(theta) * cos(theta);
	m_dot_A = vector_dot_prod(&m, &cone->orient);
	grad.x = 2 * m_dot_A * cone->orient.x - 2 * cos2 * m.x;
	grad.y = 2 * m_dot_A * cone->orient.y - 2 * cos2 * m.y;
	grad.z = 2 * m_dot_A * cone->orient.z - 2 * cos2 * m.z;
	vector_normalize(&grad);
	ray->normal = grad;
}

static void	get_cone_cap_normal(t_ray *ray, t_cone *cone)
{
	vector_set_sparam(&ray->normal, MULT, &cone->orient, -1);
}

void	cone_intersection(t_scene *scene, t_item *item, t_ray *ray)
{
	t_cone	*cone;
	double	t_side;
	double	t_cap;
	double	discr;
	double	a;
	double	b;
	double	c;
	t_vector	m;
	double	theta;
	double	cos2;
	double	d_dot_A;
	double	m_dot_A;
	t_vector	base_center;
	double	denom;
	double	t1, t2;
	double	t_final;
	t_vector	temp;
	t_vector 	tmp;

	cone = item->type.co;
	t_side = MAXFLOAT;
	t_cap = MAXFLOAT;
	m = vector_sub_dir(&ray->ray_orgn, &cone->vertex);
	theta = cone->angle * M_PI / 180.0;
	cos2 = cos(theta) * cos(theta);
	d_dot_A = vector_dot_prod(&ray->v_ray, &cone->orient);
	m_dot_A = vector_dot_prod(&m, &cone->orient);
	a = vector_dot_prod(&ray->v_ray, &ray->v_ray) - cos2 * (d_dot_A * d_dot_A);
	b = 2 * ( vector_dot_prod(&ray->v_ray, &m) - cos2 * d_dot_A * m_dot_A );
	c = vector_dot_prod(&m, &m) - cos2 * (m_dot_A * m_dot_A);
	discr = b * b - 4 * a * c;
	if (discr >= 0 && fabs(a) > 1e-6)
	{
		double sqrt_discr = sqrtf(discr);
		t1 = (-b - sqrt_discr) / (2 * a);
		t2 = (-b + sqrt_discr) / (2 * a);
		if (t1 > 0)
			t_side = t1;
		if (t2 > 0 && t2 < t_side)
			t_side = t2;
		tmp = vector_mult_dir(&ray->v_ray, t_side);
		temp = vector_add_dir(&ray->ray_orgn, &tmp);			
		t_vector v_to_hit = vector_sub_dir(&temp, &cone->vertex);
		double proj = vector_dot_prod(&v_to_hit, &cone->orient);
		if (proj < 0 || proj > cone->height)
			t_side = MAXFLOAT;
	}
	tmp = vector_mult_dir(&cone->orient, cone->height);
	base_center = vector_add_dir(&cone->vertex, &tmp);
	t_vector cap_normal = { -cone->orient.x, -cone->orient.y, -cone->orient.z };
	denom = vector_dot_prod(&ray->v_ray, &cap_normal);
	if (fabs(denom) > 1e-6)
	{
		t_cap = (vector_dot_prod(&base_center, &cap_normal)
				- vector_dot_prod(&ray->ray_orgn, &cap_normal)) / denom;
		if (t_cap > 0)
		{
			tmp = vector_mult_dir(&ray->v_ray, t_cap);
			temp = vector_add_dir(&ray->ray_orgn, &tmp);
			t_vector diff = vector_sub_dir(&temp, &base_center);
			if (vector_len(&diff) > cone->radius)
				t_cap = MAXFLOAT;
		}
	}
	t_final = fmin(t_side, t_cap);
	if (t_final < MAXFLOAT)
	{
		ray->hit = 1;
		if (t_final == t_side)
		{
			ray->cap_hit = 0;
			get_cone_normal(ray, cone, t_final);
		}
		else
		{
			ray->cap_hit = 1;
			tmp = vector_mult_dir(&ray->v_ray, t_final);
			temp = vector_add_dir(&ray->ray_orgn, &tmp);
			vector_set(&ray->hit_p, temp.x, temp.y, temp.z);
			get_cone_cap_normal(ray, cone);
		}
		int color = light_calc(scene, ray, cone->color);
		check_ray(ray, color, t_final, CO);
	}
}

double	cone_sh_intersection(t_item *item, t_ray *ray)
{
	t_cone	*cone;
	double	t_side;
	double	t_cap;
	double	discr;
	double	a, b, c;
	t_vector	m;
	double	d_dot_A, m_dot_A;
	double	theta, cos2;
	double	t1, t2, t_final;
	t_vector	temp;
	t_vector	v_to_hit;
	t_vector	base_center;
	t_vector	cap_normal;
	double	denom;
	t_vector 	tmp;


	cone = item->type.co;
	t_side = MAXFLOAT;
	t_cap = MAXFLOAT;
	m = vector_sub_dir(&ray->ray_orgn, &cone->vertex);
	theta = cone->angle * M_PI / 180.0;
	cos2 = cos(theta) * cos(theta);
	d_dot_A = vector_dot_prod(&ray->v_ray, &cone->orient);
	m_dot_A = vector_dot_prod(&m, &cone->orient);
	a = vector_dot_prod(&ray->v_ray, &ray->v_ray) - cos2 * (d_dot_A * d_dot_A);
	b = 2 * (vector_dot_prod(&ray->v_ray, &m) - cos2 * d_dot_A * m_dot_A);
	c = vector_dot_prod(&m, &m) - cos2 * (m_dot_A * m_dot_A);
	discr = b * b - 4 * a * c;
	if (discr >= 0 && fabs(a) > 1e-6)
	{
		double sqrt_discr = sqrtf(discr);
		t1 = (-b - sqrt_discr) / (2 * a);
		t2 = (-b + sqrt_discr) / (2 * a);
		if (t1 > 0)
			t_side = t1;
		if (t2 > 0 && t2 < t_side)
			t_side = t2;
		tmp = vector_mult_dir(&ray->v_ray, t_side);
		temp = vector_add_dir(&ray->ray_orgn, &tmp);
		v_to_hit = vector_sub_dir(&temp, &cone->vertex);
		double proj = vector_dot_prod(&v_to_hit, &cone->orient);
		if (proj < 0 || proj > cone->height)
			t_side = MAXFLOAT;
	}
	tmp = vector_mult_dir(&cone->orient, cone->height);
	base_center = vector_add_dir(&cone->vertex, &tmp);
	cap_normal = (t_vector){ -cone->orient.x, -cone->orient.y, -cone->orient.z };
	denom = vector_dot_prod(&ray->v_ray, &cap_normal);
	if (fabs(denom) > 1e-6)
	{
		t_cap = (vector_dot_prod(&base_center, &cap_normal)
				- vector_dot_prod(&ray->ray_orgn, &cap_normal)) / denom;
		if (t_cap > 0)
		{
			tmp = vector_mult_dir(&ray->v_ray, t_cap);
			temp = vector_add_dir(&ray->ray_orgn, &tmp);
			t_vector diff = vector_sub_dir(&temp, &base_center);
			if (vector_len(&diff) > cone->radius)
				t_cap = MAXFLOAT;
		}
	}
	t_final = fmin(t_side, t_cap);
	return (t_final);
}
