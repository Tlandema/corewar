#include "visualisator.h"

void draw_rectangle(t_window *win, SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);

	// SDL_Rect rect = {
	// 	static_cast<int>(pos.x), static_cast<int>(pos.y),
	// 	static_cast<int>(size.x), static_cast<int>(size.y)};

	SDL_RenderFillRect(win->renderer, &rect);
}

void draw_centred_rectangle(t_window *win, SDL_Rect rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);

	SDL_Rect tmp_rect = {
		rect.x - rect.w / 2, rect.y - rect.h / 2,
		rect.w, rect.h};

	SDL_RenderFillRect(win->renderer, &tmp_rect);
}

void draw_border_rectangle(t_window *win, SDL_Rect rect, SDL_Color color_back, SDL_Color color_front, int border)
{
	draw_rectangle(win, rect, color_back);

	SDL_Rect tmp_rect = {
		rect.x + border, rect.y + border,
		rect.w - border * 2, rect.h - border * 2};

	draw_rectangle(win, tmp_rect, color_front);
}

void draw_centred_border_rectangle(t_window *win, SDL_Rect rect, SDL_Color color_back, SDL_Color color_front, int border)
{
	draw_centred_rectangle(win, rect, color_back);

	SDL_Rect tmp_rect = {
		rect.x, rect.y,
		rect.w - border * 2, rect.h - border * 2};

	draw_centred_rectangle(win, tmp_rect, color_front);
}
