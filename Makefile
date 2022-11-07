.POSIX:
CXX      = c++
CXXFLAGS = -std=c++20 -Os $$(sdl2-config --cflags)
LDFLAGS  = -s
LDLIBS   = $$(sdl2-config --libs)

obj = \
 superplexed/source/SP_Config.o \
 superplexed/source/common/imgui/imgui.o \
 superplexed/source/common/imgui/imgui_demo.o \
 superplexed/source/common/imgui/imgui_draw.o \
 superplexed/source/common/imgui/imgui_impl_sdl.o \
 superplexed/source/common/imgui/imgui_impl_sdlrenderer.o \
 superplexed/source/common/imgui/imgui_tables.o \
 superplexed/source/common/imgui/imgui_widgets.o \
 superplexed/source/common/klib/KImage.o \
 superplexed/source/common/klib/Timer.o \
 superplexed/source/common/klib/User_input.o \
 superplexed/source/common/klib/klib_file.o \
 superplexed/source/common/klib/klib_gfx.o \
 superplexed/source/common/pugixml/pugixml.o \
 superplexed/source/main.o \
 superplexed/source/sp_gfx/Project_gfx.o \
 superplexed/source/sp_gfx/Project_gfx_bmp.o \
 superplexed/source/sp_gfx/Project_gfx_xml.o \
 superplexed/source/sp_gfx/SP_Image.o \
 superplexed/source/sp_gfx/SP_Palette.o \
 superplexed/source/sp_levels/SP_Level.o \
 superplexed/source/sp_levels/SP_Level_undo_interface.o \
 superplexed/source/sp_saves/SP_Hallfame.o \
 superplexed/source/sp_saves/SP_Player_List.o \
 superplexed/source/sp_wins/Graphics_window.o \
 superplexed/source/sp_wins/Level_window.o \
 superplexed/source/sp_wins/Level_window_ui.o \
 superplexed/source/sp_wins/Level_window_xml.o \
 superplexed/source/sp_wins/Main_window.o \
 superplexed/source/sp_wins/Savefile_window.o

superplexed/superplexed$(EXE): $(obj)
	$(CXX) $(LDFLAGS) -o $@ $(obj) $(LDLIBS)

clean:
	rm -f superplexed/superplexed$(EXE) $(obj)

superplexed/source/SP_Config.o: superplexed/source/SP_Config.cpp \
 superplexed/source/SP_Config.h superplexed/source/SP_Constants.h \
 superplexed/source/./common/pugixml/pugixml.hpp \
 superplexed/source/./common/pugixml/pugiconfig.hpp \
 superplexed/source/./common/pugixml/pugiconfig.hpp \
 superplexed/source/./common/klib/klib_util.h
superplexed/source/common/imgui/imgui.o: \
 superplexed/source/common/imgui/imgui.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_internal.h \
 superplexed/source/common/imgui/imstb_textedit.h
superplexed/source/common/imgui/imgui_demo.o: \
 superplexed/source/common/imgui/imgui_demo.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h
superplexed/source/common/imgui/imgui_draw.o: \
 superplexed/source/common/imgui/imgui_draw.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_internal.h \
 superplexed/source/common/imgui/imstb_textedit.h \
 superplexed/source/common/imgui/imstb_rectpack.h \
 superplexed/source/common/imgui/imstb_truetype.h
superplexed/source/common/imgui/imgui_impl_sdl.o: \
 superplexed/source/common/imgui/imgui_impl_sdl.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_impl_sdl.h
superplexed/source/common/imgui/imgui_impl_sdlrenderer.o: \
 superplexed/source/common/imgui/imgui_impl_sdlrenderer.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_impl_sdlrenderer.h
superplexed/source/common/imgui/imgui_tables.o: \
 superplexed/source/common/imgui/imgui_tables.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_internal.h \
 superplexed/source/common/imgui/imstb_textedit.h
superplexed/source/common/imgui/imgui_widgets.o: \
 superplexed/source/common/imgui/imgui_widgets.cpp \
 superplexed/source/common/imgui/imgui.h \
 superplexed/source/common/imgui/imconfig.h \
 superplexed/source/common/imgui/imgui_internal.h \
 superplexed/source/common/imgui/imstb_textedit.h
superplexed/source/common/klib/KImage.o: \
 superplexed/source/common/klib/KImage.cpp \
 superplexed/source/common/klib/KImage.h \
 superplexed/source/common/klib/klib_gfx.h
superplexed/source/common/klib/Timer.o: \
 superplexed/source/common/klib/Timer.cpp \
 superplexed/source/common/klib/Timer.h
