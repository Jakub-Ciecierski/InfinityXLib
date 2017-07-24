# Makefile generated by XPJ for linux64
-include Makefile.custom
ProjectName = flexDemoCUDA
flexDemoCUDA_cppfiles   += ./../../imgui.cpp
flexDemoCUDA_cppfiles   += ./../../main.cpp
flexDemoCUDA_cppfiles   += ./../../opengl/imguiRenderGL.cpp
flexDemoCUDA_cppfiles   += ./../../opengl/shader.cpp
flexDemoCUDA_cppfiles   += ./../../opengl/shadersGL.cpp
flexDemoCUDA_cppfiles   += ./../../../core/aabbtree.cpp
flexDemoCUDA_cppfiles   += ./../../../core/core.cpp
flexDemoCUDA_cppfiles   += ./../../../core/extrude.cpp
flexDemoCUDA_cppfiles   += ./../../../core/maths.cpp
flexDemoCUDA_cppfiles   += ./../../../core/mesh.cpp
flexDemoCUDA_cppfiles   += ./../../../core/perlin.cpp
flexDemoCUDA_cppfiles   += ./../../../core/pfm.cpp
flexDemoCUDA_cppfiles   += ./../../../core/platform.cpp
flexDemoCUDA_cppfiles   += ./../../../core/sdf.cpp
flexDemoCUDA_cppfiles   += ./../../../core/tga.cpp
flexDemoCUDA_cppfiles   += ./../../../core/voxelize.cpp

flexDemoCUDA_cpp_release_dep    = $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_c_release_dep      = $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_release_dep      = $(flexDemoCUDA_cpp_release_dep) $(flexDemoCUDA_cc_release_dep) $(flexDemoCUDA_c_release_dep)
-include $(flexDemoCUDA_release_dep)
flexDemoCUDA_cpp_debug_dep    = $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_c_debug_dep      = $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_debug_dep      = $(flexDemoCUDA_cpp_debug_dep) $(flexDemoCUDA_cc_debug_dep) $(flexDemoCUDA_c_debug_dep)
-include $(flexDemoCUDA_debug_dep)
flexDemoCUDA_release_hpaths    := 
flexDemoCUDA_release_hpaths    += $(CUDA_PATH)/include
flexDemoCUDA_release_hpaths    += $(CUDA_PATH)/extras/cupti/include
flexDemoCUDA_release_hpaths    += ./../../..
flexDemoCUDA_release_lpaths    := 
flexDemoCUDA_release_lpaths    += $(CUDA_PATH)/lib64
flexDemoCUDA_release_lpaths    += ./../../../lib/linux64
flexDemoCUDA_release_defines   := $(flexDemoCUDA_custom_defines)
flexDemoCUDA_release_libraries := 
flexDemoCUDA_release_libraries += :NvFlexExtReleaseCUDA_x64.a
flexDemoCUDA_release_libraries += :NvFlexReleaseCUDA_x64.a
flexDemoCUDA_release_libraries += :NvFlexExtReleaseCUDA_x64.a
flexDemoCUDA_release_libraries += :NvFlexDeviceRelease_x64.a
flexDemoCUDA_release_libraries += :libSDL2.a
flexDemoCUDA_release_libraries += :libSDL2main.a
flexDemoCUDA_release_common_cflags	:= $(flexDemoCUDA_custom_cflags)
flexDemoCUDA_release_common_cflags    += -MMD
flexDemoCUDA_release_common_cflags    += $(addprefix -D, $(flexDemoCUDA_release_defines))
flexDemoCUDA_release_common_cflags    += $(addprefix -I, $(flexDemoCUDA_release_hpaths))
flexDemoCUDA_release_common_cflags  += -m64
flexDemoCUDA_release_common_cflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexDemoCUDA_release_common_cflags  += -O3 -ffast-math -DNDEBUG
flexDemoCUDA_release_cflags	:= $(flexDemoCUDA_release_common_cflags)
flexDemoCUDA_release_cppflags	:= $(flexDemoCUDA_release_common_cflags)
flexDemoCUDA_release_lflags    := $(flexDemoCUDA_custom_lflags)
flexDemoCUDA_release_lflags    += $(addprefix -L, $(flexDemoCUDA_release_lpaths))
flexDemoCUDA_release_lflags    += -Wl,--start-group $(addprefix -l, $(flexDemoCUDA_release_libraries)) -Wl,--end-group
flexDemoCUDA_release_lflags  += -g -L../../../external/glew/lib/linux -L/usr/lib -L"../../../lib/linux64" -L../../../external/SDL2-2.0.4/lib/x64/ -L$(CUDA_PATH)/lib64 -lGL -lglut -lGLU -lGLEW -lcudart_static -ldl -lrt -pthread
flexDemoCUDA_release_lflags  += -m64
flexDemoCUDA_release_objsdir  = $(OBJS_DIR)/flexDemoCUDA_release
flexDemoCUDA_release_cpp_o    = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_release_cc_o    = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_release_c_o      = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_release_obj      = $(flexDemoCUDA_release_cpp_o) $(flexDemoCUDA_release_cc_o) $(flexDemoCUDA_release_c_o)
flexDemoCUDA_release_bin      := ./../../../bin/linux64/NvFlexDemoReleaseCUDA_x64

