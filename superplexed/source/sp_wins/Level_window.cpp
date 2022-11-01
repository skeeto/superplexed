#include "Level_window.h"
#include "./../common/klib/klib_gfx.h"
#include "./../common/klib/klib_file.h"
#include "./../common/klib/klib_util.h"
#include "./../common/imgui/imgui.h"
#include "./../common/imgui/imgui_impl_sdl.h"
#include "./../common/imgui/imgui_impl_sdlrenderer.h"
#include "./../SP_Constants.h"
#include <algorithm>
#include <filesystem>

constexpr std::size_t TRANS_H_IDX{ 0 };
constexpr std::size_t TRANS_V_IDX{ 1 };
constexpr std::size_t TRANS_RC_IDX{ 2 };
constexpr std::size_t TRANS_RCC_IDX{ 3 };

void Level_window::save_file(SP_file_type p_ftype, SP_Config& p_config, const Project_gfx& p_gfx, bool p_all) const {
	int l_file_counter{ 0 };

	const auto ll_save_level = [*this](SP_file_type p_ftype, std::size_t p_level_no, const SP_Config& p_config, const Project_gfx& p_gfx) -> void {
		if (p_ftype == SP_file_type::xml)
			save_xml(p_level_no, p_config);
		else if (p_ftype == SP_file_type::sp)
			save_sp(p_level_no, p_config);
		else if (p_ftype == SP_file_type::bmp)
			p_gfx.save_level_bmp(m_levels.at(p_level_no),
				p_level_no, p_config, m_ui_animate);
		else
			throw std::exception("Invalid filetype");
	};

	for (std::size_t i{ p_all ? 0 : get_current_level_idx() };
		i < (p_all ? m_levels.size() : get_current_level_idx() + 1);
		++i) {
		try {
			ll_save_level(p_ftype, i, p_config, p_gfx);
			++l_file_counter;
		}
		catch (const std::exception& ex) {
			if (!p_all)
				p_config.add_message(ex.what());
		}
	}
	if (p_all)
		p_config.add_message("Saved " + std::to_string(l_file_counter) + " file(s)");
	else if (l_file_counter != 0) {
		std::size_t l_lvl_idx = get_current_level_idx();
		if (p_ftype == SP_file_type::bmp)
			p_config.add_message("Saved " + p_config.get_bmp_full_path(l_lvl_idx));
		else
			p_config.add_message("Saved " +
				(p_ftype == SP_file_type::xml ?
					p_config.get_xml_full_path(l_lvl_idx) :
					p_config.get_SP_full_path(l_lvl_idx))
			);
	}

}

void Level_window::load_file(SP_file_type p_ftype, SP_Config& p_config, bool p_all) {
	int l_file_counter{ 0 };

	const auto ll_load_level = [*this](SP_file_type p_ftype, std::size_t p_level_no, const SP_Config& p_config)->SP_Level {
		if (p_ftype == SP_file_type::xml)
			return load_xml(p_level_no, p_config);
		else if (p_ftype == SP_file_type::sp)
			return load_sp(p_level_no, p_config);
		else
			throw std::exception("Invalid filetype");
	};

	for (std::size_t i{ p_all ? 0 : get_current_level_idx() };
		i < (p_all ? m_levels.size() : get_current_level_idx() + 1);
		++i) {
		try {
			auto l_lvl = ll_load_level(p_ftype, i, p_config);

			m_levels.at(i) = l_lvl;
			++l_file_counter;
		}
		catch (const std::exception& ex) {
			if (!p_all)
				p_config.add_message(ex.what());
		}
	}
	if (p_all)
		p_config.add_message("Loaded " + std::to_string(l_file_counter) + " file(s)");
	else if (l_file_counter != 0)
		p_config.add_message("Loaded " +
			(p_ftype == SP_file_type::xml ?
				p_config.get_xml_full_path(get_current_level_idx()) :
				p_config.get_SP_full_path(get_current_level_idx()))
		);
}

