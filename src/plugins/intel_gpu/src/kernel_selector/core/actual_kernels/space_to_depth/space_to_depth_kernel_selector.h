// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "kernel_selector.h"

namespace kernel_selector {
class space_to_depth_kernel_selector : public kernel_selector_base {
public:
    static space_to_depth_kernel_selector& Instance() {
        static space_to_depth_kernel_selector instance_;
        return instance_;
    }

    space_to_depth_kernel_selector();

    virtual ~space_to_depth_kernel_selector() {}

    KernelsData GetBestKernels(const Params& params, const optional_params& options) const override;
};
}  // namespace kernel_selector