clean_flexDemoCUDA_release: 
	@$(ECHO) clean flexDemoCUDA release
	@$(RMDIR) $(flexDemoCUDA_release_objsdir)
	@$(RMDIR) $(flexDemoCUDA_release_bin)
	@$(RMDIR) $(DEPSDIR)/flexDemoCUDA/release

build_flexDemoCUDA_release: postbuild_flexDemoCUDA_release
postbuild_flexDemoCUDA_release: mainbuild_flexDemoCUDA_release
mainbuild_flexDemoCUDA_release: prebuild_flexDemoCUDA_release $(flexDemoCUDA_release_bin)
prebuild_flexDemoCUDA_release:

$(flexDemoCUDA_release_bin): $(flexDemoCUDA_release_obj) build_flexExtCUDA_release 
	mkdir -p `dirname ./../../../bin/linux64/NvFlexDemoReleaseCUDA_x64`
	$(CCLD) $(flexDemoCUDA_release_obj) $(flexDemoCUDA_release_lflags) -o $(flexDemoCUDA_release_bin) 
	$(ECHO) building $@ complete!

flexDemoCUDA_release_DEPDIR = $(dir $(@))/$(*F)
$(flexDemoCUDA_release_cpp_o): $(flexDemoCUDA_release_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexDemoCUDA_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))))
	cp $(flexDemoCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))).P; \
	  rm -f $(flexDemoCUDA_release_DEPDIR).d

$(flexDemoCUDA_release_cc_o): $(flexDemoCUDA_release_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexDemoCUDA_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))))
	cp $(flexDemoCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))).release.P; \
	  rm -f $(flexDemoCUDA_release_DEPDIR).d

$(flexDemoCUDA_release_c_o): $(flexDemoCUDA_release_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(flexDemoCUDA_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cfiles))))))
	cp $(flexDemoCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_release_objsdir),, $@))), $(flexDemoCUDA_cfiles))))).P; \
	  rm -f $(flexDemoCUDA_release_DEPDIR).d

