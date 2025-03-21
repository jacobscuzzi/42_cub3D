/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:31:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/21 15:25:32 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "cub3d.h"
# include "math.h"
# define WIDTH 1280 // multiple de 64
# define HEIGHT 704 // multiple de 64
# define MINIMAP_WIDTH 200
# define MINIMAP_SCALE 0.2
# define PX_SIZE 64
# define FOV (PI / 3) // Field of view
# define NUM_RAYS 1280 // 1 ray per pixel (WIDTH)
# define ROW 4
# define COL 4

static const char map[8][9] = {
    "  1111  ",
    "  1001  ",
    "1110011 ",
    " 100001 ",
    "  10N01 ",
    " 110001 ",
    "  1001  ",
    "  1111  "
};
#endif