# Makefile generated by XPJ for LINUX64
-include Makefile.custom
ProjectName = PxFoundation
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsAllocator.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsAssert.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsFoundation.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsMathUtils.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsString.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsTempAllocator.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/PsUtilities.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixAtomic.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixCpu.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixFPU.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixMutex.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixPrintString.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixSList.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixSocket.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixSync.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixThread.cpp
PxFoundation_cppfiles   += ./../../../../PxShared/src/foundation/src/unix/PsUnixTime.cpp

PxFoundation_cpp_debug_dep    = $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxFoundation_cppfiles)))))
PxFoundation_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(PxFoundation_ccfiles)))))
PxFoundation_c_debug_dep      = $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxFoundation_cfiles)))))
PxFoundation_debug_dep      = $(PxFoundation_cpp_debug_dep) $(PxFoundation_cc_debug_dep) $(PxFoundation_c_debug_dep)
-include $(PxFoundation_debug_dep)
PxFoundation_cpp_release_dep    = $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxFoundation_cppfiles)))))
PxFoundation_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(PxFoundation_ccfiles)))))
PxFoundation_c_release_dep      = $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxFoundation_cfiles)))))
PxFoundation_release_dep      = $(PxFoundation_cpp_release_dep) $(PxFoundation_cc_release_dep) $(PxFoundation_c_release_dep)
-include $(PxFoundation_release_dep)
PxFoundation_cpp_checked_dep    = $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxFoundation_cppfiles)))))
PxFoundation_cc_checked_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.checked.P, $(PxFoundation_ccfiles)))))
PxFoundation_c_checked_dep      = $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxFoundation_cfiles)))))
PxFoundation_checked_dep      = $(PxFoundation_cpp_checked_dep) $(PxFoundation_cc_checked_dep) $(PxFoundation_c_checked_dep)
-include $(PxFoundation_checked_dep)
PxFoundation_cpp_profile_dep    = $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(PxFoundation_cppfiles)))))
PxFoundation_cc_profile_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.profile.P, $(PxFoundation_ccfiles)))))
PxFoundation_c_profile_dep      = $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(PxFoundation_cfiles)))))
PxFoundation_profile_dep      = $(PxFoundation_cpp_profile_dep) $(PxFoundation_cc_profile_dep) $(PxFoundation_c_profile_dep)
-include $(PxFoundation_profile_dep)
PxFoundation_debug_hpaths    := 
PxFoundation_debug_hpaths    += ./../../../../PxShared/include
PxFoundation_debug_hpaths    += ./../../../../PxShared/src/foundation/include
PxFoundation_debug_hpaths    += ./../../../../PxShared/src/foundation/include/unix
PxFoundation_debug_lpaths    := 
PxFoundation_debug_defines   := $(PxFoundation_custom_defines)
PxFoundation_debug_defines   += PX_FOUNDATION_DLL=1
PxFoundation_debug_defines   += _DEBUG
PxFoundation_debug_defines   += PX_DEBUG=1
PxFoundation_debug_defines   += PX_CHECKED=1
PxFoundation_debug_libraries := 
PxFoundation_debug_common_cflags	:= $(PxFoundation_custom_cflags)
PxFoundation_debug_common_cflags    += -MMD
PxFoundation_debug_common_cflags    += $(addprefix -D, $(PxFoundation_debug_defines))
PxFoundation_debug_common_cflags    += $(addprefix -I, $(PxFoundation_debug_hpaths))
PxFoundation_debug_common_cflags  += -m64
PxFoundation_debug_common_cflags  += -Werror -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
PxFoundation_debug_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
PxFoundation_debug_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized
PxFoundation_debug_common_cflags  += -Wno-missing-field-initializers
PxFoundation_debug_common_cflags  += -g3 -gdwarf-2
PxFoundation_debug_cflags	:= $(PxFoundation_debug_common_cflags)
PxFoundation_debug_cppflags	:= $(PxFoundation_debug_common_cflags)
PxFoundation_debug_lflags    := $(PxFoundation_custom_lflags)
PxFoundation_debug_lflags    += $(addprefix -L, $(PxFoundation_debug_lpaths))
PxFoundation_debug_lflags    += -Wl,--start-group $(addprefix -l, $(PxFoundation_debug_libraries)) -Wl,--end-group
PxFoundation_debug_lflags  += -lrt
PxFoundation_debug_lflags  += -m64
PxFoundation_debug_objsdir  = $(OBJS_DIR)/PxFoundation_debug
PxFoundation_debug_cpp_o    = $(addprefix $(PxFoundation_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxFoundation_cppfiles)))))
PxFoundation_debug_cc_o    = $(addprefix $(PxFoundation_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxFoundation_ccfiles)))))
PxFoundation_debug_c_o      = $(addprefix $(PxFoundation_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxFoundation_cfiles)))))
PxFoundation_debug_obj      = $(PxFoundation_debug_cpp_o) $(PxFoundation_debug_cc_o) $(PxFoundation_debug_c_o)
PxFoundation_debug_bin      := ./../../../../PxShared/bin/linux64/libPxFoundationDEBUG_x64.so

