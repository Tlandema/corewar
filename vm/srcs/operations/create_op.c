#include "corewar.h"

void	init_op(t_op *op)
{
    op->active = 0;
	op->op_code = 0;
	op->ocp = 0;
	op->param[0] = 0;
	op->param[1] = 0;
	op->param[2] = 0;
	op->type_param[0] = 0;
	op->type_param[1] = 0;
	op->type_param[2] = 0;
	op->nb_cycle = 0;
	op->pos_op_code = 0;
}

void	create_op(t_process *process, int op_code)
{
	init_op(&process->op);
	process->op.active = 1;
	process->op.op_code = op_code;
	process->op.nb_cycle = op_tab[op_code - 1].nb_cycle - 1;
	process->op.pos_op_code = process->pc;
}

void	delete_op(t_process *process)
{
	process->op.op_code = 0;
	process->op.ocp = 0;
	ft_bzero(process->op.param, 3);
	ft_bzero(process->op.type_param, 3);
	process->op.nb_cycle = 0;
	process->op.pos_op_code = 0;
	process->op.active = 0;
}
