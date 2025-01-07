NAME = cub3D

CC = cc

MODE        ?= RELEASE

# Compilation Flags based on MODE
ifeq ($(MODE), DEBUG)
    FLAGS    := -Wall -Wextra -Werror -g
else ifeq ($(MODE), RELEASE)
    FLAGS    := -Wall -Wextra -Werror -Ofast -flto
else
    FLAGS    := -Wall -Wextra -Werror -Ofast -flto
endif

SRC_DIR = src
HEADER = cub3D.h
MLX42_DIR = MLX42
LIBFT_DIR = LIBFT

BUILD_DIR = build

LIBFT = $(LIBFT_DIR)/libft.a
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a
LIBS = $(MLX42_LIB) -ldl -lglfw -pthread -lm

SRCS = \
	src/check_data.c \
	src/check_map_utils.c \
	src/check_map.c \
	src/main.c \
	src/move.c \
	src/ray_vector.c \
	src/raycasting_loop.c \
	src/text_choose.c \
	src/utils.c \
	src/validation_utils.c \

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(BUILD_DIR) $(LIBFT) $(MLX42_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(OBJS) $(FLAGS) -o $(BUILD_DIR)/$(NAME) $(LIBFT) $(LIBS)
	rm -f $(OBJS)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) -I./MLX42/include/MLX42 -c $< -o $@

$(MLX42_LIB):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@make -C $(MLX42_DIR)/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR)/%.o

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)

re: fclean all

# test: all
# 	./$(NAME)


.PHONY: all clean fclean re