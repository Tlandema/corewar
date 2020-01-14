/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:45:29 by brichard          #+#    #+#             */
/*   Updated: 2020/01/14 12:46:12 by brichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Soustrait le second parametre au premier parametre, et stock le
** resultat dans le troisieme parametre. Si la valeur resultante est egale a
** zero, alors le carry passe a l'etat un, sinon a l'etat zero.
*/

void	sub(t_vm *vm, t_process *process)
{
	int		sub;

	if (process->op.param[0] >= 1 && process->op.param[0] <= REG_NUMBER
			&& process->op.param[1] >= 1 && process->op.param[1] <= REG_NUMBER
			&& process->op.param[2] >= 1 && process->op.param[2] <= REG_NUMBER)
	{
		sub = process->reg[process->op.param[0] - 1]
				- process->reg[process->op.param[1] - 1];
		process->reg[process->op.param[2] - 1] = sub;
		process->carry = sub == 0 ? 1 : 0;
		if (vm->verbose)
			show_op(process);
	}
}
