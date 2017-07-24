# Makefile generated by XPJ for linux64
-include Makefile.custom
ProjectName = flexCUDA
flexCUDA_cppfiles   += ./../../../src/cuda/util.cpp
flexCUDA_cuda_src_cuda_bvh_cu   += ./../../../src/cuda/bvh.cu
flexCUDA_cuda_src_cuda_flex_cu   += ./../../../src/cuda/flex.cu
flexCUDA_cuda_src_cuda_sort_cu   += ./../../../src/cuda/sort.cu

flexCUDA_cpp_release_dep    = $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(flexCUDA_cppfiles)))))
flexCUDA_cc_release_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.release.P, $(flexCUDA_ccfiles)))))
flexCUDA_c_release_dep      = $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(flexCUDA_cfiles)))))
flexCUDA_release_dep      = $(flexCUDA_cpp_release_dep) $(flexCUDA_cc_release_dep) $(flexCUDA_c_release_dep)
-include $(flexCUDA_release_dep)
flexCUDA_cpp_debug_dep    = $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.P, $(flexCUDA_cppfiles)))))
flexCUDA_cc_debug_dep    = $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.debug.P, $(flexCUDA_ccfiles)))))
flexCUDA_c_debug_dep      = $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.P, $(flexCUDA_cfiles)))))
flexCUDA_debug_dep      = $(flexCUDA_cpp_debug_dep) $(flexCUDA_cc_debug_dep) $(flexCUDA_c_debug_dep)
-include $(flexCUDA_debug_dep)
flexCUDA_release_hpaths    := 
flexCUDA_release_hpaths    += ./../../../../../../external/CUDA/8.0.44-linux/include
flexCUDA_release_hpaths    += ./../../../../../../external/CUDA/8.0.44-linux/extras/cupti/include
flexCUDA_release_hpaths    += ./../../..
flexCUDA_release_lpaths    := 
flexCUDA_release_lpaths    += ./../../../../../../external/CUDA/8.0.44-linux/lib64
flexCUDA_release_defines   := $(flexCUDA_custom_defines)
flexCUDA_release_libraries := 
flexCUDA_release_libraries += ./../../../lib/linux64/NvFlexDevice_x64.a
flexCUDA_release_common_cflags	:= $(flexCUDA_custom_cflags)
flexCUDA_release_common_cflags    += -MMD
flexCUDA_release_common_cflags    += $(addprefix -D, $(flexCUDA_release_defines))
flexCUDA_release_common_cflags    += $(addprefix -I, $(flexCUDA_release_hpaths))
flexCUDA_release_common_cflags  += -m64
flexCUDA_release_cflags	:= $(flexCUDA_release_common_cflags)
flexCUDA_release_cflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexCUDA_release_cflags  += -O3 -ffast-math -DNDEBUG
flexCUDA_release_cppflags	:= $(flexCUDA_release_common_cflags)
flexCUDA_release_cppflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexCUDA_release_cppflags  += -O3 -ffast-math -DNDEBUG
flexCUDA_release_lflags    := $(flexCUDA_custom_lflags)
flexCUDA_release_lflags    += $(addprefix -L, $(flexCUDA_release_lpaths))
flexCUDA_release_lflags    += -Wl,--start-group $(addprefix -l, $(flexCUDA_release_libraries)) -Wl,--end-group
flexCUDA_release_lflags  += -m64
flexCUDA_release_objsdir  = $(OBJS_DIR)/flexCUDA_release
flexCUDA_release_cpp_o    = $(addprefix $(flexCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(flexCUDA_cppfiles)))))
flexCUDA_release_cc_o    = $(addprefix $(flexCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(flexCUDA_ccfiles)))))
flexCUDA_release_c_o      = $(addprefix $(flexCUDA_release_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(flexCUDA_cfiles)))))
flexCUDA_release_cuda_src_cuda_bvh_cu_o += $(OBJS_DIR)/flexCUDA_release/cuda/src/cudabvh.o
flexCUDA_release_cuda_src_cuda_flex_cu_o += $(OBJS_DIR)/flexCUDA_release/cuda/src/cudaflex.o
flexCUDA_release_cuda_src_cuda_sort_cu_o += $(OBJS_DIR)/flexCUDA_release/cuda/src/cudasort.o
flexCUDA_release_obj      = $(flexCUDA_release_cpp_o) $(flexCUDA_release_cc_o) $(flexCUDA_release_c_o) $(flexCUDA_release_cuda_src_cuda_bvh_cu_o) $(flexCUDA_release_cuda_src_cuda_flex_cu_o) $(flexCUDA_release_cuda_src_cuda_sort_cu_o)
flexCUDA_release_bin      := ./../../../lib/linux64/NvFlexReleaseCUDA_x64.a

clean_flexCUDA_release: 
	@$(ECHO) clean flexCUDA release
	@$(RMDIR) $(flexCUDA_release_objsdir)
	@$(RMDIR) $(flexCUDA_release_bin)
	@$(RMDIR) $(DEPSDIR)/flexCUDA/release

