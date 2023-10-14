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
    int y;
    int valeur;
}	t_point;

typedef struct s_map_ligne
{
    t_point				*points;
	struct s_map_ligne	*next;
}	t_map_ligne;

typedef struct s_map
{
	int 		nombre_de_lignes;
    t_map_ligne *premiere_ligne;
}	t_map;


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
