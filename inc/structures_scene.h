/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_scene.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:30:05 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/19 15:28:14 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_SCENE_H
# define STRUCTURES_SCENE_H

# include "structures_objects.h"
# include "type_id.h"

typedef union u_obj		t_obj;
typedef struct s_item	t_item;

/* define size of rendering window */

# define WIDTH 600
# define HEIGHT 600

# define DEFAULT_COLOR 0

/* define values for calculation */

# define MAXFLOAT 3.402823466e+38F
# define BIAS 1e-6
# define PL_BIAS 1e-2
# define SPEC	1

/* VECTOR STRUCTURES */

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_viewport
{
	float	width;
	float	height;
	float	x_pixel;
	float	y_pixel;
}	t_viewport;

typedef struct s_ray
{
	t_vector	v_ray;
	t_vector	ray_orgn;
	t_vector	normal;
	t_vector	hit_p;
	t_type_id	id;
	double		ray_x;
	double		ray_y;
	double		cap_hit;
	int			hit;
	int			dot_color;
	int			is_shadow;
	double		dist_curr;
}	t_ray;

/* STRUCTURES FOR MLX AND RENDERING */

typedef struct s_img
{
	void	*img_ptr;
	char	*pxl_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_mrt
{
	char			*name;
	void			*connection;
	void			*window;
	int				corner_type;
	int				is_resizing;
	unsigned int	color;
	double			angle_x;
	double			angle_y;
	t_img			img;
}	t_mrt;

/* MANDATORY SCENE ELEMENTS */

/* Camera */
typedef struct s_cam
{
	char			*type;
	t_vector		center;
	t_vector		orient;
	unsigned int	fov;
	float			fov_rad;
	int				is_inside;
}	t_cam;

/* Ambient light */
typedef struct s_amb
{
	char			*type;
	float			ratio;
	unsigned int	color[3];
}	t_amb;

/* Spot light */
typedef struct s_light
{
	char			*type;
	float			brightness;
	unsigned int	color[3];
	t_vector		center;
	struct s_light	*next;
}	t_light;

/* MAIN STRUCTURE FOR ALL THE SCENE */

typedef struct s_scene
{
	char	**table;
	t_mrt	mrt;
	t_amb	amb;
	t_light	light;
	t_cam	cam;
	t_item	*objs;
}	t_scene;

#endif
