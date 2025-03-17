/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:51:31 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/17 05:21:32 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

t_error			parsing(int argc, char **argv, t_data *data);

// INPUT CHECK
t_error			check_format(int argc, char **argv);
t_error			check_scene_file(t_data *data, char *filename);

bool	        is_map_char(char c);
bool            check_if_map(char *line);
t_line    		check_scenefile_line(char *line);
t_identifier 	is_identifier(char *line);

int				ft_count_words(char *line);
char 			*set_image_pointer(t_data *data, t_identifier type);

t_error			map_check(t_data *data);
#endif