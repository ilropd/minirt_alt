/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:02:38 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 16:13:48 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

int	open_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nProblem with fd\n");
		return (-1);
	}
	return (fd);
}

int	process_line(char *str, t_scene *scene)
{
	clear_parsing_table(scene->table);
	if (ft_empty_or_whitespaces(str))
		return (0);
	if (parse_string(scene->table, str))
	{
		printf("Error\nParsing failed\n");
		return (1);
	}
	if (init_all(scene))
	{
		printf("Error\nObject initialization failed\n");
		return (1);
	}
	return (0);
}

int	handle_error_cleanup(char *str, int fd, int line)
{
	if (str)
		free(str);
	close(fd);
	return (printf("Error\nLine %d failed\n", line), 1);
}

int	parsing_scene(char **argv, t_scene *scene)
{
	int		fd;
	int		line;
	char	*str;

	line = 1;
	str = NULL;
	fd = open_file(argv);
	if (fd == -1)
		return (1);
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (process_line(str, scene))
			return (handle_error_cleanup(str, fd, line));
		free(str);
		str = get_next_line(fd);
		line++;
	}
	update_cam_vectors(scene);
	close(fd);
	return (0);
}