build_flexCUDA_release: postbuild_flexCUDA_release
postbuild_flexCUDA_release: mainbuild_flexCUDA_release
mainbuild_flexCUDA_release: prebuild_flexCUDA_release $(flexCUDA_release_bin)
prebuild_flexCUDA_release:

$(flexCUDA_release_bin): $(flexCUDA_release_obj) 
	mkdir -p `dirname ./../../../lib/linux64/NvFlexReleaseCUDA_x64.a`
	@$(AR) rcs $(flexCUDA_release_bin) $(flexCUDA_release_obj)
	$(ECHO) building $@ complete!

$(flexCUDA_release_cuda_src_cuda_bvh_cu_o): $(flexCUDA_cuda_src_cuda_bvh_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_release/cuda/src/cudabvh.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/bvh.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudabvh.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/bvh.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudabvh.o"

$(flexCUDA_release_cuda_src_cuda_flex_cu_o): $(flexCUDA_cuda_src_cuda_flex_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_release/cuda/src/cudaflex.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/flex.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudaflex.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/flex.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudaflex.o"

$(flexCUDA_release_cuda_src_cuda_sort_cu_o): $(flexCUDA_cuda_src_cuda_sort_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_release/cuda/src/cudasort.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/sort.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudasort.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/sort.cu" -o "$(OBJS_DIR)/flexCUDA_release/cuda/src/cudasort.o"

flexCUDA_release_DEPDIR = $(dir $(@))/$(*F)
$(flexCUDA_release_cpp_o): $(flexCUDA_release_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling release $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexCUDA_release_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cppfiles))))))
	cp $(flexCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cppfiles))))).P; \
	  rm -f $(flexCUDA_release_DEPDIR).d

$(flexCUDA_release_cc_o): $(flexCUDA_release_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling release $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexCUDA_release_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_ccfiles))))))
	cp $(flexCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_ccfiles))))).release.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_ccfiles))))).release.P; \
	  rm -f $(flexCUDA_release_DEPDIR).d

$(flexCUDA_release_c_o): $(flexCUDA_release_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling release $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(flexCUDA_release_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cfiles))))))
	cp $(flexCUDA_release_DEPDIR).d $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_release_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexCUDA/release/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_release_objsdir),, $@))), $(flexCUDA_cfiles))))).P; \
	  rm -f $(flexCUDA_release_DEPDIR).d

flexCUDA_debug_hpaths    := 
flexCUDA_debug_hpaths    += ./../../../../../../external/CUDA/8.0.44-linux/include
flexCUDA_debug_hpaths    += ./../../../../../../external/CUDA/8.0.44-linux/extras/cupti/include
flexCUDA_debug_hpaths    += ./../../..
flexCUDA_debug_lpaths    := 
flexCUDA_debug_lpaths    += ./../../../../../../external/CUDA/8.0.44-linux/lib64
flexCUDA_debug_defines   := $(flexCUDA_custom_defines)
flexCUDA_debug_libraries := 
flexCUDA_debug_libraries += ./../../../lib/linux64/NvFlexDevice_x64.a
flexCUDA_debug_common_cflags	:= $(flexCUDA_custom_cflags)
flexCUDA_debug_common_cflags    += -MMD
flexCUDA_debug_common_cflags    += $(addprefix -D, $(flexCUDA_debug_defines))
flexCUDA_debug_common_cflags    += $(addprefix -I, $(flexCUDA_debug_hpaths))
flexCUDA_debug_common_cflags  += -m64
flexCUDA_debug_cflags	:= $(flexCUDA_debug_common_cflags)
flexCUDA_debug_cflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexCUDA_debug_cflags  += -g -O0
flexCUDA_debug_cppflags	:= $(flexCUDA_debug_common_cflags)
flexCUDA_debug_cppflags  += -Wall -std=c++0x -fPIC -fpermissive -fno-strict-aliasing
flexCUDA_debug_cppflags  += -g -O0
flexCUDA_debug_lflags    := $(flexCUDA_custom_lflags)
flexCUDA_debug_lflags    += $(addprefix -L, $(flexCUDA_debug_lpaths))
flexCUDA_debug_lflags    += -Wl,--start-group $(addprefix -l, $(flexCUDA_debug_libraries)) -Wl,--end-group
flexCUDA_debug_lflags  += -m64
flexCUDA_debug_objsdir  = $(OBJS_DIR)/flexCUDA_debug
flexCUDA_debug_cpp_o    = $(addprefix $(flexCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(flexCUDA_cppfiles)))))
flexCUDA_debug_cc_o    = $(addprefix $(flexCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cc, %.cc.o, $(flexCUDA_ccfiles)))))
flexCUDA_debug_c_o      = $(addprefix $(flexCUDA_debug_objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.c, %.c.o, $(flexCUDA_cfiles)))))
flexCUDA_debug_cuda_src_cuda_bvh_cu_o += $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudabvh.o
flexCUDA_debug_cuda_src_cuda_flex_cu_o += $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudaflex.o
flexCUDA_debug_cuda_src_cuda_sort_cu_o += $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudasort.o
flexCUDA_debug_obj      = $(flexCUDA_debug_cpp_o) $(flexCUDA_debug_cc_o) $(flexCUDA_debug_c_o) $(flexCUDA_debug_cuda_src_cuda_bvh_cu_o) $(flexCUDA_debug_cuda_src_cuda_flex_cu_o) $(flexCUDA_debug_cuda_src_cuda_sort_cu_o)
flexCUDA_debug_bin      := ./../../../lib/linux64/NvFlexDebugCUDA_x64.a

