/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:06:36 by root              #+#    #+#             */
/*   Updated: 2024/12/20 15:47:44 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void custom_switch(char *key, int *keys)
{
    if (ft_strncmp(key, "NO", 3) == 0)
        keys[0]++;
    else if (ft_strncmp(key, "SO", 3) == 0)
        keys[1]++;
    else if (ft_strncmp(key, "WE", 3) == 0)
        keys[2]++;
    else if (ft_strncmp(key, "EA", 3) == 0)
        keys[3]++;
    else if (ft_strncmp(key, "F", 2) == 0)
        keys[4]++;
    else if (ft_strncmp(key, "C", 2) == 0)
        keys[5]++;
    else
        keys[0] = 100;
}

static int  ft_check_double(int *keys)
{
    int i;

    i = 0;
    while (i < 6)
    {
        if (keys[i] > 1)
            return (1);
        i++;
    }
    return (0);
}

int ft_check_double_keys(char *path)
{
    int     fd;
    char    *line;
    char    **split;
    int     keys[6];

    keys[0] = 0;
    keys[1] = 0;
    keys[2] = 0;
    keys[3] = 0;
    keys[4] = 0;
    keys[5] = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (ft_log("Failed to open file", NULL, 3), 1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        split = ft_split(line, ' ');
        if (!split)
            return (ft_log("Failed to split line", NULL, 3), 1);
        custom_switch(split[0], keys);
        ft_free_2d_array(split);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (ft_check_double(keys));
}
