/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualisator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlandema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:08:18 by tlandema          #+#    #+#             */
/*   Updated: 2019/11/07 11:45:10 by tlandema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#define FONT_PATH "vm/ressources/font/Tinos-Regular.ttf"
#define NB_SIZE			150
#define NB_COLOR		26
#define NB_STYLE		5
#define BLACK			0
#define WHITE			1
#define LIGHT_BLUE		2
#define BLUE			3
#define DARK_BLUE		4
#define LIGHT_RED		5
#define RED				6
#define DARK_RED		7
#define LIGHT_GREEN		8
#define GREEN			9
#define DARK_GREEN		10
#define LIGHT_CYAN		11
#define CYAN			12
#define DARK_CYAN		13
#define LIGHT_GREY		14
#define GREY			15
#define DARK_GREY		16
#define LIGHT_ORANGE	17
#define ORANGE			18
#define DARK_ORANGE		19
#define LIGHT_YELLOW	20
#define YELLOW			21
#define DARK_YELLOW		22
#define TEXT2			23
#define BORDER			24
#define TEXT			25

#define NORMAL TTF_STYLE_NORMAL
#define BOLD TTF_STYLE_BOLD
#define ITALIC TTF_STYLE_ITALIC
#define UNDERLINE TTF_STYLE_UNDERLINE
#define STRICK TTF_STYLE_STRIKETHROUGH

/*
**	--------WINDOW FUNCTIONS----------------------------------------------------
*/
t_window 			*open_window(char *name);
void 				clear(t_window *win);
void				render(t_window *win);
int8_t				drawer(t_window *win, t_vm *env);

/*
**	--------OBJECT CREATION FUNCTIONS-------------------------------------------
*/
SDL_Rect			create_rect(int x, int y, int w, int h);
SDL_Color			create_color(int r, int g, int b, int a);
SDL_Point			create_point(int x, int y);
int					*create_tab_int3(int size, int color, int style);
t_image				load_t_image(t_window *win, SDL_Surface *p_surface);
t_image				*malloc_t_image(t_window *win, SDL_Surface *p_surface);
t_image				load_t_image_from_file(t_window *win, char *path);

/*
**--------DRAWING FUNCTIONS---------------------------------------------------
*/
int8_t				draw_image(t_window *win, t_image *image, SDL_Rect dest);
int8_t				draw_rectangle(t_window *win, SDL_Rect rect, SDL_Color color);
int8_t				draw_centred_rectangle(t_window *win, SDL_Rect rect, SDL_Color color);
int8_t				draw_border_rectangle(t_window *win, t_brect *infos,
					int border);
int8_t				draw_centred_border_rectangle(t_window *win, t_brect *infos,
					int border);
int					draw_text(t_window *win, char *str, SDL_Point pos,
					int infos[3]);
int					draw_centred_text(t_window *win, char *str, SDL_Point pos,
					int infos[3]);
int8_t              draw_arena(t_window *win, t_vm *env);

#endif