clean_PxFoundation_debug: 
	@$(ECHO) clean PxFoundation debug
	@$(RMDIR) $(PxFoundation_debug_objsdir)
	@$(RMDIR) $(PxFoundation_debug_bin)
	@$(RMDIR) $(DEPSDIR)/PxFoundation/debug

build_PxFoundation_debug: postbuild_PxFoundation_debug
postbuild_PxFoundation_debug: mainbuild_PxFoundation_debug
mainbuild_PxFoundation_debug: prebuild_PxFoundation_debug $(PxFoundation_debug_bin)
prebuild_PxFoundation_debug:

$(PxFoundation_debug_bin): $(PxFoundation_debug_obj) 
	mkdir -p `dirname ./../../../../PxShared/bin/linux64/libPxFoundationDEBUG_x64.so`
	$(CXX) -shared $(PxFoundation_debug_obj) $(PxFoundation_debug_lflags) -lc -o $@ 
	$(ECHO) building $@ complete!

PxFoundation_debug_DEPDIR = $(dir $(@))/$(*F)
$(PxFoundation_debug_cpp_o): $(PxFoundation_debug_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cppfiles))))))
	cp $(PxFoundation_debug_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  rm -f $(PxFoundation_debug_DEPDIR).d

$(PxFoundation_debug_cc_o): $(PxFoundation_debug_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_ccfiles))))))
	cp $(PxFoundation_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_ccfiles))))).debug.P; \
	  rm -f $(PxFoundation_debug_DEPDIR).d

$(PxFoundation_debug_c_o): $(PxFoundation_debug_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxFoundation_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cfiles))))))
	cp $(PxFoundation_debug_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_debug_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  rm -f $(PxFoundation_debug_DEPDIR).d

PxFoundation_release_hpaths    := 
PxFoundation_release_hpaths    += ./../../../../PxShared/include
PxFoundation_release_hpaths    += ./../../../../PxShared/src/foundation/include
PxFoundation_release_hpaths    += ./../../../../PxShared/src/foundation/include/unix
PxFoundation_release_lpaths    := 
PxFoundation_release_defines   := $(PxFoundation_custom_defines)
PxFoundation_release_defines   += PX_FOUNDATION_DLL=1
PxFoundation_release_defines   += NDEBUG
PxFoundation_release_libraries := 
PxFoundation_release_common_cflags	:= $(PxFoundation_custom_cflags)
PxFoundation_release_common_cflags    += -MMD
PxFoundation_release_common_cflags    += $(addprefix -D, $(PxFoundation_release_defines))
PxFoundation_release_common_cflags    += $(addprefix -I, $(PxFoundation_release_hpaths))
PxFoundation_release_common_cflags  += -m64
PxFoundation_release_common_cflags  += -Werror -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
PxFoundation_release_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
PxFoundation_release_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized
PxFoundation_release_common_cflags  += -Wno-missing-field-initializers
PxFoundation_release_common_cflags  += -O3 -fno-strict-aliasing
PxFoundation_release_cflags	:= $(PxFoundation_release_common_cflags)
PxFoundation_release_cppflags	:= $(PxFoundation_release_common_cflags)
PxFoundation_release_lflags    := $(PxFoundation_custom_lflags)
PxFoundation_release_lflags    += $(addprefix -L, $(PxFoundation_release_lpaths))
PxFoundation_release_lflags    += -Wl,--start-group $(addprefix -l, $(PxFoundation_release_libraries)) -Wl,--end-group
PxFoundation_release_lflags  += -lrt
PxFoundation_release_lflags  += -m64
PxFoundation_release_objsdir  = $(OBJS_DIR)/PxFoundation_release
PxFoundation_release_cpp_o    = $(addprefix $(PxFoundation_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxFoundation_cppfiles)))))
PxFoundation_release_cc_o    = $(addprefix $(PxFoundation_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxFoundation_ccfiles)))))
PxFoundation_release_c_o      = $(addprefix $(PxFoundation_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxFoundation_cfiles)))))
PxFoundation_release_obj      = $(PxFoundation_release_cpp_o) $(PxFoundation_release_cc_o) $(PxFoundation_release_c_o)
PxFoundation_release_bin      := ./../../../../PxShared/bin/linux64/libPxFoundation_x64.so

