/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:03:10 by jpancorb          #+#    #+#             */
/*   Updated: 2025/02/20 21:04:43 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

int	check_cone(char **table)
{
	int	result;

	result = 0;
	result += arg_counter(table);
	result += check_digit_cycle(table, 'f', 1, 8);
	result += check_digit_cycle(table, 'd', 9, 3);
	result += check_vector_limit(table, 4, 3);
	result += check_zerof_limit(table, 7, 2);
	result += check_rgb_limit(table, 9, 3);
	return (result);
}
