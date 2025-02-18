/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_alt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:34:41 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 16:17:06 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	file_checker(char **argv)
{
	struct stat	st;
	int			fd;

	if (access(argv[1], F_OK) != 0)
	{
		printf("%s%s", ERROR, FILE_NE);
		exit(1);
	}
	if (stat(argv[1], &st) != 0)
	{
		printf("%s%s", ERROR, FILE_RET);
		exit(1);
	}
	if (st.st_size == 0)
	{
		printf("%s%s", ERROR, FILE_E);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("%s%s", ERROR, FILE_RO);
		exit(1);
	}
	close(fd);
}

static void	arg_checker(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("%s%s", ERROR, ARGS);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (len <= 3 || ft_strcmp(argv[1] + len - 3, ".rt"))
	{
		printf("%s%s", ERROR, FILE_WF);
		exit(1);
	}
}

static void	init_scene(t_scene *scene)
{
	scene->table = parsing_table();
	if (!scene->table)
	{
		printf("%s%s", ERROR, TBL_ERR);
		free_all(scene);
		exit(1);
	}
	scene->objs = NULL;
}

int	main(int argc, char **argv)
{
	static t_scene	scene;

	arg_checker(argc, argv);
	file_checker(argv);
	init_scene(&scene);
	if (parsing_scene(argv, &scene))
		error_exit(&scene);
	render_init(&scene);
	ray_tracing(&scene);
	events(&scene);
	mlx_loop(scene.mrt.connection);
	return (0);
}