void Level_window::save_levels_dat(SP_Config& p_config) {
	// generate LEVELS.DAT and LEVEL.LST
	std::vector<byte> l_file_bytes;
	std::vector<byte> l_list_file_bytes;

	for (std::size_t i{ 0 }; i < m_levels.size(); ++i) {
		auto l_lvl_bytes = m_levels[i].get_bytes();
		l_file_bytes.insert(end(l_file_bytes),
			begin(l_lvl_bytes), end(l_lvl_bytes));

		std::string l_line = klib::util::stringnum(i + 1) + ' ' + m_levels[i].get_title();

		l_list_file_bytes.insert(end(l_list_file_bytes),
			begin(l_line), end(l_line));
		l_list_file_bytes.push_back(13);
		l_list_file_bytes.push_back(10);
	}

	try {
		klib::file::write_bytes_to_file(l_list_file_bytes,
			p_config.get_level_lst_full_path());
		p_config.add_message("Wrote " + p_config.get_level_lst_full_path());
		klib::file::write_bytes_to_file(l_file_bytes,
			p_config.get_levels_dat_full_path());
		p_config.add_message("Wrote " + std::to_string(m_levels.size()) + " levels to " + p_config.get_levels_dat_full_path());
	}
	catch (const std::exception& ex) {
		p_config.add_message(ex.what());
	}
}

void Level_window::load_levels_dat(SP_Config& p_config) {
	try {
		std::vector<SP_Level> l_levels;
		auto l_bytes = klib::file::read_file_as_bytes(p_config.get_levels_dat_full_path());

		for (std::size_t i{ 0 }; i < l_bytes.size(); i += c::LVL_DATA_BYTE_SIZE)
			l_levels.push_back(SP_Level(std::vector<byte>(begin(l_bytes) + i, begin(l_bytes) + i + c::LVL_DATA_BYTE_SIZE)));

		m_levels = l_levels;
		p_config.add_message("Loaded " + std::to_string(m_levels.size()) + " levels from " + p_config.get_levels_dat_full_path());
		if (m_current_level > static_cast<int>(m_levels.size()))
			m_current_level = static_cast<int>(m_levels.size());
	}
	catch (const std::exception& ex) {
		p_config.add_message(ex.what());
		if (m_levels.empty()) {
			m_levels.push_back(SP_Level());
			p_config.add_message("Initialized with default level");
		}
	}
}