clean_PxFoundation_release: 
	@$(ECHO) clean PxFoundation release
	@$(RMDIR) $(PxFoundation_release_objsdir)
	@$(RMDIR) $(PxFoundation_release_bin)
	@$(RMDIR) $(DEPSDIR)/PxFoundation/release

build_PxFoundation_release: postbuild_PxFoundation_release
postbuild_PxFoundation_release: mainbuild_PxFoundation_release
mainbuild_PxFoundation_release: prebuild_PxFoundation_release $(PxFoundation_release_bin)
prebuild_PxFoundation_release:

$(PxFoundation_release_bin): $(PxFoundation_release_obj) 
	mkdir -p `dirname ./../../../../PxShared/bin/linux64/libPxFoundation_x64.so`
	$(CXX) -shared $(PxFoundation_release_obj) $(PxFoundation_release_lflags) -lc -o $@ 
	$(ECHO) building $@ complete!

PxFoundation_release_DEPDIR = $(dir $(@))/$(*F)
$(PxFoundation_release_cpp_o): $(PxFoundation_release_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cppfiles))))))
	cp $(PxFoundation_release_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  rm -f $(PxFoundation_release_DEPDIR).d

$(PxFoundation_release_cc_o): $(PxFoundation_release_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_ccfiles))))))
	cp $(PxFoundation_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_ccfiles))))).release.P; \
	  rm -f $(PxFoundation_release_DEPDIR).d

$(PxFoundation_release_c_o): $(PxFoundation_release_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxFoundation_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cfiles))))))
	cp $(PxFoundation_release_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_release_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  rm -f $(PxFoundation_release_DEPDIR).d

PxFoundation_checked_hpaths    := 
PxFoundation_checked_hpaths    += ./../../../../PxShared/include
PxFoundation_checked_hpaths    += ./../../../../PxShared/src/foundation/include
PxFoundation_checked_hpaths    += ./../../../../PxShared/src/foundation/include/unix
PxFoundation_checked_lpaths    := 
PxFoundation_checked_defines   := $(PxFoundation_custom_defines)
PxFoundation_checked_defines   += PX_FOUNDATION_DLL=1
PxFoundation_checked_defines   += NDEBUG
PxFoundation_checked_defines   += PX_CHECKED=1
PxFoundation_checked_libraries := 
PxFoundation_checked_common_cflags	:= $(PxFoundation_custom_cflags)
PxFoundation_checked_common_cflags    += -MMD
PxFoundation_checked_common_cflags    += $(addprefix -D, $(PxFoundation_checked_defines))
PxFoundation_checked_common_cflags    += $(addprefix -I, $(PxFoundation_checked_hpaths))
PxFoundation_checked_common_cflags  += -m64
PxFoundation_checked_common_cflags  += -Werror -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
PxFoundation_checked_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
PxFoundation_checked_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized
PxFoundation_checked_common_cflags  += -Wno-missing-field-initializers
PxFoundation_checked_common_cflags  += -g3 -gdwarf-2 -O3 -fno-strict-aliasing
PxFoundation_checked_cflags	:= $(PxFoundation_checked_common_cflags)
PxFoundation_checked_cppflags	:= $(PxFoundation_checked_common_cflags)
PxFoundation_checked_lflags    := $(PxFoundation_custom_lflags)
PxFoundation_checked_lflags    += $(addprefix -L, $(PxFoundation_checked_lpaths))
PxFoundation_checked_lflags    += -Wl,--start-group $(addprefix -l, $(PxFoundation_checked_libraries)) -Wl,--end-group
PxFoundation_checked_lflags  += -lrt
PxFoundation_checked_lflags  += -m64
PxFoundation_checked_objsdir  = $(OBJS_DIR)/PxFoundation_checked
PxFoundation_checked_cpp_o    = $(addprefix $(PxFoundation_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxFoundation_cppfiles)))))
PxFoundation_checked_cc_o    = $(addprefix $(PxFoundation_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxFoundation_ccfiles)))))
PxFoundation_checked_c_o      = $(addprefix $(PxFoundation_checked_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxFoundation_cfiles)))))
PxFoundation_checked_obj      = $(PxFoundation_checked_cpp_o) $(PxFoundation_checked_cc_o) $(PxFoundation_checked_c_o)
PxFoundation_checked_bin      := ./../../../../PxShared/bin/linux64/libPxFoundationCHECKED_x64.so

