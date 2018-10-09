/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/09 13:35:38 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	PARSING_CAM function:
**	Parses the cam parameters in the cam structure
*/

void	parsing_cam(char **s, t_env *e)
{
	int		i;

	i = 0;
	if (ft_strcmp(s[0], "CAM"))
		return ;
	if (table_len(s) != 9 && table_len(s) != 17 && table_len(s) != 13)
		ft_printerror("Invalid file");
	e->cam->pos = newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4]));
	e->cam->dir = newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8]));
	e->cam->dir = normalize(e->cam->dir);
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'R')
			e->cam->dir = rotate(e->cam->dir, ft_atoi(s[10 + i] + 1),
				ft_atoi(s[11 + i]), ft_atoi(s[12 + i]));
		if (*(s[9 + i] + 1) == 'T')
			e->cam->pos = add(e->cam->pos, newvec(ft_atoi(s[10 + i] + 1),
				ft_atoi(s[11 + i]), ft_atoi(s[12 + i])));
		i += 4;
	}
}

/*
**	FILL_STRUCT function:
**	Fulfills the environment structure with the items structures
*/

void	fill_struct(t_env *e, char *line, int index[7])
{
	char	**s;

	s = ft_strsplit((char const*)line, ' ');
	if (!ft_strcmp(s[0], "MAT") && table_len(s) == 11)
	{
		e->mat[index[0]] = (t_mat){{ft_atoi(s[2] + 1), ft_atoi(s[3]),
			ft_atoi(s[4])}, ft_atoi(s[6]), ft_atoi(s[8]), ft_atoi(s[10])};
		index[0]++;
	}
	parsing_cam(s, e);
	parsing_light(s, e, &index[1]);
	parsing_item(s, e, &index[2]);
	if (!ft_strcmp(s[0], "CONE") && (ft_atoi(s[10]) >= 70 ||
		ft_atoi(s[10]) <= 0))
		ft_printerror("Angle error");
	if (!ft_strcmp(s[0], "CYLINDER") && ft_atoi(s[10]) <= 0)
		ft_printerror("Radius error");
	ft_freesplit(s);
}

/*
**	TABLE_LEN function:
**	Calculates the length of a char * table
*/

int		table_len(char **s)
{
	int	l;

	l = 0;
	while (s[l] != 0)
		++l;
	return (l);
}
