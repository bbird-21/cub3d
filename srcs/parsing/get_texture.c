/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboyer <aboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:16:17 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/05/31 16:56:14 by aboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**create_texture_map(void)
{
	static char	*texture_map[] = {
		"NO ",
		"SO ",
		"WE ",
		"EA ",
	};

	return (texture_map);
}

static void	init_texture_path(t_data *data, char texture, char *path)
{
	if (texture == 'N')
		data->img.n_path = ft_strtrim(path + 2, " ");
	if (texture == 'S')
		data->img.s_path = ft_strtrim(path + 2, " ");
	if (texture == 'W')
		data->img.w_path = ft_strtrim(path + 2, " ");
	if (texture == 'E')
		data->img.e_path = ft_strtrim(path + 2, " ");
	data->txt.count++;
}

static bool	is_in_texture_map(char *str)
{
	static char	**texture_map;
	int			i;

	i = 0;
	texture_map = create_texture_map();
	while (texture_map[i])
	{
		if (!(ft_strncmp(texture_map[i], str, 3)))
			return (true);
		i++;
	}
	return (false);
}

void	get_textures(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->img.file[i] && data->txt.count < 4)
	{
		j = 0;
		while (is_wspace(data->img.file[i][j]))
			j++;
		if (is_in_texture_map(data->img.file[i] + j))
			init_texture_path(data, data->img.file[i][j], data->img.file[i]
					+ j);
		else if (data->img.file[i][0] != 0 && !only_wspace(data->img.file[i]))
			exit_error(E_ELEMENT);
		i++;
		data->txt.index_file++;
	}
	check_path_textures(data);
}
