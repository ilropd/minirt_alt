/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_objects.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:42:45 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/08 19:07:54 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_OBJECTS_H
# define STRUCTURES_OBJECTS_H

# include "structures_scene.h"
# include "type_id.h"

typedef struct s_sp_vars
{
	float	a;
	float	b;
	float	c;
	float	discr;
	float	dist1;
	float	dist2;
}	t_sp_vars;

typedef struct s_sphere
{
	char			*type;
	t_vector		center;
	t_vector		cam_sphere;
	double			diameter;
	double			radius;
	unsigned int	color[3];
}	t_sphere;

typedef struct s_plane
{
	char			*type;
	t_vector		center;
	t_vector		orient;
	t_vector		cam_plane;
	unsigned int	color[3];
}	t_plane;

typedef struct	s_cylinder
{
	char			*type;
	t_vector		center;
	t_vector		orient;
	t_vector		top_cap;
	t_vector		bottom_cap;
	t_vector		cam_cylinder;
	double			diameter;
	double			radius;
	double			height;
	unsigned int	color[3];
}	t_cylinder;


typedef union	u_obj
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
}	t_obj;

typedef struct	s_item
{
	t_type_id		id;
	t_obj			type;
//	void			(*intersect)(t_obj *, t_ray *, t_item *);
	void			(*intersect)(t_scene *, t_item *, t_ray *);
	int				(*shadows)(t_item *, t_ray *);
//	void			(*trans)(t_obj *obj, t_sc *sc);
	void			(*free_obj)(t_obj *obj);
//	void			(*get_norm)(t_obj *, t_hit *, t_ray *);
	struct s_item	*next;
}	t_item;

#endif
