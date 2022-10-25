#ifndef SP_LEVEL_WINDOW_H
#define SP_LEVEL_WINDOW_H

#include <SDL.h>
#include <string>
#include <utility>
#include <vector>
#include "./../sp_levels/SP_Level.h"
#include "./../sp_gfx/Project_gfx.h"
#include "./../common/klib/User_input.h"
#include "./../common/klib/Timer.h"

class Level_window {

	std::vector<SP_Level> m_levels;
	int m_cam_x, m_current_level, m_current_gp, m_sel_tile;
	SDL_Texture* m_texture;
	bool m_ui_show_grid, m_ui_animate;
	klib::Timer m_timer;
	std::vector<std::pair<std::string, std::vector<int>>> m_tile_picker;

	// selection
	int m_sel_x, m_sel_y,
		m_sel_x2, m_sel_y2;
	std::vector<std::vector<byte>> m_clipboard;

	int get_tile_pixel_w(int p_screen_pixel_h) const;
	void regenerate_texture(SDL_Renderer* p_rnd, const Project_gfx& p_gfx);
	std::size_t get_current_level_idx(void) const;

	// selection procedures and functions
	bool has_selection(void) const;
	void clear_selection(void);
	void copy_to_clipboard(void);
	void paste_from_clipboard(void);
	void delete_selection(void);
	void cut_selection(void);
	SDL_Rect get_selection_rectangle(void) const;
	bool is_selection_empty(void) const;
	void flip_selection(bool p_vertical);
	void select_all(void);
	void show_clipboard_destination(void);
	bool selection_fits(void) const;
	void rotate_selection(bool p_clockwise);
	std::pair<int, int> mouse_coords_to_tile(int p_mouse_x, int p_mouse_y, int p_screen_h) const;

	// xml read/write
	void save_xml(std::size_t p_level_no) const;
	std::string get_level_xml_filename(std::size_t p_level_no) const;
	SP_Level load_xml(std::size_t p_level_no) const;

public:
	Level_window(SDL_Renderer* p_rnd);
	void move(int p_delta_ms, const klib::User_input& p_input, int p_w, int p_h);
	void draw(SDL_Renderer* p_rnd, const Project_gfx& p_gfx, int p_w, int p_h);
	void draw_ui(const Project_gfx& p_gfx);
	void draw_ui_level_win(void);
	void draw_ui_gp_win(void);
	void draw_ui_tile_win(const Project_gfx& p_gfx);
};

#endif
