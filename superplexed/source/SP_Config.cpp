#include "SP_Config.h"
#include "SP_Constants.h"
#include "SP_Constants.h"
#include "./common/pugixml/pugixml.hpp"
#include "./common/pugixml/pugiconfig.hpp"
#include "./common/klib/klib_util.h"
#include <stdexcept>

SP_Config::SP_Config(void) :
	m_levelset_no{ -1 }
{
	load_configuration();
}

std::string SP_Config::get_project_folder(void) const {
	return m_project_folder;
}

std::string SP_Config::get_full_filename(const std::string& p_filename, const std::string& p_suffix) {
	return p_filename + '.' + p_suffix;
}

std::string SP_Config::get_default_levels_filename(void) {
	return get_full_filename(c::FILENAME_LEVELS, c::SUFFIX_DAT);
}

void SP_Config::load_configuration(void) {
	try {
		pugi::xml_document doc;
		if (!doc.load_file(c::SPCONFIG_XML_FILENAME))
			throw std::runtime_error("Could not load xml");
		else {
			auto n_meta = doc.child(c::XML_TAG_META);
			m_project_folder = n_meta.attribute(c::XML_ATTR_PROJECT_FOLDER).as_string();
		}
		add_message("Configuration loaded");
	}
	catch (...) {
		m_project_folder = c::DEFAULT_PROJECT_FOLDER;
		add_message(std::string(c::SPCONFIG_XML_FILENAME) + " not found; using default configuration");
	}

	add_message("Level File: " + get_levels_dat_full_path());
}

std::string SP_Config::get_extension(char p_first_letter) const {
	if (m_levelset_no != -1)
		return p_first_letter + strnum();
	else
		return (p_first_letter == 'D' ? c::SUFFIX_DAT : c::SUFFIX_LST);
}

std::string SP_Config::get_levelset_lst_filename() const {
	return get_full_filename(c::FILENAME_LEVEL,
		get_extension('L'));
}

std::string SP_Config::get_levelset_dat_filename(void) const {
	return get_full_filename(c::FILENAME_LEVELS,
		get_extension('D'));
}

std::string SP_Config::get_prefix(void) const {
	if (m_levelset_no == -1)
		return c::FILENAME_LEVELS;
	else
		return c::FILENAME_LEVELS + strnum();
}

std::string SP_Config::strnum(void) const {
	return klib::util::stringnum(m_levelset_no, 2);
}

std::string SP_Config::get_full_path_ignore_extension(const std::string& p_full_filename) const {
	return m_project_folder + '/' + p_full_filename;
}

std::string SP_Config::get_level_lst_full_path(void) const {
	return get_full_path_ignore_extension(get_levelset_lst_filename());
}

std::string SP_Config::get_player_lst_full_path(void) const {
	return get_full_path_ignore_extension(
		get_full_filename(c::FILENAME_PLAYER,
			m_levelset_no == -1 ? c::SUFFIX_LST : get_extension('L'))
	);
}

std::string SP_Config::get_hallfame_lst_full_path(void) const {
	return get_full_path_ignore_extension(
		get_full_filename(c::FILENAME_HALLFAME,
			m_levelset_no == -1 ? c::SUFFIX_LST : get_extension('L'))
	);
}

std::string SP_Config::get_dat_full_path(const std::string& p_filename) const {
	return get_full_path(p_filename, c::SUFFIX_DAT);
}

std::string SP_Config::get_levels_dat_full_path(void) const {
	return get_full_path_ignore_extension(get_levelset_dat_filename());
}

std::string SP_Config::get_full_path(const std::string& p_filename, const std::string& p_extension) const {
	return m_project_folder + '/' + p_filename + '.' + p_extension;
}

void SP_Config::add_message(const std::string& p_msg, bool p_prevent_repeat) {
	if (m_messages.empty() || (!p_prevent_repeat || m_messages.front() != p_msg)) {
		m_messages.push_front(p_msg);
		if (m_messages.size() > c::MESSAGES_MAX_SIZE)
			m_messages.pop_back();
	}
}

const std::deque<std::string>& SP_Config::get_messages(void) const {
	return m_messages;
}

std::string SP_Config::get_folder(const std::string& p_subfolder) const {
	return m_project_folder + '/' + p_subfolder;
}

std::string SP_Config::get_xml_folder(void) const {
	return get_folder(c::SUFFIX_XML);
}

std::string SP_Config::get_bmp_folder(void) const {
	return get_folder(c::SUFFIX_BMP);
}

std::string SP_Config::get_SP_folder(void) const {
	return get_folder(c::SUFFIX_SP);
}

std::string SP_Config::get_xml_full_path(const std::string& p_filename) const {
	return get_xml_folder() + '/' + p_filename + ".xml";
}

std::string SP_Config::get_bmp_full_path(const std::string& p_dat_filename) const {
	return get_bmp_folder() + '/' + p_dat_filename + ".bmp";
}

// files derived from individual levels

std::string SP_Config::get_xml_full_path(std::size_t p_level_no) const {
	return get_xml_full_path(get_prefix() + '-' + klib::util::stringnum(p_level_no + 1));
}

std::string SP_Config::get_SP_full_path(std::size_t p_level_no) const {
	return get_SP_folder() + '/' + get_prefix() + '-' + klib::util::stringnum(p_level_no + 1) + ".SP";
}

std::string SP_Config::get_bmp_full_path(std::size_t p_level_no) const {
	return get_bmp_full_path(get_prefix() + '-' + klib::util::stringnum(p_level_no + 1));
}

void SP_Config::set_level_list_filename(const std::string& p_filename) {
	if (p_filename == get_default_levels_filename())
		m_levelset_no = -1;
	else
		m_levelset_no = atoi(p_filename.substr(p_filename.find_last_of('.') + 2).c_str());
}