clean_PxFoundation_checked: 
	@$(ECHO) clean PxFoundation checked
	@$(RMDIR) $(PxFoundation_checked_objsdir)
	@$(RMDIR) $(PxFoundation_checked_bin)
	@$(RMDIR) $(DEPSDIR)/PxFoundation/checked

build_PxFoundation_checked: postbuild_PxFoundation_checked
postbuild_PxFoundation_checked: mainbuild_PxFoundation_checked
mainbuild_PxFoundation_checked: prebuild_PxFoundation_checked $(PxFoundation_checked_bin)
prebuild_PxFoundation_checked:

$(PxFoundation_checked_bin): $(PxFoundation_checked_obj) 
	mkdir -p `dirname ./../../../../PxShared/bin/linux64/libPxFoundationCHECKED_x64.so`
	$(CXX) -shared $(PxFoundation_checked_obj) $(PxFoundation_checked_lflags) -lc -o $@ 
	$(ECHO) building $@ complete!

PxFoundation_checked_DEPDIR = $(dir $(@))/$(*F)
$(PxFoundation_checked_cpp_o): $(PxFoundation_checked_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling checked $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_checked_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cppfiles))))))
	cp $(PxFoundation_checked_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  rm -f $(PxFoundation_checked_DEPDIR).d

$(PxFoundation_checked_cc_o): $(PxFoundation_checked_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling checked $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_checked_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_ccfiles))))))
	cp $(PxFoundation_checked_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_ccfiles))))).checked.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_ccfiles))))).checked.P; \
	  rm -f $(PxFoundation_checked_DEPDIR).d

