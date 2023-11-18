#ifndef FDF_H
# define FDF_H

#include "../libft/libft.h"
#include <fcntl.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

typedef struct	s_point
{
    int x;
	int	x_iso;
    int y;
	int	y_iso;
    int valeur;
}	t_point;

typedef struct s_angle_and_more
{
    void 	*mlx;
    void 	*win;
	double 	angle;
	double 	scale_x;
    double 	scale_y;
	double	scale_z;
    int		center_x;
    int		center_y;
	int		map_width;
    int		map_height;
    int		x_offset;
    int		y_offset;
}	t_angle_and_more;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



# ifndef WIN_WIDTH
#  define WIN_WIDTH  1440 // Largeur de la fenêtre
# endif

# ifndef WIN_HEIGHT
#define WIN_HEIGHT 850 // Hauteur de la fenêtre
# endif

# ifndef BUTTON_WIDTH 
#define BUTTON_WIDTH 100 // Largeur du bouton
# endif

# ifndef BUTTON_HEIGHT
#define BUTTON_HEIGHT 50 // Hauteur du bouton
# endif



#endif
