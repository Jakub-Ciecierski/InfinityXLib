#include "graphics/shaders/textures/texture_activator.h"

namespace ifx {

TextureActivator::TextureActivator() :
    local_id_start_(0),
    global_id_start_(31),
    local_id_(local_id_start_),
    global_id_(global_id_start_) {
    ResetLocal();
    ResetGlobal();
}

TextureActivator::~TextureActivator() {}

// static
TextureActivator &TextureActivator::GetInstance() {
    static TextureActivator instance;
    return instance;
}

int TextureActivator::GetNextLocalID() {
    return local_id_++;
}

int TextureActivator::GetNextGlobalID() {
    return global_id_++;
}

void TextureActivator::ResetLocal() {
    local_id_ = local_id_start_;
}

void TextureActivator::ResetGlobal() {
    global_id_ = global_id_start_;
}

}
