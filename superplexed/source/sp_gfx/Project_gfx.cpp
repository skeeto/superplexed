#include "Project_gfx.h"
#include "./../common/klib/klib_gfx.h"
#include "./../common/klib/klib_file.h"
#include <tuple>

using byte = unsigned char;

SDL_Texture* Project_gfx::get_static(std::size_t p_texture_no) const {
	return m_static.at(p_texture_no);
}

SDL_Texture* Project_gfx::get_animated(std::size_t p_texture_no, std::size_t p_frame_no) const {
	if (m_animations.find(p_texture_no) != end(m_animations))
		return m_moving[m_animations.at(p_texture_no).at(p_frame_no)];
	else
		return get_static(p_texture_no);
}

Project_gfx::~Project_gfx(void) {
	for (auto texture : m_static)
		if (texture != nullptr)
			SDL_DestroyTexture(texture);

	for (auto texture : m_moving)
		if (texture != nullptr)
			SDL_DestroyTexture(texture);

	for (auto texture : m_font)
		if (texture != nullptr)
			SDL_DestroyTexture(texture);
}

void Project_gfx::blit_font(SDL_Renderer* p_rnd, std::size_t p_char_no, int p_x, int p_y, int p_w, int p_h, SDL_Color p_color) const {
	SDL_Texture* l_letter = m_font.at(p_char_no);
	SDL_SetTextureColorMod(l_letter, p_color.r, p_color.g, p_color.b);
	klib::gfx::blit_scale(p_rnd, l_letter, p_x, p_y, p_w, p_h);
}

bool Project_gfx::load_image_data_from_file(const std::string& p_filename, const SP_Config& p_config) {
	try {
		m_image_files.insert(std::make_pair(p_filename,
			SP_Image(klib::file::read_file_as_bytes(p_config.get_dat_full_path(p_filename)),
				m_image_metadata.at(p_filename).m_width,
				m_image_metadata.at(p_filename).m_binary)));
	}
	catch (const std::exception&) {
		return false;
	}

	return true;
}

Project_gfx::Project_gfx(SDL_Renderer* p_rnd, const SP_Config& p_config) {
	// initialize image metadata
	m_image_metadata.insert(std::make_pair("BACK", Gfx_metadata(320, 0)));
	m_image_metadata.insert(std::make_pair("CONTROLS", Gfx_metadata(320, 1)));
	m_image_metadata.insert(std::make_pair("CHARS6", Gfx_metadata(512, 4, true)));
	m_image_metadata.insert(std::make_pair("CHARS8", Gfx_metadata(512, 4, true)));
	m_image_metadata.insert(std::make_pair("FIXED", Gfx_metadata(640, 1)));
	m_image_metadata.insert(std::make_pair("GFX", Gfx_metadata(320, 1)));
	m_image_metadata.insert(std::make_pair("MENU", Gfx_metadata(320, 1)));
	m_image_metadata.insert(std::make_pair("MOVING", Gfx_metadata(320, 1)));
	m_image_metadata.insert(std::make_pair("PANEL", Gfx_metadata(320, 1)));
	m_image_metadata.insert(std::make_pair("TITLE", Gfx_metadata(320, 5)));
	m_image_metadata.insert(std::make_pair("TITLE1", Gfx_metadata(320, 6)));
	m_image_metadata.insert(std::make_pair("TITLE2", Gfx_metadata(320, 7)));

	// ***** read palette data *****
	// palette 0: bluescale (BLUE.DAT)
	// palette 1: game objects and screens (apart from the title-screens and fonts)
	// palette 2: ???
	// palette 3: ???
	std::vector<byte> l_bytes = klib::file::read_file_as_bytes(p_config.get_dat_full_path("PALETTES"));
	for (std::size_t i{ 0 }; i < 4; ++i)
		m_palettes.push_back(SP_Palette(std::vector<byte>(begin(l_bytes) + i * 4 * 16,
			begin(l_bytes) + (i + 1) * 4 * 16)));

	// ***** add hardcoded palettes that do not come from a file *****
	// palette for CHARS6 and CHARS8 (monochrome)
	m_palettes.push_back(SP_Palette({
		0xf,0x7,0xb,0x0, 0xf,0xf,0xf,0xf
		}));
	// palette for TITLE
	m_palettes.push_back(SP_Palette({
	0x02, 0x03, 0x05, 0x00, 0x0D, 0x0A, 0x04, 0x0C, 0x02, 0x06, 0x06, 0x02, 0x03, 0x09, 0x09, 0x03,
	0x0B, 0x08, 0x03, 0x06, 0x02, 0x07, 0x07, 0x0A, 0x08, 0x06, 0x0D, 0x09, 0x06, 0x04, 0x0B, 0x01,
	0x09, 0x01, 0x00, 0x04, 0x0B, 0x01, 0x00, 0x04, 0x0D, 0x01, 0x00, 0x0C, 0x0F, 0x01, 0x00, 0x0C,
	0x0F, 0x06, 0x04, 0x0C, 0x02, 0x05, 0x06, 0x08, 0x0F, 0x0C, 0x06, 0x0E, 0x0C, 0x0C, 0x0D, 0x0E
		}));
	// palette for TITLE1
	m_palettes.push_back(SP_Palette({
	0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0A, 0x0A, 0x0A, 0x07,
	0x0A, 0x0A, 0x0A, 0x07, 0x0B, 0x0B, 0x0B, 0x07, 0x0E, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0B, 0x00, 0x00, 0x0C,
	0x08, 0x08, 0x08, 0x08, 0x05, 0x05, 0x05, 0x08, 0x06, 0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08,
		}));
	// palette for TITLE2
	m_palettes.push_back(SP_Palette({
		0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x06, 0x06, 0x06, 0x08, 0x0A, 0x0A, 0x0A, 0x07,
		0x0A, 0x0A, 0x0A, 0x07, 0x0B, 0x0B, 0x0B, 0x07, 0x0E, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07,
		0x01, 0x03, 0x07, 0x00, 0x08, 0x08, 0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0B, 0x00, 0x00, 0x0C,
		0x00, 0x02, 0x0A, 0x01, 0x05, 0x05, 0x05, 0x08, 0x06, 0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x07,
		}));

	// read required image data for the program
	load_image_data_from_file("FIXED", p_config);
	load_image_data_from_file("MOVING", p_config);
	load_image_data_from_file("CHARS8", p_config);

	// create textures used by the editor
	std::vector<SDL_Rect> l_font_rect{ {311,0,8,8},{463,0,8,8},{295,0,8,8},{79,0,8,8} };

	m_font = klib::gfx::split_surface_specified(p_rnd,
		sp_image_to_sdl_surface(m_image_files.at("CHARS8"),
			m_palettes.at(m_image_metadata.at("CHARS8").m_palette_no)),
		l_font_rect, true, true,
		sp_color_to_sdl(m_palettes.at(m_image_metadata.at("CHARS8").m_palette_no).get_color(0)));

	m_static = klib::gfx::split_surface(p_rnd,
		sp_image_to_sdl_surface(m_image_files.at("FIXED"), m_palettes.at(1)),
		16, 16);

	auto l_moving_srf = sp_image_to_sdl_surface(m_image_files.at("MOVING"), m_palettes.at(1));
	std::vector<SDL_Rect> l_moving_rects{
		{304, 64, 16, 16 }, { 304, 100, 16, 16 }, { 256, 196, 16, 16 }, { 272, 196, 16, 16 }, { 288, 196, 16, 16 }, { 304, 196, 16, 16 },
		{176, 446, 16, 16}, {176 + 16, 446, 16, 16},{176 + 32, 446, 16, 16},{176 + 48, 446, 16, 16},{176 + 64, 446, 16, 16}
	};

	m_moving = klib::gfx::split_surface_specified(p_rnd, l_moving_srf, l_moving_rects);

	m_animations[3] = { 6, 7,8,9,10,9 }; // player
	m_animations[25] = { 0, 1,2,3,4,5 }; // "bug" enemy
}

