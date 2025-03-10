/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/09 23:59:22 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H	
# define TYPES_H

# include "../libft/includes/libft.h"

//NUMBERS

typedef enum e_error
{
	SUCCESS,
	INPUT_ERR,
	OPEN_ERR,
	SCENE_LINE_ERR,
	MAP_ERROR,
	FATAL_ERROR
}	t_error;

typedef enum e_identifier
{
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CIELING
}	t_identifier;

typedef enum e_line_check
{
	L_EMPTY,
	L_IDENTIFIER,
	L_MAP,
	L_INVALID,
	L_VALID
}	t_line_check;



// Structures

typedef struct s_data
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
}	t_data;

typedef struct coordinate
{
	size_t	row;
	size_t	column;
}	t_coord;


#endif