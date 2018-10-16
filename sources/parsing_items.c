/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/16 12:07:50 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	PARSING_LIGHT function:
**	Parses the light parameters in the structure
*/

void	parsing_light(char **s, t_env *e, int *k)
{
	int	i;

	if (ft_strcmp(s[0], "LIGHT"))
		return ;
	i = 0;
	if (table_len(s) != 9 && table_len(s) != 13 && table_len(s) != 17)
		ft_printerror("Invalid file");
	e->light[*k].pos = newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]),
		ft_atoi(s[4]));
	e->light[*k].intensity = newcolor(ft_atoi(s[6] + 1), ft_atoi(s[7]),
			ft_atoi(s[8]));
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'T')
			e->light[*k].pos = add(e->light[*k].pos,
				newvec(ft_atoi(s[10 + i] + 1), ft_atoi(s[11 + i]),
					ft_atoi(s[12 + i])));
		i += 4;
	}
	(*k)++;
}

/*
**	PARSING_CONE function:
**	Parses the cone parameters in the structure
*/

void	parsing_item(char **s, t_env *e, int *k)
{
	t_item	co;

	if (ft_strcmp(s[0], "CONE") && ft_strcmp(s[0], "CYLINDER") && ft_strcmp(s[0],
				"SPHERE") && ft_strcmp(s[0], "PLANE") && ft_strcmp(s[0], "DISK"))
		return ;
//	if (table_len(s) != 13 && table_len(s) != 17 && table_len(s) != 21)
//		ft_printerror("Invalid file");
	co = e->item[*k];
	if (!(ft_strcmp(s[0], "CONE")))
		co = newcone(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8])),
			ft_atoi(s[10]), ft_atoi(s[12]));
	else if (!(ft_strcmp(s[0], "CYLINDER")))
		co = newcyl(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8])),
			ft_atoi(s[10]), ft_atoi(s[12]));
	else if (!(ft_strcmp(s[0], "SPHERE")))
		co = newsph(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			ft_atoi(s[6]), ft_atoi(s[8]));
	else if (!(ft_strcmp(s[0], "PLANE")))
		co = newplane(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			ft_atoi(s[6]), ft_atoi(s[8]));
	else if (!(ft_strcmp(s[0], "DISK")))
		co = newdisk(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8])),
			ft_atoi(s[10]), ft_atoi(s[12]));
	if (ft_strcmp(s[0], "SPHERE"))
		co.dir = normalize(co.dir);
	e->item[*k] = co;
	(*k)++;
}
