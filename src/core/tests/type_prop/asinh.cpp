// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "unary_ops.hpp"

using Type = ::testing::Types<ngraph::op::Asinh>;

INSTANTIATE_TYPED_TEST_SUITE_P(type_prop_asinh, UnaryOperator, Type);
