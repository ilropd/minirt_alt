/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:04:50 by irozhkov          #+#    #+#             */
/*   Updated: 2025/01/30 15:43:19 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

int	average_colors(int col1, int col2)
{
	int	r_avg;
	int	g_avg;
	int	b_avg;

	r_avg = (((col1 >> 16) & 0xFF) + ((col2 >> 16) & 0xFF)) / 2; 
	g_avg = (((col1 >> 8) & 0xFF) + ((col2 >> 8) & 0xFF)) / 2;
	b_avg = ((col1 & 0xFF) + (col2 & 0xFF)) / 2;
	return (r_avg << 16 | g_avg << 8 | b_avg);
}

int	rgb_to_int(unsigned int color[3])
{
    return ((color[0] << 16) | (color[1] << 8) | color[2]);
}
