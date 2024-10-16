CC= cc
CFLAGS= -Wall -Wextra -Werror
RM = rm -rf
MLX_FLAGS = ../MLX42/build/libmlx42.a ../MLX42/build/libglfw3.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit
NAME = graphic


all : $(NAME)

$(NAME) : graphic.c
	$(CC) $(CFLAGS) $(MLX_FLAGS) graphic.c  -o $(NAME)
%.o:%c
	$(CC) -c $(CFLAGS) -Imlx $< -o $@

# clean:
# 	@echo "make clean..."
# 	@$(MAKE) clean -C ./libft
# 	@$(MAKE) clean -C ./ft_printf
# 	@$(MAKE) clean -C ./get_next_line

# fclean:
# 	@echo "make fclean..."
# 	@$(MAKE) fclean -C ./libft
# 	@$(MAKE) fclean -C ./ft_printf
# 	@$(MAKE) fclean -C ./get_next_line
# 	@${RM} $(NAME1) $(SO_LONGO) $(UTILSO)
# 	@${RM} $(NAME2) $(SO_LONGO_BONUS) $(UTILSO_BONUS)
# re: fclean all
