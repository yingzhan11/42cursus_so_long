# include "so_long.h"

//check file, is invalid, exit
static void file_check (t_map *map)
{
    int length;
    int fd;
    
    //is file
    if (!map->filename)
        error_info(map, "NULL filname of map!");
    //filename is *.ber
    length = ft_strlen(map->filename);
    if (ft_strncmp(&map->filename[length - 4], ".ber", 4))
        error_info(map, "Map name is not '*.ber'!");
    //open
    fd = open(map->filename, O_RDONLY);
    if (fd == -1)
        error_info(map, "Failed to open map file!");
    close (fd);
}

void count_rows(t_map *map)
{
    char *line;
    int fd;

    fd = open(map->filename, O_RDONLY);
    if (fd < 0)
        error_info(map, "Failed to open map file!");
    while ((line = get_next_line(fd)) != NULL)
    {
        map->rows++;
        free (line);
    }
    close (fd);
}

void read_map(t_map *map) 
{
    char *line;
    int y;
    int fd;

    count_rows(map);
    map->grid = malloc((map->rows + 1) * sizeof(char *));
    if (map->grid == NULL)
        error_info(map, "Failed to create map grid!");
    fd = open(map->filename, O_RDONLY);
    if (fd < 0)
        error_info(map, "Failed to open map file!");
    y = 0;
    while ((line = get_next_line(fd)) != NULL) 
    {
        //if (map->cols == 0) 
            //map->cols = ft_strlen(line) - 1; // exclude newline character
        map->grid[y] = ft_strtrim(line, "\n");
        if (!map->grid[y])
            error_info(map, "Failed to create column in map grid!");
        y++;
        free(line);
    }
    close(fd);
}

void map_initialize(t_map *map)
{
    //check file, if invalid, exit
    file_check(map);

    //read file to a 2d array
    read_map(map); //TODO

    check_map(map);
    //check elements '01CEP' only 1E, 1C, 1P
    //check shape, rectangular
    //check closed walls
    //check path, atleast a valid path
}