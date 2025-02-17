# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/22 14:32:18 by irozhkov          #+#    #+#              #
#    Updated: 2025/02/17 21:36:39 by irozhkov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# ═══ COMPILACIÓN ═════════════════════════════════════════════════════════════#
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LIB_FLAG = -L./Libft -lft
MLX_FLAG = -L./minilibx-linux -lmlx -lX11 -lXext -lm -lz
DEP_FLAG = -MMD -MP
INCLUDE = -I./Libft/ -I./minilibx-linux/ -I./inc/
MKDIR = mkdir -p
RMF = rm -f
RMD = rm -rf

# ═══ DIRECTORIOS ════════════════════════════════════════════════════════════#
CHECK_DIR    = check/
COLORS_DIR   = colors/
GEOM_DIR     = geometry/
INC_DIR      = inc/
INIT_DIR     = init/
INTERSEC_DIR = intersections/
LIBFT_DIR    = Libft/
LIGHT_DIR    = light/
MLX_DIR      = minilibx-linux/
OBJ_DIR      = obj/
PARS_DIR     = parser/
REND_DIR     = render/
SRC_DIR      = src/
UTILS_DIR    = utils/

# ═══ FUENTES ══════════════════════════════════════════════════════════════#
MAIN         = main_alt
CHECK_FILES  = checker_ambient checker checker_camera checker_cylinder \
			   checker_plane checker_sphere checker_light check_limits
COLORS_FILES = colors
GEOM_FILES   = vector vector_math vector_math_dir vector_prod vector_set
INIT_FILES   = init_all init_figures init_unique set_figures
INTERSEC_FILES = intersections plane_intersection sphere_intersection \
				 cylinder_intersection cylinder_body cylinder_caps
LIGHT_FILES    = check_cam_inside check_light_inside light_calc shadow_calc
PARS_FILES     = parsing_gnl parsing_scene parsing_table
REND_FILES     = ray_tracing render
UTILS_FILES    = ft_atof utils_add utils_exit utils_free utils_parsing \
				 utils_str

SRC_FILES += $(MAIN)
SRC_FILES += $(addprefix $(CHECK_DIR),$(CHECK_FILES))
SRC_FILES += $(addprefix $(COLORS_DIR),$(COLORS_FILES))
SRC_FILES += $(addprefix $(GEOM_DIR),$(GEOM_FILES))
SRC_FILES += $(addprefix $(INIT_DIR),$(INIT_FILES))
SRC_FILES += $(addprefix $(INTERSEC_DIR),$(INTERSEC_FILES))
SRC_FILES += $(addprefix $(LIGHT_DIR),$(LIGHT_FILES))
SRC_FILES += $(addprefix $(PARS_DIR),$(PARS_FILES))
SRC_FILES += $(addprefix $(REND_DIR),$(REND_FILES))
SRC_FILES += $(addprefix $(UTILS_DIR),$(UTILS_FILES))

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

# ═══ REGLAS ════════════════════════════════════════════════════════════════════#

all: $(LIBFT_DIR)libft.a $(MLX_DIR)libmlx.a $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)libft.a $(MLX_DIR)libmlx.a Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAG) $(MLX_FLAG) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(DEP_FLAG) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(LIBFT_DIR)libft.a:
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX_DIR)libmlx.a:
	-$(MAKE) -C $(MLX_DIR) all CFLAGS="-O3 -w -I/usr/include" > /dev/null 2>&1

clean:
	$(RMD) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	$(RMF) $(NAME)
	$(RMF) $(LIBFT_DIR)libft.a
	$(RMF) $(MLX_DIR)libmlx.a
	$(RMF) $(MLX_DIR)libmlx_Linux.a

re: fclean all

-include $(DEPS)
.PHONY: all clean fclean re
