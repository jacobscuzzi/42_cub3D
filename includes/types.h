/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/03 15:05:15 by jbaumfal         ###   ########.fr       */
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
	FILE_ERR,
	FATAL_ERROR,
	MAP_ERROR
}	t_error;





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