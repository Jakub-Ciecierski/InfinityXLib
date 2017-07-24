# Makefile generated by XPJ for android
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
flexDemoCUDA_cppfiles   += ./../../../external/egl_setup/egl_setup.cpp
flexDemoCUDA_cppfiles   += ./../../android/android_main.cpp
flexDemoCUDA_cppfiles   += ./../../android/android_mainRender.cpp
flexDemoCUDA_cfiles   += ./../../android/android_native_app_glue.c

flexDemoCUDA_cpp_release_dep    = $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_c_release_dep      = $(addprefix $(DEPSDIR)/flexDemoCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_release_dep      = $(flexDemoCUDA_cpp_release_dep) $(flexDemoCUDA_cc_release_dep) $(flexDemoCUDA_c_release_dep)
-include $(flexDemoCUDA_release_dep)
flexDemoCUDA_release_hpaths    := 
flexDemoCUDA_release_hpaths    += ./../../..
flexDemoCUDA_release_hpaths    += ./../../../../../../external/android-ndk/android-ndk-r10e-linux/platforms/android-15/arch-arm/usr/include
flexDemoCUDA_release_hpaths    += ./../../../../../../external/android-ndk/android-ndk-r10e-linux/sources/cxx-stl/stlport/stlport
flexDemoCUDA_release_hpaths    += ./../../../../../../external/CUDA/cuda-6.0-linux/targets/armv7-linux-androideabi/include
flexDemoCUDA_release_hpaths    += ./../../../external/egl_setup
flexDemoCUDA_release_hpaths    += ./../../../external/regal_static/include
flexDemoCUDA_release_lpaths    := 
flexDemoCUDA_release_lpaths    += ./../../../../../../external/CUDA/cuda-6.0-linux/targets/armv7-linux-androideabi/lib
flexDemoCUDA_release_lpaths    += ./../../../lib/android
flexDemoCUDA_release_lpaths    += ./../../../../../../external/android-ndk/android-ndk-r10e-linux/sources/cxx-stl/stlport/libs/armeabi-v7a
flexDemoCUDA_release_lpaths    += ./../../../external/regal_static/lib/armeabi-v7a
flexDemoCUDA_release_lpaths    += ./../../../lib/android
flexDemoCUDA_release_defines   := $(flexDemoCUDA_custom_defines)
flexDemoCUDA_release_defines   += android
flexDemoCUDA_release_defines   += ANDROID=1
flexDemoCUDA_release_defines   += ANDROID_PLAT=1
flexDemoCUDA_release_defines   += DISABLE_IMPORTGL
flexDemoCUDA_release_defines   += NDEBUG
flexDemoCUDA_release_libraries := 
flexDemoCUDA_release_libraries += NvFlexReleaseCUDA_armv7l
flexDemoCUDA_release_libraries += flexDevice_x64
flexDemoCUDA_release_libraries += flexExt_cuda_release_armv7l
flexDemoCUDA_release_libraries += android
flexDemoCUDA_release_libraries += stdc++
flexDemoCUDA_release_libraries += c
flexDemoCUDA_release_libraries += m
flexDemoCUDA_release_libraries += log
flexDemoCUDA_release_libraries += dl
flexDemoCUDA_release_libraries += EGL
flexDemoCUDA_release_libraries += gomp
flexDemoCUDA_release_libraries += cudart_static
flexDemoCUDA_release_libraries += Regal_static
flexDemoCUDA_release_libraries += stlport_static
flexDemoCUDA_release_libraries += NvFlexRelease_armv7l
flexDemoCUDA_release_libraries += NvFlexExtRelease_armv7l
flexDemoCUDA_release_common_cflags	:= $(flexDemoCUDA_custom_cflags)
flexDemoCUDA_release_common_cflags    += -MMD
flexDemoCUDA_release_common_cflags    += $(addprefix -D, $(flexDemoCUDA_release_defines))
flexDemoCUDA_release_common_cflags    += $(addprefix -I, $(flexDemoCUDA_release_hpaths))
flexDemoCUDA_release_cflags	:= $(flexDemoCUDA_release_common_cflags)
flexDemoCUDA_release_cflags  += -std=c++11 -fno-exceptions -fno-rtti
flexDemoCUDA_release_cflags  += -fpic -fPIC -ffunction-sections -funwind-tables -fstack-protector -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -O2 -g -fomit-frame-pointer -fstrict-aliasing -funswitch-loops -finline-limit=300
flexDemoCUDA_release_cppflags	:= $(flexDemoCUDA_release_common_cflags)
flexDemoCUDA_release_cppflags  += -std=c++11 -fno-exceptions -fno-rtti
flexDemoCUDA_release_cppflags  += -fpic -fPIC -ffunction-sections -funwind-tables -fstack-protector -no-canonical-prefixes -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -O2 -g -fomit-frame-pointer -fstrict-aliasing -funswitch-loops -finline-limit=300
flexDemoCUDA_release_lflags    := $(flexDemoCUDA_custom_lflags)
flexDemoCUDA_release_lflags    += $(addprefix -L, $(flexDemoCUDA_release_lpaths))
flexDemoCUDA_release_lflags    += -Wl,--start-group $(addprefix -l, $(flexDemoCUDA_release_libraries)) -Wl,--end-group
flexDemoCUDA_release_lflags  += --sysroot=/home/mmacklin/swhost/devrel/libdev/flex/dev/main/../../../external/android-ndk/android-ndk-r10e-linux/platforms/android-15/arch-arm -shared -Wl,--no-undefined
flexDemoCUDA_release_objsdir  = $(OBJS_DIR)/flexDemoCUDA_release
flexDemoCUDA_release_cpp_o    = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(flexDemoCUDA_cppfiles)))))
flexDemoCUDA_release_cc_o    = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(flexDemoCUDA_ccfiles)))))
flexDemoCUDA_release_c_o      = $(addprefix $(flexDemoCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(flexDemoCUDA_cfiles)))))
flexDemoCUDA_release_obj      = $(flexDemoCUDA_release_cpp_o) $(flexDemoCUDA_release_cc_o) $(flexDemoCUDA_release_c_o)
flexDemoCUDA_release_bin      := ./../android/flex_project/libs/armeabi-v7a/libflexDemo.so

