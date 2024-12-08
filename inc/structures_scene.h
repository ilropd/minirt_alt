/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_scene.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:30:05 by irozhkov          #+#    #+#             */
/*   Updated: 2024/12/07 18:00:31 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_SCENE_H
# define STRUCTURES_SCENE_H

# include "structures_objects.h"

typedef union	u_obj	t_obj;
typedef struct  s_item	t_item;

/* define size of rendering window */

# define WIDTH 600
# define HEIGHT 600
# define CORNER_THRESHOLD 20

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
}	t_cam;

/* Ambient light */
typedef struct s_amb
{
	char			*type;
	float			ratio;
	unsigned int	color[3];
}	t_amb;

/* Spot light */
typedef struct	s_light
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
