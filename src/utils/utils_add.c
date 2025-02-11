/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:51:47 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/26 15:38:56 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_item	*add_last_obj(t_item *objs)
{
	if (!objs)
		return (objs);
	while (objs->next != NULL)
		objs = objs->next;
	return (objs);
}

t_item	*add_obj(t_item *objs, t_scene *scene)
{
	t_item	*result;

	result = ft_calloc(1, sizeof(t_item));
	if (!result)
		error_exit(scene);
	result->next = NULL;
	if (!objs)
		scene->objs = result;
	else
		add_last_obj(objs)->next = result;
	return (result);
}
