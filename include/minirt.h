/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:53 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/21 11:06:40 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx/mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 600
# define HEIGHT 300

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}					t_type;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
	// for lights' brightness and ratio
	float			ratio;
}					t_colour;

// typedef struct s_sphere
// {
// 	t_vec3			center;
// 	float			diameter;
// 	float			r;
// 	t_colour		colour;
// }					t_sphere;

// typedef struct s_plane
// {
// 	t_vec3			point;
// 	t_vec3			norm;
// 	t_colour		colour;
// }					t_plane;

// typedef struct s_cylinder
// {
// 	t_vec3			center;
// 	t_vec3			norm;
// 	float			diameter;
// 	float			r;
// 	float			h;
// 	t_colour		colour;
// }					t_cylinder;

typedef struct s_camera
{
	t_vec3			view_point;
	t_vec3			norm;
	float			fov_rad;
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

typedef struct s_ray
{
	t_vec3			start;
	t_vec3			dir;
	t_colour		colour;
}					t_ray;

typedef struct s_hit
{
	t_vec3			p;
	t_vec3			normal;
	float			t;
	bool			front_face;
	t_colour		colour;
}					t_hit;

typedef struct s_obj
{
	struct s_obj	*next;
	t_type			type;
	t_vec3			center;
	t_colour		colour;
	t_vec3			norm;
	float			diameter;
	float			r;
	//	for cylinder
	float			h;
	//	for plane
	t_vec3			point;

}					t_obj;

typedef struct s_scene
{
	// this should all be 1 list of all objects
	// t_sphere		**spheres;
	// t_cylinder		**cylinders;
	// t_plane			**planes;
	// int				num_sp;
	// int				num_cy;
	// int				num_pl;
	t_obj			*objects;
	t_camera		camera;
	t_light			light;
	t_ambient_light	a_light;
}					t_scene;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_l;
	int				endian;
}					t_img;

typedef struct s_data
{
	void			*mlx;
	void			*window;
	t_img			img;
	t_scene			*scene;
	int				w;
	int				h;
	//------ viewport -------
	float			aspect_ratio;
	float			focal_len;
	float			viewport_h; //can be a var in function
	float			viewport_w; //can be a var in function
	t_vec3			viewport_u; //can be a var in function
	t_vec3			viewport_v; //can be a var in function
	t_vec3			viewport_u_l; //can be a var in function
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	t_vec3			pixel00_loc;

}					t_data;

/*		MAIN		*/
int					error_message(char *str);

/*		PUT PIXELS		*/
t_ray				send_cam_ray(t_data *data, int x, int y);
int					rgb_to_int(t_colour c);
void				put_pixel_to_img(t_img *img, int x, int y, int colour);
void				put_pixels(t_data *data);

/*		VECTOR OPERATIONS		*/
t_vec3				v_add(t_vec3 vec, t_vec3 vec2);
t_vec3				v_subtract(t_vec3 vec, t_vec3 vec2);
t_vec3				v_scale(t_vec3 vec, float c);
float				v_len(t_vec3 vec);
t_vec3				v_unit(t_vec3 vec);
t_vec3				v_at(t_ray ray, float t);
float				v_dot(t_vec3 vec, t_vec3 vec2);
t_vec3				v_cross(t_vec3 vec, t_vec3 vec2);
void				v_add_inplace(t_vec3 *vec, t_vec3 vec2);
void				v_subtract_inplace(t_vec3 *vec, t_vec3 vec2);
void				v_scale_inplace(t_vec3 *vec, float c);

/*		SPHERE		*/
float				hit_sphere(t_ray r, t_obj *sp);
float				solve_quadratic(float d, float a, float b);

/*		ERRORS		*/
int					error_message(char *str);

/*		UTILS		*/
t_obj				*create_object(t_type type, t_vec3 center, t_colour colour,
						t_vec3 norm, float diameter, float h);
void				add_object(t_obj **list, t_obj *new_obj);
void				setup_scene(t_scene *scene);

/*		PARSING		*/
int					rt_file(char *file);

/*		CLEANUP		*/
int					clean_exit(t_data *data);
int					key_hook(int k, t_data *data);

#endif