Level_window::Level_window(SDL_Renderer* p_rnd, SP_Config& p_config) :
	m_current_level{ 1 }, m_current_gp{ 1 }, m_cam_x{ 0 },
	m_ui_show_grid{ false }, m_ui_animate{ true }, m_ui_flash{ false },
	m_sel_x{ 0 }, m_sel_y{ 0 }, m_sel_x2{ -1 }, m_sel_y2{ 0 },
	m_sel_tile{ 0 }, m_tile_picker_scale{ 1.0f },
	m_show_stats{ -1 }, m_show_stats_tc0{ false }
{
	load_levels_dat(p_config);
	m_texture = SDL_CreateTexture(p_rnd, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, c::LEVEL_W * c::TILE_W, c::LEVEL_H * c::TILE_W);

	// initialize the tile picker
	m_tile_picker = {
		{"Basic Tiles", {c::TILE_NO_PLAYER_START, c::TILE_NO_EMPTY, c::TILE_NO_BASE, c::TILE_NO_INFOTRON, c::TILE_NO_WALL, c::TILE_NO_EXIT, c::TILE_NO_ZONK, c::TILE_NO_SNIKSNAK, c::TILE_NO_ELECTRON, c::TILE_NO_BUG}},
		{"Floppies", {c::TILE_NO_FLOPPY_O, c::TILE_NO_FLOPPY_Y, c::TILE_NO_FLOPPY_R, c::TILE_NO_TERMINAL}},
		{"Ports", {c::TILE_NO_PORT_RIGHT, c::TILE_NO_PORT_DOWN, c::TILE_NO_PORT_LEFT, c::TILE_NO_PORT_UP, c::TILE_NO_PORT2WAY_V, c::TILE_NO_PORT2WAY_H, c::TILE_NO_PORT4WAY}},
		{"RAM Chips", {c::TILE_NO_RAMCHIP,c::TILE_NO_RAM_LEFT, c::TILE_NO_RAM_RIGHT, c::TILE_NO_RAM_TOP, c::TILE_NO_RAM_BOTTOM}},
		{"Decoration", {c::TILE_NO_HW01,c::TILE_NO_HW02,c::TILE_NO_HW03,c::TILE_NO_HW04,c::TILE_NO_HW05,c::TILE_NO_HW06,c::TILE_NO_HW07,c::TILE_NO_HW08,c::TILE_NO_HW09,c::TILE_NO_HW10, c::TILE_NO_MURPHY}},
		{"Special Ports", {c::TILE_NO_GP_RIGHT, c::TILE_NO_GP_DOWN, c::TILE_NO_GP_LEFT, c::TILE_NO_GP_UP}}
	};

	// initalize timers
	m_timers = {
		klib::Timer(6, 250),			// tile animations
		klib::Timer(255, 5, true),		// pulsating colors
		klib::Timer(3, 1000, false),	// pulsating letter
	};

	// initialize transforms
	// map: from tile -> to tile, under the given transform
	m_transforms = {
		// flip in the x-direction
		{{c::TILE_NO_PORT_LEFT, c::TILE_NO_PORT_RIGHT},
		{c::TILE_NO_PORT_RIGHT, c::TILE_NO_PORT_LEFT},
		{c::TILE_NO_GP_LEFT, c::TILE_NO_GP_RIGHT},
		{c::TILE_NO_GP_RIGHT, c::TILE_NO_GP_LEFT}},
		// flips in the y-direction
		{{c::TILE_NO_PORT_UP, c::TILE_NO_PORT_DOWN},
		{c::TILE_NO_PORT_DOWN, c::TILE_NO_PORT_UP},
		{c::TILE_NO_GP_UP, c::TILE_NO_GP_DOWN},
		{c::TILE_NO_GP_DOWN, c::TILE_NO_GP_UP}},
		// clockwise rotations
		{{c::TILE_NO_PORT_RIGHT,c::TILE_NO_PORT_DOWN},
		{c::TILE_NO_PORT_DOWN,c::TILE_NO_PORT_LEFT},
		{c::TILE_NO_PORT_LEFT,c::TILE_NO_PORT_UP},
		{c::TILE_NO_PORT_UP,c::TILE_NO_PORT_RIGHT},
		{c::TILE_NO_GP_RIGHT,c::TILE_NO_GP_DOWN},
		{c::TILE_NO_GP_DOWN,c::TILE_NO_GP_LEFT},
		{c::TILE_NO_GP_LEFT,c::TILE_NO_GP_UP},
		{c::TILE_NO_GP_UP,c::TILE_NO_GP_RIGHT},
		{c::TILE_NO_PORT2WAY_H, c::TILE_NO_PORT2WAY_V},
		{c::TILE_NO_PORT2WAY_V, c::TILE_NO_PORT2WAY_H}}
	};
	// finally generate transform for counter-clockwise rotation
	std::map<byte, byte> l_cc_transforms;
	for (const auto& kv : m_transforms.at(TRANS_RC_IDX))
		l_cc_transforms.insert(std::make_pair(kv.second, kv.first));
	m_transforms.push_back(l_cc_transforms);
}