bool Project_gfx::save_bmp(const std::string& p_filename) const {
	return save_bmp(m_image_files.at(p_filename),
		m_palettes.at(m_image_metadata.at(p_filename).m_palette_no),
		p_filename + ".bmp");
}

bool Project_gfx::save_bmp(const SP_Image& p_image, const SP_Palette& p_palette, const std::string& p_filename) const {
	SDL_Surface* l_bmp = sp_image_to_sdl_surface(p_image, p_palette);
	int file_status = SDL_SaveBMP(l_bmp, p_filename.c_str());
	SDL_FreeSurface(l_bmp);
	return (file_status != -1);
}

SDL_Color Project_gfx::sp_color_to_sdl(const std::tuple<byte, byte, byte, byte>& p_col) const {
	return SDL_Color{
		std::get<0>(p_col),
		std::get<1>(p_col),
		std::get<2>(p_col),
		std::get<3>(p_col)
	};
}

SDL_Surface* Project_gfx::sp_image_to_sdl_surface(const SP_Image& p_image, const SP_Palette& p_palette, int p_transp_idx) const {
	SDL_Surface* l_bmp = SDL_CreateRGBSurface(0, p_image.get_w(),
		p_image.get_h(), 8, 0, 0, 0, 0);

	SDL_Color out_palette[256] = { 0, 0, 0 };
	for (int i{ 0 }; i < static_cast<int>(p_palette.get_size()); ++i)
		out_palette[i] = sp_color_to_sdl(p_palette.get_color(i));

	SDL_SetPaletteColors(l_bmp->format->palette, out_palette, 0, 256);

	for (int j{ 0 }; j < p_image.get_h(); ++j)
		for (int i{ 0 }; i < p_image.get_w(); ++i)
			klib::gfx::put_pixel(l_bmp, i, j, p_image.get_palette_index(i, j));

	if (p_transp_idx >= 0) {
		SDL_Color l_trans_rgb = sp_color_to_sdl(p_palette.get_color(p_transp_idx));
		SDL_SetColorKey(l_bmp, true, SDL_MapRGB(l_bmp->format, l_trans_rgb.r, l_trans_rgb.g, l_trans_rgb.b));
	}

	return l_bmp;
}

// image metadata
Project_gfx::Gfx_metadata::Gfx_metadata(int p_w, int p_pal_no, bool p_binary)
	: m_width{ p_w }, m_palette_no{ p_pal_no }, m_binary{ p_binary }
{}

// palettes
std::vector<byte> Project_gfx::get_palette_bytes(void) const {
	std::vector<byte> result;

	// only the first four palettes should be stored in the palettes DAT file
	for (std::size_t i{ 0 }; i < 4; ++i) {
		auto l_pal_bytes = m_palettes[i].to_bytes();
		result.insert(end(result), begin(l_pal_bytes), end(l_pal_bytes));
	}

	return result;
}
