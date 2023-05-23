/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:56:10 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/05/23 13:59:50 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(int err_msg)
{
	const char	*map_error[E_LENGHT] = {
		"The requested access to the file is prohibited, \
		or the file does not yet exist.\n",
		"Invalid map extension (.cub required).\n",
		"Only 1 argument is required.\n",
		"Something went wrong initializing mlx.\n",
		"It seems like some textures or colors are missing.\n"
	};

	ft_putstr_fd("Error\n", STDOUT_FILENO);
	ft_putstr_fd((char *)map_error[err_msg], STDOUT_FILENO);
	exit(err_msg);
}