flexDemoCUDA_debug_hpaths    := 
flexDemoCUDA_debug_hpaths    += $(CUDA_PATH)/include
flexDemoCUDA_debug_hpaths    += $(CUDA_PATH)/extras/cupti/include
flexDemoCUDA_debug_hpaths    += ./../../..
flexDemoCUDA_debug_lpaths    := 
flexDemoCUDA_debug_lpaths    += $(CUDA_PATH)/lib64
flexDemoCUDA_debug_lpaths    += ./../../../lib/linux64
flexDemoCUDA_debug_defines   := $(flexDemoCUDA_custom_defines)
flexDemoCUDA_debug_libraries := 
flexDemoCUDA_debug_libraries += :NvFlexExtDebugCUDA_x64.a
flexDemoCUDA_debug_libraries += :NvFlexDebugCUDA_x64.a
flexDemoCUDA_debug_libraries += :NvFlexExtDebugCUDA_x64.a
flexDemoCUDA_debug_libraries += :libSDL2.a
flexDemoCUDA_debug_libraries += :libSDL2main.a
flexDemoCUDA_debug_common_cflags	:= $(flexDemoCUDA_custom_cflags)
flexDemoCUDA_debug_common_cflags    += -MMD
flexDemoCUDA_debug_common_cflags    += $(addprefix -D, $(flexDemoCUDA_debug_defines))
flexDemoCUDA_debug_common_cflags    += $(addprefix -I, $(flexDemoCUDA_debug_hpaths))
flexDemoCUDA_debug_common_cflags  += -m64
flexDemoCUDA_debug_common_cflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexDemoCUDA_debug_common_cflags  += -g -O0
flexDemoCUDA_debug_cflags	:= $(flexDemoCUDA_debug_common_cflags)
flexDemoCUDA_debug_cppflags	:= $(flexDemoCUDA_debug_common_cflags)
flexDemoCUDA_debug_lflags    := $(flexDemoCUDA_custom_lflags)
flexDemoCUDA_debug_lflags    += $(addprefix -L, $(flexDemoCUDA_debug_lpaths))
flexDemoCUDA_debug_lflags    += -Wl,--start-group $(addprefix -l, $(flexDemoCUDA_debug_libraries)) -Wl,--end-group
flexDemoCUDA_debug_lflags  += -g -L../../../external/glew/lib/linux -L/usr/lib -L"../../../lib/linux64" -L../../../external/SDL2-2.0.4/lib/x64/ -L$(CUDA_PATH)/lib64 -lGL -lglut -lGLU -lGLEW -lcudart_static -ldl -lrt -pthread
flexDemoCUDA_debug_lflags  += -m64
flexDemoCUDA_debug_objsdir  = $(OBJS_DIR)/flexDemoCUDA_debug
flexDemoCUDA_debug_cpp_o    = $(addprefix $(flexDemoCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_debug_cc_o    = $(addprefix $(flexDemoCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_debug_c_o      = $(addprefix $(flexDemoCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_debug_obj      = $(flexDemoCUDA_debug_cpp_o) $(flexDemoCUDA_debug_cc_o) $(flexDemoCUDA_debug_c_o)
flexDemoCUDA_debug_bin      := ./../../../bin/linux64/NvFlexDemoDebugCUDA_x64

clean_flexDemoCUDA_debug: 
	@$(ECHO) clean flexDemoCUDA debug
	@$(RMDIR) $(flexDemoCUDA_debug_objsdir)
	@$(RMDIR) $(flexDemoCUDA_debug_bin)
	@$(RMDIR) $(DEPSDIR)/flexDemoCUDA/debug

build_flexDemoCUDA_debug: postbuild_flexDemoCUDA_debug
postbuild_flexDemoCUDA_debug: mainbuild_flexDemoCUDA_debug
mainbuild_flexDemoCUDA_debug: prebuild_flexDemoCUDA_debug $(flexDemoCUDA_debug_bin)
prebuild_flexDemoCUDA_debug:

$(flexDemoCUDA_debug_bin): $(flexDemoCUDA_debug_obj) build_flexExtCUDA_debug 
	mkdir -p `dirname ./../../../bin/linux64/NvFlexDemoDebugCUDA_x64`
	$(CCLD) $(flexDemoCUDA_debug_obj) $(flexDemoCUDA_debug_lflags) -o $(flexDemoCUDA_debug_bin) 
	$(ECHO) building $@ complete!

flexDemoCUDA_debug_DEPDIR = $(dir $(@))/$(*F)
$(flexDemoCUDA_debug_cpp_o): $(flexDemoCUDA_debug_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexDemoCUDA_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))))
	cp $(flexDemoCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cppfiles))))).P; \
	  rm -f $(flexDemoCUDA_debug_DEPDIR).d

$(flexDemoCUDA_debug_cc_o): $(flexDemoCUDA_debug_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexDemoCUDA_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))))
	cp $(flexDemoCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_ccfiles))))).debug.P; \
	  rm -f $(flexDemoCUDA_debug_DEPDIR).d

$(flexDemoCUDA_debug_c_o): $(flexDemoCUDA_debug_objsdir)/%.o:
	$(ECHO) flexDemoCUDA: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(flexDemoCUDA_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cfiles))))))
	cp $(flexDemoCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexDemoCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexDemoCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexDemoCUDA_debug_objsdir),, $@))), $(flexDemoCUDA_cfiles))))).P; \
	  rm -f $(flexDemoCUDA_debug_DEPDIR).d

clean_flexDemoCUDA:  clean_flexDemoCUDA_release clean_flexDemoCUDA_debug
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
