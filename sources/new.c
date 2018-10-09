/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:19:32 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/09 15:21:37 by sderet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	NEWCOLOR function:
**	Create a new color with 3 parameters
*/

t_color	newcolor(double r, double g, double b)
{
	t_color	c;

	c.red = r;
	c.green = g;
	c.blue = b;
	return (c);
}

/*
**	NEWSH function:
**	Create a new sphere with 3 parameters
*/

t_item	newsph(t_vec center, double radius, int mat)
{
	t_item	sph;

	sph.item_type = SPHERE;
	sph.dir = newvec(0, 0, 0);
	sph.center = center;
	sph.radius = radius;
	sph.mat = mat;
	sph.d = 0;
	sph.angle = 0;
	return (sph);
}

/*
**	NEWPLANE function:
**	Create a new plane with 3 parameters
*/

t_item	newplane(t_vec dir, double d, int mat)
{
	t_item	p;

	p.item_type = PLANE;
	p.dir = dir;
	p.center = newvec(0, 0, 0);
	p.radius = 0;
	p.mat = mat;
	p.d = d;
	p.angle = 0;
	return (p);
}

/*
**	NEWCYL function:
**	Create a new cylinder with 4 parameters
*/

t_item	newcyl(t_vec dir, t_vec center, double radius, int mat)
{
	t_item	cy;

	cy.item_type = I_CYL;
	cy.dir = dir;
	cy.center = center;
	cy.radius = radius;
	cy.mat = mat;
	cy.d = 0;
	cy.angle = 0;
	return (cy);
}

/*
**	NEWCONE function:
**	Create a new cone with 4 parameters
*/

t_item	newcone(t_vec dir, t_vec center, double angle, int mat)
{
	t_item	co;

	co.item_type = I_CONE;
	co.dir = dir;
	co.center = center;
	co.radius = 0;
	co.mat = mat;
	co.d = 0;
	co.angle = angle;
	return (co);
}
