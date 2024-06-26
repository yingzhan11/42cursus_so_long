# include "so_long.h"

/*void    delete_game(t_game *game)
{
    if (!game)
        return ;
    if (game->map)
        delete_map(game->map); //TODO
    if (game->mlx)
        delete_mlx(game->mlx); //TODO
}*/

void    error_info(char *message)
{
    //delete_game(map); //TODO
    ft_printf("Error: %s\n", message);
    exit(EXIT_FAILURE);
}