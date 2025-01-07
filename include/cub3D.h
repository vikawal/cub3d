/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vmyshko <vmyshko@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/25 15:47:52 by vmyshko       #+#    #+#                 */
/*   Updated: 2024/12/17 12:25:23 by kkopnev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include "../LIBFT/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h> // For O_RDONLY
# include <unistd.h> // For open(), close()
// u_int32_t value = 1234567890;

/* WINDOWS DEFINES */

# define WIDTH 1920
# define HEIGHT 1080
//rotation speed and movement speed in radians
# define RSPEED 0.2
# define MSPEED 0.1
# define DOFIGA 1e30

# define ERR_MLX "Mlx42 error."
# define ERR_ARGV "ONLY 2 arguments are allowed. Did you put 2? I doubt!."
# define ERR_MALLOC "Malloc failed. life is complicated."
# define ERR_OUFLOW "RGB range mistake [0, 255]. Check your input file"
# define ERR_RGB "RGB is 3 values, 2 is wrong, 4 is too"
# define ERR_NORGB "Void is not a color."
# define ERR_EMPTYPATH "Where is the path to the file?"
# define ERR_NOMAP "No map! What's going on??."
# define ERR_UNKNOWNID "You are allowed: NO,SO,WE,EA,F or C only. TYPO? eval??"
# define ERR_PARSING "Parsing error - I've tried, but you are cheating."
# define ERR_MAPNOTCLOSED "Close map. it is NOT now"
# define ERR_FORBIDDENCHAR "Forbidden character. Check the map"
# define ERR_NOPLAYER "NO Player. No game! Check the map"
# define ERR_MANYPLAYERS "There can be ONLY 1 player. It's SOLO."
# define ERR_FILENAME "File name invalid."
# define ERR_FILEEXTENSION "File extension invalid. It is NOT .cub"
# define ERR_EXTRA_CONTENT "Some extra shir in file! WE did check it, dude!"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_map
{
	char		**map;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*we;
	mlx_image_t	*ea;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	size_t		max;
	int			fc[2];
}	t_map;

typedef struct s_player
{
	t_vector	pos;
	t_vector	plane;
	t_vector	dir;
	int			nb;
}	t_player;

typedef struct s_data
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	size_t		time;
	int			width;
	int			height;
}	t_data;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_raycast
{
	int				draw_start;
	int				draw_end;
	int				line_height;
	t_int_vector	tex;
	t_int_vector	ipos;
	t_int_vector	step;
	int				side;
	int				x;
	int				y;
	t_vector		ray_dir;
	t_vector		delta_dist;
	t_vector		side_dist;
	double			perp_wall_dist;
	mlx_image_t		*t;
}	t_raycast;

//utils:
int		ft_strslen(char **strs);
char	**ft_arrayjoin(char **old, char **new, int size_new);
char	*ft_strrev(char *str);
char	*strdup_to(char *line, int start);
void	add_color(char t, t_data *data);
char	**my_split(char *str, char *sep);
void	free_split(char **array, int len);

//init and parsing
void	fill_player_infos(t_data *data, double dir[2], double plane[2]);
char	*fill_line(t_data *data, char *str);
int		input_check(char *map_name, t_data *data);
void	get_infos(int fd, t_data *data);
void	free_all(char *str, int out, t_data *data);
//raycasting
void	raycast(t_data *data);
void	resize_render(t_data *data);
void	draw_ceiling_floor(t_data *data);
void	init_ray_param(t_data *data, t_raycast *rc);
void	step_init(t_data *data, t_raycast *rc);
void	dda(t_data *data, t_raycast *rc);
//game management
void	choose_texture_ptr(t_data *data, t_raycast *rc);

void	keypress(mlx_key_data_t key, void *data);
void	close_window(void *gdata);
void	resize_window(int32_t width, int32_t height, void *gdata);

#endif