superplexed/source/common/klib/User_input.o: \
 superplexed/source/common/klib/User_input.cpp \
 superplexed/source/common/klib/User_input.h
superplexed/source/common/klib/klib_file.o: \
 superplexed/source/common/klib/klib_file.cpp \
 superplexed/source/common/klib/klib_file.h
superplexed/source/common/klib/klib_gfx.o: \
 superplexed/source/common/klib/klib_gfx.cpp \
 superplexed/source/common/klib/klib_gfx.h
superplexed/source/common/pugixml/pugixml.o: \
 superplexed/source/common/pugixml/pugixml.cpp \
 superplexed/source/common/pugixml/pugixml.hpp \
 superplexed/source/common/pugixml/pugiconfig.hpp
superplexed/source/main.o: superplexed/source/main.cpp \
 superplexed/source/./common/imgui/imgui.h \
 superplexed/source/./common/imgui/imconfig.h \
 superplexed/source/./common/imgui/imgui_impl_sdl.h \
 superplexed/source/./common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/./common/klib/User_input.h \
 superplexed/source/./sp_wins/Main_window.h \
 superplexed/source/./sp_wins/./../SP_Config.h \
 superplexed/source/./sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/./sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/./sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/./sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/./sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/./sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/./sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/./sp_wins/./../common/klib/User_input.h \
 superplexed/source/./sp_wins/Level_window.h \
 superplexed/source/./sp_wins/./../sp_levels/SP_Level_undo_interface.h \
 superplexed/source/./sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/./sp_wins/./../common/klib/Timer.h \
 superplexed/source/./sp_wins/./../SP_Constants.h \
 superplexed/source/./sp_wins/Graphics_window.h \
 superplexed/source/./sp_wins/Savefile_window.h \
 superplexed/source/./sp_wins/./../sp_saves/SP_Hallfame.h \
 superplexed/source/./sp_wins/./../sp_saves/SP_Player_list.h \
 superplexed/source/./SP_Config.h superplexed/source/./SP_Constants.h \
 superplexed/source/./common/klib/klib_file.h
superplexed/source/sp_gfx/Project_gfx.o: \
 superplexed/source/sp_gfx/Project_gfx.cpp \
 superplexed/source/sp_gfx/Project_gfx.h \
 superplexed/source/sp_gfx/SP_Palette.h \
 superplexed/source/sp_gfx/SP_Image.h \
 superplexed/source/sp_gfx/./../SP_Config.h \
 superplexed/source/sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_gfx/./../common/klib/klib_gfx.h \
 superplexed/source/sp_gfx/./../common/klib/klib_file.h \
 superplexed/source/sp_gfx/./../common/klib/KImage.h
superplexed/source/sp_gfx/Project_gfx_bmp.o: \
 superplexed/source/sp_gfx/Project_gfx_bmp.cpp \
 superplexed/source/sp_gfx/Project_gfx.h \
 superplexed/source/sp_gfx/SP_Palette.h \
 superplexed/source/sp_gfx/SP_Image.h \
 superplexed/source/sp_gfx/./../SP_Config.h \
 superplexed/source/sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_gfx/./../common/klib/klib_gfx.h
superplexed/source/sp_gfx/Project_gfx_xml.o: \
 superplexed/source/sp_gfx/Project_gfx_xml.cpp \
 superplexed/source/sp_gfx/Project_gfx.h \
 superplexed/source/sp_gfx/SP_Palette.h \
 superplexed/source/sp_gfx/SP_Image.h \
 superplexed/source/sp_gfx/./../SP_Config.h \
 superplexed/source/sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_gfx/./../common/pugixml/pugixml.hpp \
 superplexed/source/sp_gfx/./../common/pugixml/pugiconfig.hpp \
 superplexed/source/sp_gfx/./../common/pugixml/pugiconfig.hpp \
 superplexed/source/sp_gfx/./../common/klib/klib_util.h
superplexed/source/sp_gfx/SP_Image.o: \
 superplexed/source/sp_gfx/SP_Image.cpp \
 superplexed/source/sp_gfx/SP_Image.h
superplexed/source/sp_gfx/SP_Palette.o: \
 superplexed/source/sp_gfx/SP_Palette.cpp \
 superplexed/source/sp_gfx/SP_Palette.h
superplexed/source/sp_levels/SP_Level.o: \
 superplexed/source/sp_levels/SP_Level.cpp \
 superplexed/source/sp_levels/SP_Level.h \
 superplexed/source/sp_levels/./../SP_Constants.h
