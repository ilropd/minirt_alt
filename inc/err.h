/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:13:20 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/26 16:57:18 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "minirt.h"

# define ERROR "\033[1;31mError\n\033[0m"
# define WARN "\033[1;33mWarning\n\033[0m"

/* Errors of file checking*/ 
# define FILE_NE "File doesn't exist\n"
# define FILE_E "File is empty\n"
# define FILE_RET "Cannot retrieve file information\n"
# define FILE_RO "Can't open or read file\n"
# define FILE_WF "Incorrect format of the file\n"

/* Errors of parsing */
# define ARGS "Wrong number of parameters\n"
# define TBL_ERR "Creation of parsing table failed\n"

/* Errors of scene creation */
# define ARGS_SC "Wrong scene arguments\n"
# define ARGS_WAMB "Wrong ambient light arguments\n"
# define ARGS_WCAM "Wrong camera arguments\n"
# define ARGS_WLIG "Wrong light arguments\n"
# define ARGS_NUNIQUE_A "Ambient light is not unique\n"
# define ARGS_NUNIQUE_C "Camera is not unique\n"
# define ARGS_NUNIQUE_L "Light is not unique\n"

/* Errors of memory allocation */
# define MEM "Memory allocation failed\n"
# define MEM_AMB "Memory allocation for ambient light failed\n"
# define MEM_CAM "Memory allocation for camera failed\n"
# define MEM_LIG "Memory allocation for light failed\n"
# define MEM_SP "Memory allocation for sphere failed\n"
# define MEM_PL "Memory allocation for plane failed\n"
# define MEM_CY "Memory allocation for cylinder failed\n"

#endif