void Level_window::move(int p_delta_ms, const klib::User_input& p_input, SP_Config& p_config, int p_w, int p_h) {
	bool l_shift = p_input.is_shift_pressed();
	bool l_ctrl = p_input.is_ctrl_pressed();

	for (auto& timer : m_timers)
		timer.move(p_delta_ms);

	// handle keyboard
	if (!ImGui::GetIO().WantCaptureKeyboard) {
		if (p_input.is_pressed(SDL_SCANCODE_DELETE))
			delete_selection();
		else if (l_ctrl && p_input.is_pressed(SDL_SCANCODE_C))
			copy_to_clipboard();
		else if (l_ctrl && p_input.is_pressed(SDL_SCANCODE_V)) {
			if (selection_fits())
				paste_from_clipboard();
		}
		else if (l_ctrl && p_input.is_pressed(SDL_SCANCODE_X))
			cut_selection();
		else if (p_input.is_pressed(SDL_SCANCODE_F))
			flip_selection(l_shift);
		else if (l_ctrl && p_input.is_pressed(SDL_SCANCODE_A))
			select_all();
		else if (l_shift && p_input.is_pressed(SDL_SCANCODE_V))
			show_clipboard_destination();
		else if (p_input.is_pressed(SDL_SCANCODE_R))
			rotate_selection(l_shift, p_config);
		else if (p_input.is_pressed(SDL_SCANCODE_TAB)) {
			int l_gp_count = m_levels.at(get_current_level_idx()).get_gravity_port_count();
			m_current_gp += (l_shift ? -1 : 1);
			if (m_current_gp <= 0)
				m_current_gp = l_gp_count;
			else if (m_current_gp > l_gp_count)
				m_current_gp = 1;
		}
	}

	// handle mouse
	if (!ImGui::GetIO().WantCaptureMouse) {

		if (p_input.mouse_held()) {
			auto tcoords = mouse_coords_to_tile(p_input.mx(), p_input.my(), p_h);

			if (l_ctrl) {
				m_sel_tile = m_levels.at(get_current_level_idx()).get_tile_no(tcoords.first, tcoords.second);
			}
			if (!l_ctrl && l_shift) {
				m_sel_x2 = tcoords.first;
				m_sel_y2 = tcoords.second;
			}
			else if (p_input.is_pressed(SDL_SCANCODE_G) &&
				m_levels.at(get_current_level_idx()).get_gravity_port_count() > 0) {
				m_levels.at(get_current_level_idx()).set_gp_x(m_current_gp - 1, tcoords.first);
				m_levels.at(get_current_level_idx()).set_gp_y(m_current_gp - 1, tcoords.second);
			}
			else {
				clear_selection();
				m_sel_x = tcoords.first;
				m_sel_y = tcoords.second;

				// select a special port if one was clicked
				int l_gp_no{ m_levels.at(get_current_level_idx()).has_gp_at_pos(m_sel_x, m_sel_y) };
				if (l_gp_no > -1)
					m_current_gp = l_gp_no + 1;
			}
		}
		else if (p_input.mouse_held(false)) {
			auto tcoords = mouse_coords_to_tile(p_input.mx(), p_input.my(), p_h);
			if (m_sel_tile == c::TILE_NO_PLAYER_START)
				m_levels.at(get_current_level_idx()).set_player_start(tcoords.first, tcoords.second);
			else {
				m_levels.at(get_current_level_idx()).set_tile_value(tcoords.first, tcoords.second, m_sel_tile);
				if (m_sel_tile >= c::TILE_NO_GP_RIGHT &&
					m_sel_tile <= c::TILE_NO_GP_UP &&
					m_levels.at(get_current_level_idx()).has_gp_at_pos(tcoords.first, tcoords.second) == -1 &&
					m_levels.at(get_current_level_idx()).get_gravity_port_count() < c::MAX_GP_COUNT)
					m_levels.at(get_current_level_idx()).add_gravity_port(tcoords.first, tcoords.second);
			}
		}
		else if (p_input.mw_down()) {
			if (l_shift && get_current_level_idx() > 0)
				--m_current_level;
			else if (!l_shift && m_cam_x > 0)
				--m_cam_x;
		}
		else if (p_input.mw_up()) {
			if (l_shift && get_current_level_idx() < m_levels.size() - 1)
				++m_current_level;
			else if (!l_shift && m_cam_x < 40)
				++m_cam_x;
		}

	}
}

void Level_window::draw(SDL_Renderer* p_rnd, const Project_gfx& p_gfx, int p_w, int p_h) {
	regenerate_texture(p_rnd, p_gfx);

	// get tile pixel width
	int l_tpw = std::max(1, get_tile_pixel_w(p_h));
	// get screen tile widht
	int l_stw = p_w / l_tpw + 1;
	// get rest tile count
	int l_stw_tc = std::min<int>(60 - m_cam_x, l_stw);

	klib::gfx::blit_full_spec(p_rnd, m_texture,
		0, 0, l_stw_tc * l_tpw, p_h,
		c::TILE_W * static_cast<int>(m_cam_x), 0, c::TILE_W * l_stw_tc, c::TILE_W * c::LEVEL_H);
}