superplexed/source/sp_levels/SP_Level_undo_interface.o: \
 superplexed/source/sp_levels/SP_Level_undo_interface.cpp \
 superplexed/source/sp_levels/SP_Level_undo_interface.h \
 superplexed/source/sp_levels/SP_Level.h \
 superplexed/source/sp_levels/./../SP_Constants.h
superplexed/source/sp_saves/SP_Hallfame.o: \
 superplexed/source/sp_saves/SP_Hallfame.cpp \
 superplexed/source/sp_saves/SP_Hallfame.h \
 superplexed/source/sp_saves/./../SP_Constants.h
superplexed/source/sp_saves/SP_Player_List.o: \
 superplexed/source/sp_saves/SP_Player_List.cpp \
 superplexed/source/sp_saves/SP_Player_list.h \
 superplexed/source/sp_saves/./../SP_Constants.h
superplexed/source/sp_wins/Graphics_window.o: \
 superplexed/source/sp_wins/Graphics_window.cpp \
 superplexed/source/sp_wins/Graphics_window.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../SP_Constants.h
superplexed/source/sp_wins/Level_window.o: \
 superplexed/source/sp_wins/Level_window.cpp \
 superplexed/source/sp_wins/Level_window.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level_undo_interface.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/User_input.h \
 superplexed/source/sp_wins/./../common/klib/Timer.h \
 superplexed/source/sp_wins/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/klib_gfx.h \
 superplexed/source/sp_wins/./../common/klib/klib_file.h \
 superplexed/source/sp_wins/./../common/klib/klib_util.h
superplexed/source/sp_wins/Level_window_ui.o: \
 superplexed/source/sp_wins/Level_window_ui.cpp \
 superplexed/source/sp_wins/Level_window.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level_undo_interface.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/User_input.h \
 superplexed/source/sp_wins/./../common/klib/Timer.h \
 superplexed/source/sp_wins/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/klib_file.h \
 superplexed/source/sp_wins/./../common/klib/klib_util.h
superplexed/source/sp_wins/Level_window_xml.o: \
 superplexed/source/sp_wins/Level_window_xml.cpp \
 superplexed/source/sp_wins/Level_window.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level_undo_interface.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/User_input.h \
 superplexed/source/sp_wins/./../common/klib/Timer.h \
 superplexed/source/sp_wins/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/pugixml/pugixml.hpp \
 superplexed/source/sp_wins/./../common/pugixml/pugiconfig.hpp \
 superplexed/source/sp_wins/./../common/pugixml/pugiconfig.hpp \
 superplexed/source/sp_wins/./../common/klib/klib_util.h
superplexed/source/sp_wins/Main_window.o: \
 superplexed/source/sp_wins/Main_window.cpp \
 superplexed/source/sp_wins/Main_window.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/Project_gfx.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Palette.h \
 superplexed/source/sp_wins/./../sp_gfx/SP_Image.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Config.h \
 superplexed/source/sp_wins/./../sp_gfx/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../sp_gfx/./../SP_Constants.h \
 superplexed/source/sp_wins/./../common/klib/User_input.h \
 superplexed/source/sp_wins/Level_window.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level_undo_interface.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h \
 superplexed/source/sp_wins/./../common/klib/Timer.h \
 superplexed/source/sp_wins/./../SP_Constants.h \
 superplexed/source/sp_wins/Graphics_window.h \
 superplexed/source/sp_wins/Savefile_window.h \
 superplexed/source/sp_wins/./../sp_saves/SP_Hallfame.h \
 superplexed/source/sp_wins/./../sp_saves/SP_Player_list.h \
 superplexed/source/sp_wins/./../common/klib/klib_gfx.h \
 superplexed/source/sp_wins/./../common/klib/klib_file.h
superplexed/source/sp_wins/Savefile_window.o: \
 superplexed/source/sp_wins/Savefile_window.cpp \
 superplexed/source/sp_wins/Savefile_window.h \
 superplexed/source/sp_wins/./../SP_Config.h \
 superplexed/source/sp_wins/./../SP_Constants.h \
 superplexed/source/sp_wins/./../sp_saves/SP_Hallfame.h \
 superplexed/source/sp_wins/./../sp_saves/SP_Player_list.h \
 superplexed/source/sp_wins/./../common/imgui/imgui.h \
 superplexed/source/sp_wins/./../common/imgui/imconfig.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdl.h \
 superplexed/source/sp_wins/./../common/imgui/imgui_impl_sdlrenderer.h \
 superplexed/source/sp_wins/./../common/klib/klib_file.h \
 superplexed/source/sp_wins/./../common/klib/klib_util.h \
 superplexed/source/sp_wins/./../sp_levels/SP_Level.h
