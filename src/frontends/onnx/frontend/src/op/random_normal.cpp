// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "utils/random_normal.hpp"

#include "exceptions.hpp"
#include "ngraph/shape.hpp"
#include "utils/common.hpp"

namespace ngraph {
namespace onnx_import {
namespace op {
namespace set_1 {

OutputVector random_normal(const Node& node) {
    CHECK_VALID_NODE(node, node.has_attribute("shape"), "RandomNormal operator must specify a 'shape' attribute.");

    const auto dtype =
        node.get_attribute_value<int64_t>("dtype", static_cast<int64_t>(ONNX_NAMESPACE::TensorProto_DataType_FLOAT));
    const auto target_type = common::get_ngraph_element_type(dtype);

    const auto mean = node.get_attribute_value<float>("mean", 0.0f);
    const auto scale = node.get_attribute_value<float>("scale", 1.0f);
    const auto seed = node.get_attribute_value<float>("seed", 0);

    const auto shape_dims = node.get_attribute_value<std::vector<int64_t>>("shape");
    const auto shape = default_opset::Constant::create(element::i64, {shape_dims.size()}, shape_dims);

    return detail::make_random_normal(shape, target_type, mean, scale, seed);
}

}  // namespace set_1
}  // namespace op
}  // namespace onnx_import
}  // namespace ngraph
