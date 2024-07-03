# include "so_long.h"

//wall, stop    //others, move to
static int check_grid_next(t_map *map)
{

    if (map->grid[map->next.y][map->next.x] == '1')
    {
        ft_printf("No passage! You cannot enter the area ahead.\n");
        return (0);
    }
    return (1);
}

    //count collections
    //change image of collect to empty, disabled the collect image
        //check collect number
static void get_collect(t_map *map, t_image *image)
{
    size_t i;

    map->collect_get++;
    map->grid[map->cur.y][map->cur.x] = 'c';
    i = 0;
    while (i < image->collect->count)
    {
        if (image->collect->instances[i].x == map->cur.x * map->scale
        && image->collect->instances[i].y == map->cur.y * map->scale)
        {
            image->collect->instances[i].enabled = false;
            break ;
        }
        i++;
    }
    if (map->collect_get == map->collect_all)
    {
        ft_printf("You've collected all the fries!\n");
        image->exit1->instances[0].enabled = false;
    }
    else
        ft_printf("Found Fries: %d/%d\n", map->collect_get, map->collect_all);  
}

//check next place char in map grid
    //if 0, wall or exit without all collection, cannt move to
    //if 1, move to
    //change cur place
        //check current place
    //if collection;
        //if exit, check colloction number
                //didn't collect all, move to but not out return 0
                        //collect all, win
void player_move(t_map *map, t_image *image)
{
    if (check_grid_next(map) == 0)
        return ;
    image->player->instances[0].x = map->next.x * map->scale;
    image->player->instances[0].y = map->next.y * map->scale;
    map->move++;
    ft_printf("Steps count: %d\n", map->move);
    map->cur = map->next;
    if (map->grid[map->cur.y][map->cur.x] == 'C')
        get_collect(map, image);
    if (map->grid[map->cur.y][map->cur.x] == 'E')
    {
        if (map->collect_get != map->collect_all)
        {
            ft_printf("Can't open! you need to collect all the fries first.\n");
            ft_printf("Current Fries: %d/%d\n", map->collect_get, map->collect_all);
        }
        if (map->collect_get == map->collect_all)
        {
            ft_printf("You win!\n");
            quit_game(map);
        }    
    }
}
