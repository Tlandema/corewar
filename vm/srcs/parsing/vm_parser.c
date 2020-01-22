/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:27:05 by brichard          #+#    #+#             */
/*   Updated: 2020/01/22 18:55:22 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		sort_champ_tab(t_parser *parser, t_champ champ[4],
				int32_t chp_amount)
{
	t_champ	tmp;
	uint8_t	i;
	uint8_t	j;

	i = 0;
	j = chp_amount;
	if (parser->state == S_ERR)
		return ;
	while (j >= 1)
	{
		while (i < j)
		{
			if (champ[i].num > champ[i + 1].num)
			{
				tmp = champ[i];
				champ[i] = champ[i + 1];
				champ[i + 1] = tmp;
			}
			++i;
		}
		i = 0;
		--j;
	}
}

static void		check_chp_num_validity(t_parser *parser)
{
	uint8_t	i;
	uint8_t	highest_num;

	i = 0;
	highest_num = 0;
	if (parser->state == S_ERR)
		return ;
	while (i < 4)
	{
		if (highest_num < parser->env.champ[i].num)
			highest_num = parser->env.champ[i].num;
		++i;
	}
	if (highest_num > parser->cur_chp_index)
		parsing_error(parser, ERR_INVALID_CHAMP_NUM);
}

static void		end_of_arg_line(t_parser *parser)
{
	if (parser->state == S_DUMP)
		parsing_error(parser, ERR_INVALID_DUMP_NUM);
	else if (parser->state == S_CHP_NUM)
		parsing_error(parser, ERR_INVALID_CHAMP_NUM);
	else if (parser->state == S_VERB)
		parsing_error(parser, ERR_INVALID_VERB_NUM);
	else if (parser->state == S_VERB)
		parsing_error(parser, ERR_INVALID_VERB_NUM);
	else if (parser->state == S_CHAMP)
		parsing_error(parser, ERR_NO_CHP_AFTER_NUM);
	else if (parser->env.champ[0].num == 0 && parser->state != S_ERR)
		parsing_error(parser, ERR_NO_CHAMP);
	else if (parser->env.champ_amount > 4)
		parsing_error(parser, ERR_TOO_MUCH_CHAMP);
}

int8_t			vm_parser(t_parser *parser, char **av)
{
	t_parser			d_parser;
	static t_get_func	get_func[GET_F_NUM] = {get_opt, get_dump, get_chpnum,
														get_champ, get_verb};

	parser->env = init_vm();
	d_parser = *parser;
	while (d_parser.state != S_ERR && *av != NULL)
	{
		get_func[d_parser.state](&d_parser, av);
		++av;
	}
	end_of_arg_line(&d_parser);
	*parser = d_parser;
	check_chp_num_validity(parser);
	sort_champ_tab(parser, parser->env.champ, parser->cur_chp_index - 1);
	return (parser->state == S_OPTION ? SUCCESS : FAILURE);
}
