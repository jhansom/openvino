// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "kernel_base_opencl.h"
#include "kernel_selector_params.h"

namespace kernel_selector {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gather_tree_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct gather_tree_params : public base_params {
    gather_tree_params() : base_params(KernelType::GATHER_TREE) {}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gather_tree_optional_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct gather_tree_optional_params : optional_params {
    gather_tree_optional_params() : optional_params(KernelType::GATHER_TREE) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BorderKernelBase
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GatherTreeKernelBase : public KernelBaseOpenCL {
public:
    using KernelBaseOpenCL::KernelBaseOpenCL;
    using DispatchData = CommonDispatchData;

    protected:
        JitConstants GetJitConstants(const gather_tree_params& params) const;
        DispatchData SetDefault(const gather_tree_params& params) const;
        KernelsData GetCommonKernelsData(const Params& params, const optional_params&) const;
};
}  // namespace kernel_selector
