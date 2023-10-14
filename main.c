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

int	ft_find_width(int fd)
{
	int		i;
	int		count;
	char	*ligne;

	i = 0;
	count = 0;
	ligne = get_next_line(fd);
	while (ligne[i])
	{
		if (ligne[i] >= '0' && ligne[i] <= '9')
			count++;
		i++;
	}
	free(ligne);
	close(fd);
	return (count);
}

t_point	*ft_stock_ligne(int fd, int width)
{
	char	*ligne;
	char	**ligne_split;
	int		i;
	int		j;
	t_point	*map_ligne;

	ligne = get_next_line(fd);
	i = 0;
	j = 0;
	map_ligne = (t_point*)malloc(sizeof(t_point) * width);
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

t_point	**ft_stock_map(int fd, char	*fichier_map)
{
	t_point			**map;
	int				height;
	int				width;
	int				i;

	i = 1;
	map = NULL;
	height = ft_find_height(fd);
	fd = open(fichier_map, O_RDONLY);
	width = ft_find_width(fd);
	fd = open(fichier_map, O_RDONLY);
	printf("longueur : %d\nlargeur : %d\n", height, width);

	map = (t_point**)malloc(sizeof(t_point*) * height);
	while (i < height)
	{
		map[i] = ft_stock_ligne(fd, width);
		i++;
	}

	ft_print_matrice(map, height, width);
	return (map);
}

int main(int argc, char *argv[])
{
 	void		*mlx;
	void		*win;
	t_point		**map;
	int		fd;

	(void)argc;
   	(void)win;
	(void)mlx;
	(void)map;
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	map = ft_stock_map(fd, argv[1]);


	mlx = mlx_init();
   	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "FDF by Caedus");
    mlx_loop(mlx);
	return (0);
}
