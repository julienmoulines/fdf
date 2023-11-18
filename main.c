/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jmouline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:58:09 by jmouline          #+#    #+#             */
/*   Updated: 2023/11/14 03:25:18 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	ft_print_matrice(t_point **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < height)
	{
		while (x < width)
		{
			ft_printf("%d ", map[y][x].valeur);
			x++;
		}
		printf("\n");
		printf("\n");
		x = 0;
		y++;
	}
	return ;
}

int	ft_find_height(int fd)
{
	int	i;

	i = 0;
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

int	ft_find_width(char *ligne)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (ligne[i])
	{
		if (ligne[i] >= '0' && ligne[i] <= '9')
		{
			count++;
			while (ligne[i] >= '0' && ligne[i] <= '9')
				i++;
		}
		i++;
	}
	return (count);
}

t_point	*ft_stock_ligne(int fd, int *width, t_angle_and_more *mlx)
{
	char	*ligne;
	char	**ligne_split;
	int		i;
	int		j;
	t_point	*map_ligne;

	ligne = get_next_line(fd);
	*width = ft_find_width(ligne);
	mlx->map_width = *width;
	i = 0;
	j = 0;
	map_ligne = (t_point *) malloc(sizeof(t_point) * *width);
	ligne_split = ft_split(ligne, ' ');
	while (ligne_split[j])
	{
		map_ligne[i].valeur = ft_atoi(ligne_split[j]);
		i++;
		j++;
	}
	i = 0;
	j = 0;
	return (map_ligne);
}

void	ft_init_x_y(t_point **map, int height, int width)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			map[y][x].y = y;
			map[y][x].x = x;
			x++;
		}
		y++;
	}
}

t_point	**ft_stock_map(int fd, char	*fichier_map, t_angle_and_more *mlx)
{
	t_point			**map;
	int				width;
	int				i;

	i = 0;
	map = NULL;
	mlx->map_height = ft_find_height(fd);
	fd = open(fichier_map, O_RDONLY);
	map = (t_point **) malloc(sizeof(t_point *) * mlx->map_height);
	while (i < mlx->map_height)
	{
		map[i] = ft_stock_ligne(fd, &width, mlx);
		i++;
	}
	ft_init_x_y(map, mlx->map_height, width);
	mlx->map_width = width;
	printf("longueur : %d\nlargeur : %d\n", mlx->map_height, width);
	ft_print_matrice(map, mlx->map_height, width);
	return (map);
}

void	ft_draw_map_line(t_point **map, t_angle_and_more *m, int x1, int y1, int x2, int y2)
{
	(void)map;
	int		dx = abs(x2 - x1);
	int		dy = abs(y2 - y1);
	int		sx = (x1 < x2) ? 1 : -1;
	int		sy = (y1 < y2) ? 1 : -1;
	int		err = dx - dy;

	while (1)
	{
		mlx_pixel_put(m->mlx, m->win, x1, y1, 0x00FF00);
		if (x1 == x2 && y1 == y2)
			break;
		int err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	ft_draw_map_lines(t_point **map, t_angle_and_more *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;

	while (i < m->map_height)
	{
		while (j < m->map_width)
		{
			// Dessiner les lignes vers les points adjacents
			if (j < m->map_width - 1)
				ft_draw_map_line(map, m, m->x_offset + (map[i][j].x - map[i][j].y) * m->cosinus,
								m->y_offset + (map[i][j].x + map[i][j].y) * sin(m->angle) * m->scale_y - map[i][j].valeur * m->scale_z,
								m->x_offset + (map[i][j + 1].x - map[i][j + 1].y) * m->cosinus,
								m->y_offset + (map[i][j + 1].x + map[i][j + 1].y) * sin(m->angle) * m->scale_y - map[i][j + 1].valeur * m->scale_z);
			
			if (i < m->map_height - 1)
				ft_draw_map_line(map, m, m->x_offset + (map[i][j].x - map[i][j].y) * m->cosinus,
								m->y_offset + (map[i][j].x + map[i][j].y) * sin(m->angle) * m->scale_y - map[i][j].valeur * m->scale_z,
								m->x_offset + (map[i + 1][j].x - map[i + 1][j].y) * m->cosinus,
								m->y_offset + (map[i + 1][j].x + map[i + 1][j].y) * sin(m->angle) * m->scale_y - map[i + 1][j].valeur * m->scale_z);

			j++;
		}
		j = 0;
		i++;
	}
}


void	ft_draw_map_point(t_point **map, t_angle_and_more *m)
{
	int		i;
	int		j;
	int		x;
	int		y;
	double	cosinus;

	cosinus = cos(m->angle) * m->scale_x;
	i = 0;
	j = 0;
	while (i < m->map_height)
	{
		while (j < m->map_width)
		{
			x = m->x_offset + (map[i][j].x - map[i][j].y) * cosinus;
			y = m->y_offset + (map[i][j].x + map[i][j].y)
				* sin(m->angle) * m->scale_y - map[i][j].valeur * m->scale_z;
			mlx_pixel_put(m->mlx, m->win, x, y, 0x00FF00);
			j++;
		}
		j = 0;
		i++;
	}
}

void	*ft_init_window(t_point **map, t_angle_and_more *angle_and_more)
{
	
	(void)map;

	angle_and_more->mlx = mlx_init();
	angle_and_more->win = mlx_new_window(angle_and_more->mlx,
		WIN_WIDTH, WIN_HEIGHT, "FDF by Caedus");
	angle_and_more->angle = M_PI / 4; // Angle isométrique en radians
	angle_and_more->center_x = WIN_WIDTH / 2 + 100; // Centre de la fenêtre
	angle_and_more->center_y = WIN_HEIGHT / 2 - 100;
	angle_and_more->scale_x = 10;
	angle_and_more->scale_y = 10;
	angle_and_more->scale_z = 10;
	angle_and_more->x_offset = angle_and_more->center_x - (angle_and_more->map_width * angle_and_more->scale_x) / 2;;
	angle_and_more->y_offset = angle_and_more->center_y - (angle_and_more->map_height * angle_and_more->scale_y) / 2;;
	angle_and_more->cosinus = cos(angle_and_more->angle) * angle_and_more->scale_x;

	ft_draw_map_lines(map, angle_and_more);
	//ft_draw_map_point(map, angle_and_more);

	return (angle_and_more->mlx);
}

void	free_map(t_angle_and_more *angle_and_more, t_point ***map)
{
	int	x;
	int	y;

	y = 0;
	while (y < angle_and_more->map_height)
	{
		x = 0;
		while (x < angle_and_more->map_width)
		{
			free(map[y][x]);
			x++;
		}
		free(map[y]);
		y++;
	}
	//free(map);
}

int	leave(t_angle_and_more *angle_and_more, t_point **map)
{
	(void)map;
	//free_map(angle_and_more, &map);
	close(angle_and_more->fd);
	exit(1);
	return 0;
}

int	key(int key, t_angle_and_more *angle_and_more, t_point **map)
{
	(void)angle_and_more;
	if (key == 65307)
		leave(angle_and_more, map);
	return 0;
}

int main(int argc, char *argv[])
{
    t_point 			**map;
	t_angle_and_more	*angle_and_more;
	// t_data				*img;

   
	(void)argc;
	angle_and_more = malloc(sizeof(t_angle_and_more));
    // Initialisation de MiniLibX et chargement de la carte
   	angle_and_more->fd = open(argv[1], O_RDONLY);
    map = ft_stock_map(angle_and_more->fd, argv[1], angle_and_more);
	ft_init_window(map, angle_and_more);
	mlx_hook(angle_and_more->win, 17, 0, leave, &angle_and_more);
	mlx_key_hook(angle_and_more->win, key, &angle_and_more);
	
	// img->img = mlx_new_image(angle_and_more->mlx, 1920, 1080);

	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	
    mlx_loop(angle_and_more->mlx); // Lancer la boucle de rendu MiniLibX
    return (0);
}


