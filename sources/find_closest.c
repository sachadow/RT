/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/09 15:33:56 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	FIND_CLOSEST_ITEM function:
**	Finds the closest item hit by the ray
*/

int			find_closest_item(t_ray r, t_env *e, t_vec *newstart, int *curr)
{
	double	t;
	double	before;
	int		(*hit[6])(t_ray, t_item, double *);
	int		i;

	t = -1;
	before = -1;
	hit[SPHERE] = &hitsphere;
	hit[PLANE] = &hitplane;
	hit[I_CYL] = &hitcylinder;
	hit[I_CONE] = &hitcone;
	hit[DISK] = &hitdisk;
	*curr = -1;
	i = -1;
	while (++i < e->nbs[3])
	{
		if (hit[e->item[i].item_type](r, e->item[i], &t))
			if (before == -1 || (t < before && t >= 0))
			{
				before = t;
				*curr = i;
			}
	}
  if (*curr < 0)
    return (-1);
	hit[e->item[*curr].item_type](r, e->item[*curr], &t);
	*newstart = add(scale(t, r.dir), r.start);
	return (e->item[*curr].item_type);
}
