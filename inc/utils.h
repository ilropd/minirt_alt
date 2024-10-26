/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irozhkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:23:21 by irozhkov          #+#    #+#             */
/*   Updated: 2024/10/26 16:41:12 by irozhkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

/* ft_atof.c */
float			ft_atof(char *str);

/* utils_add.c */
t_item			*add_last_obj(t_item *objs);
t_item			*add_obj(t_item *objs, t_scene *scene);

/* utils_exit.c */
void			error_exit(t_scene *scene);

/* utils_free.c */
void			free_all(t_scene *scene);
void			free_sphere(t_obj *obj);
void			free_plane(t_obj *obj);
void			free_cylinder(t_obj *obj);

/* utils_parsing.c */
unsigned int	parse_int(char **str);
float			parse_float(char **str);
int				ft_isspace(char c);
char			*skip_whitespace(char *str);

/* utils_str.c */
int				ft_strcmp(const char *str1, const char *str2);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_empty_or_whitespaces(const char *str);

#endif