clean_flexCUDA_debug: 
	@$(ECHO) clean flexCUDA debug
	@$(RMDIR) $(flexCUDA_debug_objsdir)
	@$(RMDIR) $(flexCUDA_debug_bin)
	@$(RMDIR) $(DEPSDIR)/flexCUDA/debug

build_flexCUDA_debug: postbuild_flexCUDA_debug
postbuild_flexCUDA_debug: mainbuild_flexCUDA_debug
mainbuild_flexCUDA_debug: prebuild_flexCUDA_debug $(flexCUDA_debug_bin)
prebuild_flexCUDA_debug:

$(flexCUDA_debug_bin): $(flexCUDA_debug_obj) 
	mkdir -p `dirname ./../../../lib/linux64/NvFlexDebugCUDA_x64.a`
	@$(AR) rcs $(flexCUDA_debug_bin) $(flexCUDA_debug_obj)
	$(ECHO) building $@ complete!

$(flexCUDA_debug_cuda_src_cuda_bvh_cu_o): $(flexCUDA_cuda_src_cuda_bvh_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudabvh.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/bvh.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudabvh.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/bvh.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudabvh.o"

$(flexCUDA_debug_cuda_src_cuda_flex_cu_o): $(flexCUDA_cuda_src_cuda_flex_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudaflex.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/flex.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudaflex.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/flex.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudaflex.o"

$(flexCUDA_debug_cuda_src_cuda_sort_cu_o): $(flexCUDA_cuda_src_cuda_sort_cu) 
	@mkdir -p `dirname $(OBJS_DIR)/flexCUDA_debug/cuda/src/cudasort.o`
	$(ECHO) ../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/sort.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudasort.o"
	../../../../../../external/CUDA/8.0.44-linux/bin/nvcc -O3 -g -arch=sm_30 -m64 -Xcompiler -fPIC -D_FORCE_INLINES  -I../../.. -I../../../external -I../../../../../../external/CUDA/8.0.44-linux/include -I../../../external/cub-1.3.2  --compile "../../../src/cuda/sort.cu" -o "$(OBJS_DIR)/flexCUDA_debug/cuda/src/cudasort.o"

flexCUDA_debug_DEPDIR = $(dir $(@))/$(*F)
$(flexCUDA_debug_cpp_o): $(flexCUDA_debug_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling debug $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cppfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexCUDA_debug_cppflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cppfiles)) -o $@
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cppfiles))))))
	cp $(flexCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cppfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cppfiles))))).P; \
	  rm -f $(flexCUDA_debug_DEPDIR).d

$(flexCUDA_debug_cc_o): $(flexCUDA_debug_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling debug $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_ccfiles))...
	mkdir -p $(dir $(@))
	$(CXX) $(flexCUDA_debug_cppflags) -c $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_ccfiles)) -o $@
	mkdir -p $(dir $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_ccfiles))))))
	cp $(flexCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_ccfiles))))).debug.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .cc.o,.cc, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_ccfiles))))).debug.P; \
	  rm -f $(flexCUDA_debug_DEPDIR).d

$(flexCUDA_debug_c_o): $(flexCUDA_debug_objsdir)/%.o:
	$(ECHO) flexCUDA: compiling debug $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cfiles))...
	mkdir -p $(dir $(@))
	$(CC) $(flexCUDA_debug_cflags) -c $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cfiles)) -o $@ 
	@mkdir -p $(dir $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cfiles))))))
	cp $(flexCUDA_debug_DEPDIR).d $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cfiles))))).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(flexCUDA_debug_DEPDIR).d >> $(addprefix $(DEPSDIR)/flexCUDA/debug/, $(subst ./, , $(subst ../, , $(filter %$(strip $(subst .c.o,.c, $(subst $(flexCUDA_debug_objsdir),, $@))), $(flexCUDA_cfiles))))).P; \
	  rm -f $(flexCUDA_debug_DEPDIR).d

clean_flexCUDA:  clean_flexCUDA_release clean_flexCUDA_debug
	rm -rf $(DEPSDIR)

export VERBOSE
ifndef VERBOSE
.SILENT:
endif
