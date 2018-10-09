/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/09 15:08:28 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	READ_FILE1 function:
**	Counts the number of items in the config file line by line
*/

int		read_file1(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		nbs[7];
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = -1;
	while (++i < 8)
		nbs[i] = 0;
	while (get_next_line(fd, &line) == 1)
	{
		count_param_control(line, nbs);
		free(line);
	}
	free(line);
	if (nbs[1] == 0 || nbs[2] == 0 || nbs[0] != 1)
		ft_printerror("No material, no light or not one cam in the file");
	build_struct(e, nbs);
	close(fd);
	return (1);
}

/*
**	READ_FILE2 function:
**	Fulfills the environment structure with items
*/

int		read_file2(char *av, t_env *e)
{
	int		fd;
	char	*line;
	int		i;
	int		index[7];

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = -1;
	while (++i < 7)
		index[i] = 0;
	while (get_next_line(fd, &line) == 1)
	{
		fill_struct(e, line, index);
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}

/*
**	COUNT_PARAM_CONTROL function:
**	Controls if the line of the file is correct, then increments parameters
*/

void	count_param_control(char *line, int nbs[6])
{
	char	**s;
	int		l;

	s = ft_strsplit((char const*)line, ' ');
	l = table_len(s);
	if (!s[0])
		ft_printerror("Invalid file");
	else if (!ft_strcmp(s[0], "//"))
	{
		ft_freesplit(s);
		return ;
	}
	count_param(nbs, s, l);
	ft_freesplit(s);
}

/*
**	COUNT_PARAM function:
**	Adds one item according to the parameters of the line
*/

void	count_param(int nbs[6], char **s, int l)
{
	if (!ft_strcmp(s[0], "CAM") && (l == 9 || l == 13 || l == 17))
		nbs[0]++;
	else if (!ft_strcmp(s[0], "MAT") && l == 11)
		nbs[1]++;
	else if (!ft_strcmp(s[0], "LIGHT") && (l == 9 || l == 13 || l == 17))
		nbs[2]++;
	else if (!ft_strcmp(s[0], "SPHERE") && (l == 9 || l == 13 || l == 17))
		nbs[3]++;
	else if (!ft_strcmp(s[0], "PLANE") && (l == 9 || l == 13 || l == 17))
		nbs[3]++;
	else if (!ft_strcmp(s[0], "CYLINDER") && (l == 13 || l == 17 || l == 21))
		nbs[3]++;
	else if (!ft_strcmp(s[0], "CONE") && (l == 13 || l == 17 || l == 21))
		nbs[3]++;
	else if (!ft_strcmp(s[0], "DISK") && (l == 13 || l == 17 || l == 21))
		nbs[3]++;
	else
		ft_printerror("Invalid file");
}

/*
**	BUILD_STRUCTURE function:
**	Builds the items structures inside the environment structure
*/

void	build_struct(t_env *e, int nbs[7])
{
	int	a;

	if (!(e->cam = (t_cam*)malloc(sizeof(t_cam))))
		ft_printerror("Error malloc");
	if (!(e->mat = (t_mat*)malloc(nbs[1] * sizeof(t_mat))))
		ft_printerror("Error malloc");
	if (!(e->light = (t_light*)malloc(nbs[2] * sizeof(t_light))))
		ft_printerror("Error malloc");
	if (!(e->item = (t_item*)malloc(nbs[3] * sizeof(t_item))))
		ft_printerror("Error malloc");
	a = 0;
	while (a < 4)
	{
		e->nbs[a] = nbs[a];
		a++;
	}
}