clean_flexDemoCUDA_release: 
	@$(ECHO) clean flexDemoCUDA release
	@$(RMDIR) $(flexDemoCUDA_release_objsdir)
	@$(RMDIR) $(flexDemoCUDA_release_bin)
	@$(RMDIR) $(DEPSDIR)/flexDemoCUDA/release

build_flexDemoCUDA_release: postbuild_flexDemoCUDA_release
postbuild_flexDemoCUDA_release: mainbuild_flexDemoCUDA_release preantbuild_flexDemoCUDA_release antbuild_flexDemoCUDA_release
preantbuild_flexDemoCUDA_release: mainbuild_flexDemoCUDA_release
antbuild_flexDemoCUDA_release: preantbuild_flexDemoCUDA_release
	dos2unix $(ANT_TOOL); JAVA_HOME=$(JAVA_HOME) $(ANT_TOOL) -f ./../android/flex_project/build.xml debug
mainbuild_flexDemoCUDA_release: prebuild_flexDemoCUDA_release $(flexDemoCUDA_release_bin)
prebuild_flexDemoCUDA_release:

$(flexDemoCUDA_release_bin): $(flexDemoCUDA_release_obj) build_flexCUDA_release build_flexDevice_release build_flexExtCUDA_release 
	mkdir -p `dirname ./../android/flex_project/libs/armeabi-v7a/libflexDemo.so`
	$(CXX) -shared $(flexDemoCUDA_release_obj) $(flexDemoCUDA_release_lflags) -lc -o $@ 
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

clean_flexDemoCUDA:  clean_flexDemoCUDA_release
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