void Level_window::regenerate_texture(SDL_Renderer* p_rnd, const Project_gfx& p_gfx) {
	SDL_SetRenderTarget(p_rnd, m_texture);
	SDL_SetRenderDrawColor(p_rnd, 0, 0, 0, 0);
	SDL_RenderClear(p_rnd);

	int l_atime = m_timers[0].get_frame();
	int l_ltime = m_timers[2].get_frame();

	// calculate pulsating colors for this frame
	float l_pulse_progress = static_cast<float>(m_timers[1].get_frame()) / 255.0f;
	std::vector<SDL_Color> l_pulse_colors;
	l_pulse_colors.push_back(klib::gfx::pulse_color(Project_gfx::sp_col_to_sdl(c::COL_RED_DARK), Project_gfx::sp_col_to_sdl(c::COL_RED), l_pulse_progress));  // gravity port property turned off
	l_pulse_colors.push_back(klib::gfx::pulse_color(Project_gfx::sp_col_to_sdl(c::COL_ORANGE), Project_gfx::sp_col_to_sdl(c::COL_RED), l_pulse_progress));      // gravity port property not ok
	l_pulse_colors.push_back(klib::gfx::pulse_color(Project_gfx::sp_col_to_sdl(c::COL_YELLOW), Project_gfx::sp_col_to_sdl(c::COL_ORANGE), l_pulse_progress));        // selection rectangle
	l_pulse_colors.push_back(klib::gfx::pulse_color(Project_gfx::sp_col_to_sdl(c::COL_BLUE_LIGHT), Project_gfx::sp_col_to_sdl(c::COL_BLUE), l_pulse_progress));      // selected gravity port outline
	l_pulse_colors.push_back(klib::gfx::pulse_color(Project_gfx::sp_col_to_sdl(c::COL_GREEN), Project_gfx::sp_col_to_sdl(c::COL_GREEN_LIGHT), l_pulse_progress));      // gravity port property turned on

	for (int i = 0; i < 60; ++i)
		for (int j = 0; j < 24; ++j) {
			byte l_tile_no = m_levels.at(get_current_level_idx()).get_tile_no(i, j);
			klib::gfx::blit(p_rnd,
				p_gfx.get_tile_texture(l_tile_no, m_ui_animate ? l_atime : 0),
				i * c::TILE_W, j * c::TILE_W);

			if (static_cast<byte>(m_sel_tile) == l_tile_no && m_ui_flash) {
				p_gfx.blit_fixed(p_rnd, 4, i * c::TILE_W, j * c::TILE_W,
					l_pulse_colors[4]);
			}
		}

	auto l_spos = m_levels.at(get_current_level_idx()).get_start_pos();
	klib::gfx::blit(p_rnd, p_gfx.get_tile_texture(40, m_ui_animate ? l_atime : 0),
		c::TILE_W * l_spos.first, c::TILE_W * l_spos.second);

	SDL_SetRenderDrawColor(p_rnd, 0, 0, 0, 0);

	if (m_ui_show_grid) {
		for (int i{ 1 }; i < c::LEVEL_W; ++i)
			SDL_RenderDrawLine(p_rnd, i * c::TILE_W, 0, i * c::TILE_W, c::LEVEL_H * c::TILE_W);
		for (int i{ 1 }; i < c::LEVEL_H; ++i)
			SDL_RenderDrawLine(p_rnd, 0, i * c::TILE_W, c::LEVEL_W * c::TILE_W, i * c::TILE_W);
	}

	int l_letter_ind = m_timers[2].get_frame();

	for (int i{ 0 }; i < m_levels.at(get_current_level_idx()).get_gravity_port_count(); ++i) {
		int l_x = c::TILE_W * m_levels.at(get_current_level_idx()).get_gp_x(i);
		int l_y = c::TILE_W * m_levels.at(get_current_level_idx()).get_gp_y(i);
		bool l_gp_grav = m_levels.at(get_current_level_idx()).get_gp_gravity(i);
		bool l_gp_fz = m_levels.at(get_current_level_idx()).get_gp_freeze_zonks(i);
		bool l_gp_fe = m_levels.at(get_current_level_idx()).get_gp_freeze_enemies(i);

		bool l_port_ok = m_levels.at(get_current_level_idx()).get_gp_status(i);

		if (i == m_current_gp - 1)
			klib::gfx::draw_rect(p_rnd, l_x, l_y, c::TILE_W, c::TILE_W,
				l_pulse_colors[3],
				1);

		if (l_port_ok) {
			bool l_property_on = ((l_ltime == 0 && l_gp_grav) || (l_ltime == 1 && l_gp_fz) || (l_ltime == 2 && l_gp_fe));

			p_gfx.blit_fixed(p_rnd, l_letter_ind, l_x, l_y, l_pulse_colors[l_property_on ? 4 : 0]);
		}
		else {
			p_gfx.blit_fixed(p_rnd, 3, l_x, l_y, l_pulse_colors[1]);
		}
	}

	auto l_rect = this->get_selection_rectangle();
	klib::gfx::draw_rect(p_rnd, c::TILE_W * l_rect.x, c::TILE_W * l_rect.y, c::TILE_W * (l_rect.w + 1), c::TILE_W * (l_rect.h + 1),
		l_pulse_colors[2],
		3);

	SDL_SetRenderTarget(p_rnd, nullptr);
}

