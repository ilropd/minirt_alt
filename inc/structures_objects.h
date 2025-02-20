/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_objects.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:42:45 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/20 21:28:30 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_OBJECTS_H
# define STRUCTURES_OBJECTS_H

# include "structures_scene.h"
# include "type_id.h"

typedef struct s_sp_vars
{
	double	a;
	double	b;
	double	c;
	double	discr;
	double	dist1;
	double	dist2;
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

typedef struct s_cylinder
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

typedef struct s_cone
{
	char			*type;
	t_vector		vertex;    // Vértice (apex) del cono.
	t_vector		orient;    // Dirección del eje del cono (normalizada).
	t_vector		cam_cone;  // Para cálculos relativos a la cámara.
	double			angle;     // Ángulo de apertura del cono (en grados).
	double			height;    // Altura del cono.
	double			radius;    // Radio de la base (calculado a partir de height y angle).
	unsigned int	color[3];
}	t_cone;

typedef union u_obj
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cone		*co;
}	t_obj;

typedef struct s_item
{
	t_type_id		id;
	t_obj			type;
	void			(*update_cam)(t_scene *, t_item *);
	void			(*intersect)(t_scene *, t_item *, t_ray *);
	void			(*inside)(t_scene *, t_item *);
	double			(*shadows)(t_item *, t_ray *);
	void			(*free_obj)(t_obj *obj);
	struct s_item	*next;
}	t_item;

#endif
