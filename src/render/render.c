/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:14:57 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/13 20:43:42 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	destroy_handler(t_scene *scene)
{
	printf ("X button pressed\n");
	free_all(scene);
	exit(0);
}

int	key_handler(int key, t_scene *scene)
{
	printf("----> key: %d\n", key);
	if (key == XK_Escape)
	{
		printf("----> ESC button pressed\n");
		free_all(scene);
		exit(1);
	}
	return (0);
}

void	events(t_scene *scene)
{
	if (scene->mrt.window == NULL)
	{
		printf("%s%s", ERROR, MLX_WIN_ERR);
		free_all(scene);
	}
	mlx_hook(scene->mrt.window, 2, 1L << 0, key_handler, scene);
	mlx_hook(scene->mrt.window, 17, 0L, destroy_handler, scene);
}

int	render_init(t_scene *scene)
{
	scene->mrt.connection = NULL;
	scene->mrt.window = NULL;
	scene->mrt.name = "mandatory";
	scene->mrt.connection = mlx_init();
	if (scene->mrt.connection == NULL)
		return (printf("%s%s", ERROR, MLX_INIT), 1);
	scene->mrt.window = mlx_new_window(scene->mrt.connection, WIDTH, HEIGHT,
			scene->mrt.name);
	if (scene->mrt.window == NULL)
		return (printf("%s%s", ERROR, MLX_WIN), 1);
	scene->mrt.img.img_ptr = mlx_new_image(scene->mrt.connection, WIDTH,
			HEIGHT);
	if (scene->mrt.img.img_ptr == NULL)
		return (printf("%s%s", ERROR, MLX_IMG), 1);
	scene->mrt.img.pxl_ptr = mlx_get_data_addr(scene->mrt.connection,
			&scene->mrt.img.bpp, &scene->mrt.img.line_len,
			&scene->mrt.img.endian);
//	events_init(scene->mrt);
	return (0);
}
