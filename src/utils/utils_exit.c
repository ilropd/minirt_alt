/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:24:12 by irozhkov          #+#    #+#             */
/*   Updated: 2025/02/18 19:19:58 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	error_exit(t_scene *scene)
{
	free_all(scene);
	exit(1);
}

void	error_exit_print(char *str)
{
	printf("%s%s", ERROR, str);
	exit(1);
}
