// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "kernel_base_opencl.h"

namespace kernel_selector {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// space_to_depth_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct space_to_depth_params : public base_params {
    space_to_depth_params() : base_params(KernelType::SPACE_TO_DEPTH), depth_mode(SpaceToDepthMode::BLOCKS_FIRST), block_size(1) {}

    SpaceToDepthMode depth_mode;

    size_t block_size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// space_to_depth_optional_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct space_to_depth_optional_params : optional_params {
    space_to_depth_optional_params() : optional_params(KernelType::SPACE_TO_DEPTH) {}
};

class SpaceToDepthKernelRef : public KernelBaseOpenCL {
public:
    SpaceToDepthKernelRef() : KernelBaseOpenCL("space_to_depth_ref") {}
    virtual ~SpaceToDepthKernelRef() = default;
    KernelsData GetKernelsData(const Params& params, const optional_params& options) const override;
    KernelsPriority GetKernelsPriority(const Params& params, const optional_params& options) const override;
    ParamsKey GetSupportedKey() const override;

protected:
    virtual CommonDispatchData SetDefault(const space_to_depth_params& params, const optional_params&) const;
    virtual JitConstants GetJitConstants(const space_to_depth_params& params) const;
    bool Validate(const Params& p, const optional_params& o) const override;
    std::vector<FusedOpType> GetSupportedFusedOps() const override {
        return { FusedOpType::ELTWISE,
                 FusedOpType::QUANTIZE,
                 FusedOpType::SCALE,
                 FusedOpType::ACTIVATION };
    }
};
}  // namespace kernel_selector
