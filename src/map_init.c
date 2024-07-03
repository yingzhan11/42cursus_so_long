# include "so_long.h"

//check file, is invalid, exit, is file, filename is *.ber, open
static void file_check (t_map *map, char *filename)
{
    int length;
    int fd;
    
    if (!filename)
        error_info(map, "NULL filname of map!");
    length = ft_strlen(filename);
    if (ft_strncmp(&filename[length - 4], ".ber", 4))
        error_info(map, "Map name is not '*.ber'!");
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        error_info(map, "Failed to open map file!");
    close (fd);
}

void count_rows(t_map *map, char *filename)
{
    char *line;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_info(map, "Failed to open map file!");
    while ((line = get_next_line(fd)) != NULL)
    {
        map->rows++;
        free (line);
    }
    close (fd);
}

void read_map(t_map *map, char *filename) 
{
    char *line;
    int y;
    int fd;

    count_rows(map, filename);
    map->grid = malloc((map->rows + 1) * sizeof(char *));
    if (map->grid == NULL)
        error_info(map, "Failed to create map grid!");
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_info(map, "Failed to open map file!");
    y = 0;
    while ((line = get_next_line(fd)) != NULL) 
    {
        map->grid[y] = ft_strtrim(line, "\n");
        if (!map->grid[y])
            error_info(map, "Failed to create column in map grid!");
        y++;
        free(line);
    }
    close(fd);
}

//read file to a 2d array, check_map, check shape, rectangular
//check elements '01CEP' only 1E, 1C, 1P
//check closed walls, check path, atleast a valid path
void map_initialize(t_map *map, char *filename)
{
    file_check(map, filename);
    read_map(map, filename);
    if (map->rows == 0)
        error_info(map, "Map is empty.");
    if (check_shape(map) == 0)
        error_info(map, "Map is not a rectangular.");
    if (map->rows > 120 || map->cols > 120)
        error_info(map, "This map is too big.");
    if (check_elements(map) == 0)
        error_info(map, "Elements of map is invalid.");
    if (check_wall(map) == 0)
        error_info(map, "The map is not closed by walls.");
    if (check_path(map) == 0)
        error_info(map, "Can't find a valid path on this map.");
}