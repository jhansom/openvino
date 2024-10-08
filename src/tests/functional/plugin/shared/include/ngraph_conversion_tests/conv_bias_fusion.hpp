// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <tuple>
#include <string>
#include <functional>
#include <vector>
#include <memory>

#include "ie_core.hpp"
#include "ngraph/opsets/opset1.hpp"

#include "functional_test_utils/blob_utils.hpp"
#include "common_test_utils/common_utils.hpp"
#include "shared_test_classes/base/layer_test_utils.hpp"

namespace NGraphConversionTestsDefinitions {

class ConvBiasFusion : public CommonTestUtils::TestsCommon, public testing::WithParamInterface<std::string> {
public:
    static std::string getTestCaseName(const testing::TestParamInfo<std::string> & obj);

protected:
    std::string getOutputName() const;
};
}  // namespace NGraphConversionTestsDefinitions
