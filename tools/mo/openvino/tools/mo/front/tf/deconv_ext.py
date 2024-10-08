# Copyright (C) 2018-2022 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

from openvino.tools.mo.front.common.partial_infer.utils import convert_deconv_tf_padding_to_str, int64_array
from openvino.tools.mo.front.extractor import FrontExtractorOp
from openvino.tools.mo.front.tf.extractors.utils import tf_data_format_spatial, tf_data_format_channel, tf_data_format_batch, \
    tf_int_list
from openvino.tools.mo.ops.deconvolution import Deconvolution
from openvino.tools.mo.ops.op import PermuteAttrs


class Conv2DBackpropInputFrontExtractor(FrontExtractorOp):
    op = 'Conv2DBackpropInput'
    enabled = True

    @classmethod
    def extract(cls, node):
        attrs = tf_create_attrs(node, 3, 2)
        attrs.update({'op': cls.op,
                      'get_weights_permute': PermuteAttrs.Permutation(perm=int64_array([3, 2, 0, 1]),
                                                                      inv=int64_array([2, 3, 1, 0])),
                      'swap_0_and_2_inputs': True,
                      'shape_input': True,
                      })

        # update the attributes of the node
        Deconvolution.update_node_stat(node, attrs)
        return cls.enabled


class Conv3DBackpropInputV2InputFrontExtractor(FrontExtractorOp):
    op = 'Conv3DBackpropInputV2'
    enabled = True

    @classmethod
    def extract(cls, node):
        attrs = tf_create_attrs(node, 4, 3)
        attrs.update({'op': cls.op,
                      'get_weights_permute': PermuteAttrs.Permutation(perm=int64_array([4, 3, 0, 1, 2]),
                                                                      inv=int64_array([2, 3, 4, 1, 0])),
                      'swap_0_and_2_inputs': True,
                      'shape_input': True,
                      })

        # update the attributes of the node
        Deconvolution.update_node_stat(node, attrs)
        return cls.enabled


def tf_create_attrs(node, input_feature_channel, output_feature_channel):
    data_format = node.pb.attr["data_format"]

    return {
        'auto_pad': convert_deconv_tf_padding_to_str(node.pb.attr['padding'].s.decode()),
        'bias_addable': True,
        'bias_term': False,
        'spatial_dims': tf_data_format_spatial(data_format),
        'channel_dims': tf_data_format_channel(data_format),
        'batch_dims': tf_data_format_batch(data_format),
        'pad': None,  # will be inferred when input shape is known
        'pad_spatial_shape': None,
        'output_spatial_shape': None,
        'output_shape': None,
        'output': None,
        'stride': tf_int_list(node.pb.attr["strides"].list),
        'type': None,  # don't set type until we are sure it is really translated to correct IR; see infer function
        'group': None,
        'layout': data_format.s.decode(),
        'input_feature_channel': input_feature_channel,
        'output_feature_channel': output_feature_channel,
    }
