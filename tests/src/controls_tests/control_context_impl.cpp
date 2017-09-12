#include "controls_tests/control_context_impl.h"

namespace ifx {

ControlContextImpl::ControlContextImpl() {}

ControlContextImpl::~ControlContextImpl() {}

bool ControlContextImpl::InitAndSetupNativeCallbacks(void *) {
    return true;
};

bool ControlContextImpl::Terminate() {
    return true;
}

}