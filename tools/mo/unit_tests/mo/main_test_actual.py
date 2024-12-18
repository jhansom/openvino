# Copyright (C) 2018-2022 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

import argparse
import unittest
from unittest.mock import patch

import pytest

from openvino.tools.mo.utils.error import FrameworkError


ngraph_available = True
try:
    from openvino.tools.mo.main import main
except Exception:
    ngraph_available = False

ngraph_needed = pytest.mark.skipif(not ngraph_available,
                                   reason="mock MO fe is not available")


class TestMainErrors(unittest.TestCase):
    @patch('argparse.ArgumentParser.parse_args', return_value=argparse.Namespace())
    @patch('openvino.tools.mo.main.driver', side_effect=FrameworkError('FW ERROR MESSAGE'))
    @ngraph_needed
    def test_FrameworkError(self, mock_argparse, mock_driver):
        with self.assertLogs() as logger:
            main(argparse.ArgumentParser(), None, 'framework_string')
            self.assertEqual(logger.output, ['ERROR:root:FW ERROR MESSAGE'])
