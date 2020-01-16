/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armoulin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:10:13 by armoulin          #+#    #+#             */
/*   Updated: 2019/10/11 17:08:31 by armoulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** Transform '*.s' in '*.cor'.
*/
static char		*get_name(char *title, t_asm *asmr)
{
	char 	*name;
	size_t	length;

	length = ft_strlen(title);
	if (title[length - 1] != 's' || title[length - 2] != '.')
		exit_msg(ERROR_FILE_NAME, NULL, NULL, asmr);
	if (!(name = ft_strnew(length + 2)))
		exit_msg(ERROR_MALLOC, NULL, NULL, asmr);
	ft_strcpy(name, title);
	name[length - 1] = 'c';
	name[length] = 'o';
	name[length + 1] = 'r';
	return (name);
}

/*
** Create (or open if exist) the file:
**	- O_WRONLY 	--> Write only.
**	- O_TRUNC	--> If file exist, erase and start fresh.
**	- O_CREAT	--> If file doesn't exist, create it.
**	- 00755		--> Same as: chmod 755.
*/
static int32_t	open_file(t_asm *asmr, char *file)
{
	int32_t	fd;
	char 	*name;

	name = get_name(file, asmr);
	if ((fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 00755)) < 0)
	{
		free(name);
		exit_msg(ERROR_FILE_OPEN, file, NULL, asmr);
	}
	free(name);
	return (fd);
}

/*
** Couldn't directly read and write the maximum bytes for champion's name,
** as if name doesn't fill all memory, it could be corrupted.
** So write until first '\0' then fill ourself.
** Precisly, we fill to 129 (max = 128 + 1 for '\0'), then we add 3 more
** blanks bytes because the memory works with group of 4 bytes.
** (128 % 4 = 0 ; 129 % 4 = 1 ; 132 % 4 = 0)
*/
static void		write_magic_name_size(t_asm *asmr, int32_t fd)
{
	size_t	name_size;
	size_t	i;
	char	c;

	write_nb_4(asmr, fd, (int32_t)asmr->header.magic);
	c = '\0';
	name_size = ft_strlen(asmr->header.prog_name);
	if (write(fd, asmr->header.prog_name, name_size) != (int)name_size)
		exit_msg(ERROR_FILE_WRITE, NULL, NULL, asmr);
	i = PROG_NAME_LENGTH - name_size + 4;
	while (i--)
		if (write(fd, &c, 1) != 1)
			exit_msg(ERROR_FILE_WRITE, NULL, NULL, asmr);
	write_nb_4(asmr, fd, (int32_t)asmr->header.prog_size);
}

/*
** Same remark as previous function.
*/
static void		write_comment(t_asm *asmr, int32_t fd)
{
	size_t	comment_size;
	size_t	i;
	char	c;

	c = '\0';
	comment_size = ft_strlen(asmr->header.comment);
	if (write(fd, asmr->header.comment, comment_size) != (int)comment_size)
			exit_msg(ERROR_FILE_WRITE, NULL, NULL, asmr);
	i = COMMENT_LENGTH - comment_size + 4;
	while (i--)
		if (write(fd, &c, 1) != 1)
			exit_msg(ERROR_FILE_WRITE, NULL, NULL, asmr);	
}

/*
** - Write the opcode on 1 byte.
** - If needed, write the param byte on byte.
** - Write the value of each parameter.
*/
static void		write_cmd(t_asm *asmr, int32_t fd, t_cmd *cmd)
{
	int i;

	write_nb_1(asmr, fd, cmd->op_code);
	if (asmr->op_tab[cmd->op_code - 1].have_param_byte)
		write_param_byte(asmr, fd, cmd);
	i = 0;
	while (i < cmd->nb_param)
		write_param(asmr, fd, &(cmd->params[i++]), cmd->op_code);
}

void			write_file(t_asm *asmr, char *title)
{
	int32_t	fd;
	t_cmd	*list;
	
	fd = open_file(asmr, title);
	write_magic_name_size(asmr, fd);
	write_comment(asmr, fd);
	list = asmr->list;
	while (list)
	{
		write_cmd(asmr, fd, list);
		list = list->next;
	}
}