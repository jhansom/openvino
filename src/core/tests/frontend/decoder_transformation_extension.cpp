// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <openvino/pass/manager.hpp>

#include "gtest/gtest.h"
#include "openvino/frontend/extension/decoder_transformation.hpp"

using namespace ov::frontend;

TEST(DecoderTransformation, MatcherPass) {
    bool flag = false;
    DecoderTransformationExtension decoder_ext([&](ov::pass::MatcherPass* matcher) {
        flag = true;
    });

    ov::pass::Manager manager;
    decoder_ext.register_pass(manager);
    manager.run_passes(std::make_shared<ov::Model>(ov::ResultVector{}, ov::ParameterVector{}));
    EXPECT_EQ(flag, true);
}

TEST(DecoderTransformation, FunctionPass) {
    bool flag = false;
    DecoderTransformationExtension decoder_ext([&](const std::shared_ptr<ov::Model>&) {
        flag = true;
        return flag;
    });

    ov::pass::Manager manager;
    decoder_ext.register_pass(manager);
    manager.run_passes(std::make_shared<ov::Model>(ov::ResultVector{}, ov::ParameterVector{}));
    EXPECT_EQ(flag, true);
}

TEST(DecoderTransformation, TestPass) {
    class TestPass : public ov::pass::ModelPass {
    public:
        OPENVINO_RTTI("ov::pass::TestPass");
        TestPass() = default;
        TestPass(const TestPass& tp) = default;
        bool run_on_model(const std::shared_ptr<ov::Model>&) override {
            *m_flag = true;
            return *m_flag;
        }
        std::shared_ptr<bool> m_flag = std::make_shared<bool>(false);
    } test_pass;
    DecoderTransformationExtension decoder_ext(test_pass);

    ov::pass::Manager manager;
    decoder_ext.register_pass(manager);
    manager.run_passes(std::make_shared<ov::Model>(ov::ResultVector{}, ov::ParameterVector{}));
    EXPECT_EQ(*test_pass.m_flag, true);
}
