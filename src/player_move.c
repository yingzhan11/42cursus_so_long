# include "so_long.h"

static int check_grid_next(t_map *map)
{
    //wall, stop
    if (map->grid[map->next.y][map->next.x] == '1')
    {
        ft_printf("No passage! You cannot enter the area ahead.\n");
        return (0);
    }
    //others, move to
    return (1);
}

static void get_collect(t_map *map, t_image *image)
{
    size_t i;

    i = 0;
    //count collections
    map->collect_get++;
    map->grid[map->cur.y][map->cur.x] = 'c';
    //change image of collect to empty, disabled the collect image
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
    //check collect number
    if (map->collect_get == map->collect_all)
    {
        ft_printf("You've collected all the fries!\n");
        image->exit1->instances[0].enabled = false;
    }
    else
        ft_printf("Found Fries: %d/%d\n", map->collect_get, map->collect_all);  
}

void player_move(t_map *map, t_image *image)
{
    //check next place char in map grid
    //if 0, wall or exit without all collection, cannt move to
    if (check_grid_next(map) == 0)
        return ;
    //if 1, move to
    image->player->instances[0].x = map->next.x * map->scale;
    image->player->instances[0].y = map->next.y * map->scale;
    map->move++;
    ft_printf("Steps count: %d\n", map->move);
    //change cur place
    map->cur = map->next;
    //check current place
    //if collection;
    if (map->grid[map->cur.y][map->cur.x] == 'C')
        get_collect(map, image);
    //if exit, check colloction number
    if (map->grid[map->cur.y][map->cur.x] == 'E')
    {
        //didn't collect all, move to but not out return 0
        if (map->collect_get != map->collect_all)
        {
            ft_printf("Can't open! you need to collect all the fries first.\n");
            ft_printf("Current Fries: %d/%d\n", map->collect_get, map->collect_all);
        }
        //collect all, win
        if (map->collect_get == map->collect_all)
        {
            ft_printf("You win!\n");
            quit_game(map);
        }    
    }
        
}
