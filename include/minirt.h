#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx/mlx.h>

# define WIDTH 600
# define HEIGHT 300

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct s_colour
{
	int			r;
	int			g;
	int			b;
	// for lights' brightness and ratio
	float		ratio;
}				t_colour;

typedef struct s_sphere
{
	t_vec3			center;
	float			diameter;
	float			r;
	t_colour		colour;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			norm;
	t_colour		colour;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			center;
	t_vec3			norm;
	float			diameter;
	float			r;
	float			h;
	t_colour		colour;
}					t_cylinder;

typedef struct s_camera
{
	t_vec3			view_point;
	t_vec3			norm;
	float			fov;
	int				fov_deg;
}					t_camera;

typedef struct s_light
{
	t_vec3			pos;
	t_colour		colour;
}					t_light;

typedef struct s_ambient_light
{
	t_colour		colour;
}					t_ambient_light;

typedef struct s_scene
{
	t_sphere	**spheres;
	t_cylinder	**cylinders;
	t_plane	**planes;
	int	num_sp;
	int	num_cy;
	int	num_pl;
	t_camera	camera;
	t_light	light;
	t_ambient_light a_light;
}					t_scene;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_l;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	t_img	img;
	t_scene	*scene;
	int		w;
	int		h;
	float	aspect_ratio;

}				t_data;

/*		MAIN		*/
int	error_message(char *str);

/*		ERRORS		*/
int	error_message(char *str);

/*		UTILS		*/


/*		PARSING		*/
int	rt_file(char *file);

/*		CLEANUP		*/
int clean_exit(t_data *data);

#endif