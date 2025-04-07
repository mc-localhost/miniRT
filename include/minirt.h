/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:53 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/04/07 07:19:29 by ykhattab         ###   ########.fr       */
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
# include <fcntl.h>

# define WIDTH 600
# define HEIGHT 300
# define INVALID_VEC3 ((t_vec3){NAN, NAN, NAN})
# define INVALID_COL (t_colour){-1, -1, -1, -1.0f}

// Key codes for MacOS
# define KEY_ESC     53
# define KEY_W       13
# define KEY_A       0
# define KEY_S       1
# define KEY_D       2
# define KEY_Q       12
# define KEY_E       14
# define KEY_LEFT    123
# define KEY_RIGHT   124
# define KEY_UP      126
# define KEY_DOWN	125
# define KEY_PLUS	24
# define KEY_MINUS	27

// object transform keys
# define KEY_I       34
# define KEY_K       40
# define KEY_J       38
# define KEY_L       37
# define KEY_U       32
# define KEY_O       31
//for object rotation direction
# define KEY_NUM_2           84
# define KEY_NUM_4           86
# define KEY_NUM_6           88
# define KEY_NUM_8           91

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

// typedef struct s_ambient_light
// {
// 	t_colour		colour;
// }					t_ambient_light;

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
	t_obj			*objects;
	t_camera		camera;
	t_light			light;
	t_colour		a_light;
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
	//transformation variables
	float			move_speed;       // Units per keypress for translation
	float			rotate_speed;		//radians per key press
    bool			needs_update;      // Flag to indicate when the scene needs to be rerendered
	t_obj			*selected_object; //currently selected object
}					t_data;

/*		MAIN		*/
int					error_message(char *str);
int					init_data(t_data *data, char *file);
void				init_viewport(t_data *data);


/*		COLOUR		*/
int					rgb_to_int(t_colour c);
t_colour			c_clamp(t_colour colour);
t_colour			c_add(t_colour a, t_colour b);
t_colour			c_scale(t_colour colour, float c);
void				add_ambient(t_colour *obj, t_colour a_light);

/*		PUT PIXELS		*/
t_ray				send_cam_ray(t_data *data, int x, int y);
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
t_hit				hit_sphere(t_ray r, t_obj *sp);
float				solve_quadratic(float d, float a, float b);

/*		PLANE		*/
t_hit				hit_plane(t_ray r, t_obj *pl);

/*		ERRORS		*/
int					error_message(char *str);

/*		UTILS		*/
t_obj				*create_object(t_type type, t_vec3 center, t_colour colour,
						t_vec3 norm, float diameter, float h);
void				add_object(t_obj **list, t_obj *new_obj);
void				setup_scene(t_scene *scene);

/*		PARSING		*/
int					rt_file(char *file);
int					open_file(const char *filename);
int				parse_scene_file(const char *filename, t_scene *scene);

// parse_vector_color.c
t_vec3				parse_vector(char *string);
t_colour			parse_colour(char *string);
bool				validate_colour(t_colour colour);
bool				is_valid_component(char *str, int *out);
void				free_split(char **split);

// parse_objects.c
int				parse_sphere(char *line, t_scene *scene);
int				parse_plane(char *line, t_scene *scene);
int				parse_cylinder(char *line, t_scene *scene);
int				parse_ambient(char *line, t_scene *scene);
int				parse_light(char *line, t_scene *scene);

// parse_scene.c
int					parse_line(char *line, t_scene *scene);
int					parse_camera(char *line, t_scene *scene);
bool				is_number(char *str);
bool				is_valid_ratio(float f);


// movement
void				move_camera_forward(t_data *data, float distance);
void				move_camera_sideways(t_data *data, float distance);
void				move_camera_vertical(t_data *data, float distance);
void				move_sphere_x(t_data *data, t_obj *sphere, float distance);
void				move_sphere_y(t_data *data, t_obj *sphere, float distance);
void				move_sphere_z(t_data *data, t_obj *sphere, float distance);
void				move_plane_x(t_data *data, t_obj *plane, float distance);
void				move_plane_y(t_data *data, t_obj *plane, float distance);
void				move_plane_z(t_data *data, t_obj *plane, float distance);
//rotation
void				rotate_camera_yaw(t_data *data, float angle);
void				rotate_camera_pitch(t_data *data, float angle);
void				rotate_object_x(t_obj *obj, float angle);
void				rotate_object_y(t_obj *obj, float angle);
void				rotate_object_z(t_obj *obj, float angle);
//selection

void				select_next_object(t_data *data);
void				select_prev_object(t_data *data);

/*		CLEANUP		*/
int					clean_exit(t_data *data);
void				free_scene(t_scene *scene);
int					key_hook(int k, t_data *data);

#endif