$(PxFoundation_checked_c_o): $(PxFoundation_checked_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling checked $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxFoundation_checked_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cfiles))))))
	cp $(PxFoundation_checked_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_checked_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/checked/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_checked_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  rm -f $(PxFoundation_checked_DEPDIR).d

PxFoundation_profile_hpaths    := 
PxFoundation_profile_hpaths    += ./../../../../PxShared/include
PxFoundation_profile_hpaths    += ./../../../../PxShared/src/foundation/include
PxFoundation_profile_hpaths    += ./../../../../PxShared/src/foundation/include/unix
PxFoundation_profile_lpaths    := 
PxFoundation_profile_defines   := $(PxFoundation_custom_defines)
PxFoundation_profile_defines   += PX_FOUNDATION_DLL=1
PxFoundation_profile_defines   += NDEBUG
PxFoundation_profile_defines   += PX_PROFILE=1
PxFoundation_profile_libraries := 
PxFoundation_profile_common_cflags	:= $(PxFoundation_custom_cflags)
PxFoundation_profile_common_cflags    += -MMD
PxFoundation_profile_common_cflags    += $(addprefix -D, $(PxFoundation_profile_defines))
PxFoundation_profile_common_cflags    += $(addprefix -I, $(PxFoundation_profile_hpaths))
PxFoundation_profile_common_cflags  += -m64
PxFoundation_profile_common_cflags  += -Werror -m64 -fPIC -msse2 -mfpmath=sse -ffast-math -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden
PxFoundation_profile_common_cflags  += -Wall -Wextra -Wstrict-aliasing=2 -fdiagnostics-show-option
PxFoundation_profile_common_cflags  += -Wno-invalid-offsetof -Wno-uninitialized
PxFoundation_profile_common_cflags  += -Wno-missing-field-initializers
PxFoundation_profile_common_cflags  += -O3 -fno-strict-aliasing
PxFoundation_profile_cflags	:= $(PxFoundation_profile_common_cflags)
PxFoundation_profile_cppflags	:= $(PxFoundation_profile_common_cflags)
PxFoundation_profile_lflags    := $(PxFoundation_custom_lflags)
PxFoundation_profile_lflags    += $(addprefix -L, $(PxFoundation_profile_lpaths))
PxFoundation_profile_lflags    += -Wl,--start-group $(addprefix -l, $(PxFoundation_profile_libraries)) -Wl,--end-group
PxFoundation_profile_lflags  += -lrt
PxFoundation_profile_lflags  += -m64
PxFoundation_profile_objsdir  = $(OBJS_DIR)/PxFoundation_profile
PxFoundation_profile_cpp_o    = $(addprefix $(PxFoundation_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(PxFoundation_cppfiles)))))
PxFoundation_profile_cc_o    = $(addprefix $(PxFoundation_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(PxFoundation_ccfiles)))))
PxFoundation_profile_c_o      = $(addprefix $(PxFoundation_profile_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(PxFoundation_cfiles)))))
PxFoundation_profile_obj      = $(PxFoundation_profile_cpp_o) $(PxFoundation_profile_cc_o) $(PxFoundation_profile_c_o)
PxFoundation_profile_bin      := ./../../../../PxShared/bin/linux64/libPxFoundationPROFILE_x64.so

clean_PxFoundation_profile: 
	@$(ECHO) clean PxFoundation profile
	@$(RMDIR) $(PxFoundation_profile_objsdir)
	@$(RMDIR) $(PxFoundation_profile_bin)
	@$(RMDIR) $(DEPSDIR)/PxFoundation/profile

build_PxFoundation_profile: postbuild_PxFoundation_profile
postbuild_PxFoundation_profile: mainbuild_PxFoundation_profile
mainbuild_PxFoundation_profile: prebuild_PxFoundation_profile $(PxFoundation_profile_bin)
prebuild_PxFoundation_profile:

$(PxFoundation_profile_bin): $(PxFoundation_profile_obj) 
	mkdir -p `dirname ./../../../../PxShared/bin/linux64/libPxFoundationPROFILE_x64.so`
	$(CXX) -shared $(PxFoundation_profile_obj) $(PxFoundation_profile_lflags) -lc -o $@ 
	$(ECHO) building $@ complete!

PxFoundation_profile_DEPDIR = $(dir $(@))/$(*F)
$(PxFoundation_profile_cpp_o): $(PxFoundation_profile_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling profile $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_profile_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cppfiles))))))
	cp $(PxFoundation_profile_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cppfiles))))).P; \
	  rm -f $(PxFoundation_profile_DEPDIR).d

$(PxFoundation_profile_cc_o): $(PxFoundation_profile_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling profile $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(PxFoundation_profile_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_ccfiles))))))
	cp $(PxFoundation_profile_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_ccfiles))))).profile.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_ccfiles))))).profile.P; \
	  rm -f $(PxFoundation_profile_DEPDIR).d

$(PxFoundation_profile_c_o): $(PxFoundation_profile_objsdir)/%.o:
	$(ECHO) PxFoundation: compiling profile $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(PxFoundation_profile_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cfiles))))))
	cp $(PxFoundation_profile_DEPDIR).d $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(PxFoundation_profile_DEPDIR).d >> $(addprefix $(DEPSDIR)/PxFoundation/profile/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(PxFoundation_profile_objsdir),, $@))), $(PxFoundation_cfiles))))).P; \
	  rm -f $(PxFoundation_profile_DEPDIR).d

clean_PxFoundation:  clean_PxFoundation_debug clean_PxFoundation_release clean_PxFoundation_checked clean_PxFoundation_profile
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