int Level_window::get_tile_pixel_w(int p_screen_pixel_h) const {
	return static_cast<int>(static_cast<float>(p_screen_pixel_h) / 24.0f);
}

std::size_t Level_window::get_current_level_idx(void) const {
	return static_cast<std::size_t>(m_current_level) - 1;
}

// selections
bool Level_window::has_selection(void) const {
	return (m_sel_x2 != -1);
}

void Level_window::clear_selection(void) {
	m_sel_x2 = -1;
}

SDL_Rect Level_window::get_selection_rectangle(void) const {
	if (has_selection()) {
		int l_x = std::min(m_sel_x, m_sel_x2);
		int l_y = std::min(m_sel_y, m_sel_y2);
		int l_w = std::max(m_sel_x2, m_sel_x) - l_x;
		int l_h = std::max(m_sel_y2, m_sel_y) - l_y;

		return SDL_Rect{ l_x, l_y, l_w, l_h };
	}
	else
		return SDL_Rect{ m_sel_x, m_sel_y, 0, 0 };
}

bool Level_window::is_selection_empty(void) const {
	auto l_rect = get_selection_rectangle();

	for (int j{ l_rect.y }; j <= l_rect.y + l_rect.h; ++j)
		for (int i{ l_rect.x }; i <= l_rect.x + l_rect.w; ++i)
			if (m_levels.at(get_current_level_idx()).get_tile_no(i, j) != 0)
				return false;

	return true;
}

byte Level_window::apply_transform(byte p_byte, std::size_t p_transform_type) const {
	auto iter = m_transforms[p_transform_type].find(p_byte);
	return (iter != end(m_transforms[p_transform_type]) ?
		iter->second : p_byte);
}

void Level_window::flip_selection(bool p_vertical) {
	auto l_rect = get_selection_rectangle();

	// vertical flip
	if (p_vertical) {
		for (int j{ 0 }; j <= l_rect.w; ++j)
			for (int i{ 0 }; i <= l_rect.h / 2; ++i) {
				byte l_tmp = m_levels.at(get_current_level_idx()).get_tile_no(l_rect.x + j, l_rect.y + i);
				m_levels.at(get_current_level_idx()).set_tile_value(l_rect.x + j, l_rect.y + i,
					m_levels.at(get_current_level_idx()).get_tile_no(l_rect.x + j, l_rect.y + l_rect.h - i));
				m_levels.at(get_current_level_idx()).set_tile_value(l_rect.x + j, l_rect.y + l_rect.h - i, l_tmp);
			}
	}
	// horizontal flip
	else {
		for (int j{ 0 }; j <= l_rect.w / 2; ++j)
			for (int i{ 0 }; i <= l_rect.h; ++i) {
				byte l_tmp = m_levels.at(get_current_level_idx()).get_tile_no(l_rect.x + j, l_rect.y + i);
				m_levels.at(get_current_level_idx()).set_tile_value(l_rect.x + j, l_rect.y + i,
					m_levels.at(get_current_level_idx()).get_tile_no(l_rect.x + l_rect.w - j, l_rect.y + i));
				m_levels.at(get_current_level_idx()).set_tile_value(l_rect.x + l_rect.w - j, l_rect.y + i, l_tmp);
			}
	}

	for (int i{ 0 }; i <= l_rect.w; ++i)
		for (int j{ 0 }; j <= l_rect.h; ++j)
			m_levels.at(get_current_level_idx()).set_tile_value(l_rect.x + i, l_rect.y + j,
				apply_transform(m_levels.at(get_current_level_idx()).get_tile_no(l_rect.x + i, l_rect.y + j),
					p_vertical ? TRANS_V_IDX : TRANS_H_IDX)
			);
}

void Level_window::select_all(void) {
	m_sel_x = 0;
	m_sel_y = 0;
	m_sel_x2 = 59;
	m_sel_y2 = 23;
}

void Level_window::show_clipboard_destination(void) {
	if (!m_clipboard.empty() && selection_fits()) {
		m_sel_x2 = m_sel_x + static_cast<int>(m_clipboard[0].size()) - 1;
		m_sel_y2 = m_sel_y + static_cast<int>(m_clipboard.size()) - 1;
	}
}

bool Level_window::selection_fits(void) const {
	return (m_sel_y + m_clipboard.size() <= 24) && (m_clipboard.size() == 0 || (m_sel_x + m_clipboard[0].size() <= 60));
}

