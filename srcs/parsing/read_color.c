/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:33 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/19 20:54:48 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error rgb_error(char *line, t_error error)
{
	ft_printf("Error\n");
	if (error == RGB_ERR)
	{
		ft_printf("Invalid color description:\n");
		ft_printf("%s", line);
		ft_printf("Color should be in the format: R,G,B\n");
	}
	if (error == RGB_NUM_ERR)
	{
		ft_printf("Invalid RGB value:\n");
		ft_printf("%s\n", line);
		ft_printf("RGB values should be between 0 and 255\n");
	}
	return (error);
}

int	ft_count_digits(char *line, int i)
{
	int	counter;

	counter = 0;
	while (line[i] && ft_isdigit(line[i]) == 1)
	{
		i++;
		counter++;
	}
	return (counter);
}

t_error check_after_last_digit(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '\n')
		return (ft_printf("this 3\n"), rgb_error(line, RGB_ERR));
	return (SUCCESS);
}


t_error	check_rgb(char *line)
{
	int	i;
	int	digit_count;
	int	number_count;

	i = 0;
	number_count = 0;
	while (line[i])
	{
		digit_count = ft_count_digits(line, i);
		if (digit_count > 3)
			return (ft_printf("this 1\n"), rgb_error(line, RGB_NUM_ERR));
		if (digit_count == 0)
			return (ft_printf("this 2\n"), rgb_error(line, RGB_ERR));
		number_count++;
		i += digit_count;
		if (number_count == 3)
			return (check_after_last_digit(line, i));
		else
		{
			if (line[i] != ',')
				return (ft_printf("this 4\n"), rgb_error(line, RGB_ERR));
			i++;
		}
	}
	return (rgb_error(line, RGB_ERR));
}

t_error	read_color(char *line, t_identifier identifier, t_data *data)
{
	t_rgb		rgb;
	t_error		status;

	while (line[0] && line[0] == ' ')
		line++;
	if (!line[0])
		return (rgb_error(line, RGB_ERR));
	status = check_rgb(line);
	if (status != SUCCESS)
		return (status);
	rgb.red = ft_atoi(line);
	line += ft_count_digits(line, 0) + 1;
	rgb.green = ft_atoi(line);
	line += ft_count_digits(line, 0) + 1;
	rgb.blue = ft_atoi(line);
	ft_printf("red: %d, green: %d, blue: %d\n", rgb.red, rgb.green, rgb.blue);
	if (rgb.red > 255 || rgb.green > 255 || rgb.blue > 255)
		return (ft_printf("this 5\n"), rgb_error(line, RGB_NUM_ERR));
	if (identifier == FLOOR)
		data->graphics.floor = rgb;
	else
		data->graphics.ceiling = rgb;
	return (SUCCESS);
}