void Level_window::copy_to_clipboard(void) {
	auto l_rect = get_selection_rectangle();
	m_clipboard.clear();

	for (int j{ l_rect.y }; j <= l_rect.y + l_rect.h; ++j) {
		std::vector<byte> l_row;
		for (int i{ l_rect.x }; i <= l_rect.x + l_rect.w; ++i)
			l_row.push_back(m_levels.at(get_current_level_idx()).get_tile_no(i, j));
		m_clipboard.push_back(l_row);
	}

}

void Level_window::paste_from_clipboard(void) {
	for (int j{ 0 }; j < m_clipboard.size(); ++j)
		for (int i{ 0 }; i < m_clipboard.at(j).size(); ++i)
			m_levels.at(get_current_level_idx()).set_tile_value(
				m_sel_x + i, m_sel_y + j, m_clipboard[j][i]);
}

void Level_window::delete_selection(void) {
	auto l_rect = get_selection_rectangle();

	for (int j{ l_rect.y }; j <= l_rect.y + l_rect.h; ++j)
		for (int i{ l_rect.x }; i <= l_rect.x + l_rect.w; ++i)
			m_levels.at(get_current_level_idx()).set_tile_value(i, j, 0);
}

void Level_window::cut_selection(void) {
	if (!is_selection_empty()) {
		copy_to_clipboard();
		delete_selection();
	}
}

void Level_window::rotate_selection(bool p_cclockwise, SP_Config& p_config) {
	if (m_clipboard.empty()) {
		p_config.add_message("Clipboard is empty, no rotation possible");
		return;
	}

	std::vector<std::vector<byte>> result;

	if (p_cclockwise) {
		for (int j{ static_cast<int>(m_clipboard[0].size()) - 1 }; j >= 0; --j) {
			std::vector<byte> l_row;
			for (int i{ 0 }; i < m_clipboard.size(); ++i) {
				l_row.push_back(m_clipboard[i][j]);
			}
			result.push_back(l_row);
		}
		p_config.add_message("Clipboard rotated counter-clockwise");
	}
	else {
		for (int j{ 0 }; j < static_cast<int>(m_clipboard[0].size()); ++j) {
			std::vector<byte> l_row;
			for (int i{ 0 }; i < m_clipboard.size(); ++i) {
				l_row.push_back(m_clipboard[static_cast<std::size_t>(m_clipboard.size() - i - 1)][j]);
			}
			result.push_back(l_row);
		}
		p_config.add_message("Clipboard rotated clockwise");
	}

	for (std::size_t y{ 0 }; y < result.size(); ++y)
		for (std::size_t x{ 0 }; x < result[y].size(); ++x)
			result[y][x] = apply_transform(result[y][x],
				p_cclockwise ? TRANS_RCC_IDX : TRANS_RC_IDX);

	m_clipboard = result;
}

std::pair<int, int> Level_window::mouse_coords_to_tile(int p_mouse_x, int p_mouse_y, int p_screen_h) const {
	int l_tpw = get_tile_pixel_w(p_screen_h);

	int l_tx = m_cam_x + p_mouse_x / l_tpw;
	int l_ty = p_mouse_y / l_tpw;

	return std::make_pair(
		klib::util::validate(l_tx, 0, 59),
		klib::util::validate(l_ty, 0, 23)
	);
}

std::vector<int> Level_window::get_tile_counts(bool p_all_levels) const {
	if (p_all_levels) {
		std::vector<int> result(c::TILE_COUNT, 0);
		for (std::size_t i{ 0 }; i < m_levels.size(); ++i) {
			auto l_lvl_counts = m_levels[i].get_tile_counts();
			for (std::size_t j{ 0 }; j < l_lvl_counts.size(); ++j)
				result[j] += l_lvl_counts[j];
		}
		return result;
	}
	else
		return m_levels.at(get_current_level_idx()).get_tile_counts();

}

// SP load/save
SP_Level Level_window::load_sp(std::size_t p_level_no, const SP_Config& p_config) const {
	return SP_Level(klib::file::read_file_as_bytes(p_config.get_SP_full_path(p_level_no)));
}

void Level_window::save_sp(std::size_t p_level_no, const SP_Config& p_config) const {
	std::filesystem::create_directory(p_config.get_SP_folder());
	klib::file::write_bytes_to_file(m_levels.at(p_level_no).get_bytes(true),
		p_config.get_SP_full_path(p_level_no));
}
