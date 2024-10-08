// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "nodes/reference.h"
#include "nodes/shapeof.h"
#include "nodes/batch_to_space.h"
#include "nodes/multiclass_nms.hpp"
#include "nodes/adaptive_pooling.h"
#include "nodes/conv.h"
#include "nodes/roi_align.h"
#include "nodes/lrn.h"
#include "nodes/generic.h"
#include "nodes/experimental_detectron_roifeatureextractor.h"
#include "nodes/eltwise.h"
#include "nodes/reorg_yolo.h"
#include "nodes/pooling.h"
#include "nodes/transpose.h"
#include "nodes/grn.h"
#include "nodes/interpolate.h"
#include "nodes/experimental_detectron_detection_output.h"
#include "nodes/roll.h"
#include "nodes/fake_quantize.h"
#include "nodes/embedding_segments_sum.h"
#include "nodes/region_yolo.h"
#include "nodes/matmul.h"
#include "nodes/detection_output.h"
#include "nodes/reverse_sequence.h"
#include "nodes/pad.h"
#include "nodes/ctc_greedy_decoder_seq_len.h"
#include "nodes/reshape.h"
#include "nodes/psroi_pooling.h"
#include "nodes/memory.hpp"
#include "nodes/bin_conv.h"
#include "nodes/gather_elements.h"
#include "nodes/experimental_detectron_priorgridgenerator.h"
#include "nodes/tile.h"
#include "nodes/mathematics.h"
#include "nodes/normalize.h"
#include "nodes/proposal.h"
#include "nodes/tensoriterator.h"
#include "nodes/fullyconnected.h"
#include "nodes/extract_image_patches.h"
#include "nodes/ctc_loss.h"
#include "nodes/reorder.h"
#include "nodes/gather_nd.h"
#include "nodes/shuffle_channels.h"
#include "nodes/bucketize.h"
#include "nodes/space_to_depth.h"
#include "nodes/concat.h"
#include "nodes/softmax.h"
#include "nodes/space_to_batch.h"
#include "nodes/select.h"
#include "nodes/topk.h"
#include "nodes/broadcast.h"
#include "nodes/matrix_nms.h"
#include "nodes/mvn.h"
#include "nodes/gather.h"
#include "nodes/scatter_update.h"
#include "nodes/gather_tree.h"
#include "nodes/def_conv.h"
#include "nodes/embedding_bag_offset_sum.h"
#include "nodes/deconv.h"
#include "nodes/roi_pooling.h"
#include "nodes/range.h"
#include "nodes/split.h"
#include "nodes/one_hot.h"
#include "nodes/log_softmax.h"
#include "nodes/strided_slice.h"
#include "nodes/dft.h"
#include "nodes/non_max_suppression.h"
#include "nodes/convert.h"
#include "nodes/rnn.h"
#include "nodes/experimental_detectron_topkrois.h"
#include "nodes/cum_sum.h"
#include "nodes/depth_to_space.h"
#include "nodes/input.h"
#include "nodes/experimental_detectron_generate_proposals_single_image.h"
#include "nodes/embedding_bag_packed_sum.h"
#include "nodes/reduce.h"
#include "nodes/if.h"
#include "nodes/ctc_greedy_decoder.h"
#include "nodes/non_zero.h"
#include "nodes/color_convert.h"
#include "nodes/subgraph.h"
#include "nodes/priorbox.h"
#include "nodes/priorbox_clustered.h"

#define MKLDNN_NODE(__prim, __type) \
    registerNodeIfRequired(intel_cpu, __prim, __type, MKLDNNNodeImpl<__prim>)

ov::intel_cpu::MKLDNNNode::NodesFactory::NodesFactory()
    : Factory("NodesFactory") {
    MKLDNN_NODE(MKLDNNGenericNode, Generic);
    MKLDNN_NODE(MKLDNNCumSumNode, CumSum);
    MKLDNN_NODE(MKLDNNConvolutionNode, Convolution);
    MKLDNN_NODE(MKLDNNSpaceToBatchNode, SpaceToBatch);
    MKLDNN_NODE(MKLDNNLrnNode, Lrn);
    MKLDNN_NODE(MKLDNNBatchToSpaceNode, BatchToSpace);
    MKLDNN_NODE(MKLDNNNormalizeL2Node, NormalizeL2);
    MKLDNN_NODE(MKLDNNIfNode, If);
    MKLDNN_NODE(MKLDNNProposalNode, Proposal);
    MKLDNN_NODE(MKLDNNBroadcastNode, Broadcast);
    MKLDNN_NODE(MKLDNNExperimentalDetectronTopKROIsNode, ExperimentalDetectronTopKROIs);
    MKLDNN_NODE(MKLDNNReorderNode, Reorder);
    MKLDNN_NODE(MKLDNNBinaryConvolutionNode, BinaryConvolution);
    MKLDNN_NODE(MKLDNNMatrixNmsNode, MatrixNms);
    MKLDNN_NODE(MKLDNNAdaptivePoolingNode, AdaptivePooling);
    MKLDNN_NODE(MKLDNNPoolingNode, Pooling);
    MKLDNN_NODE(MKLDNNReduceNode, Reduce);
    MKLDNN_NODE(MKLDNNEltwiseNode, Eltwise);
    MKLDNN_NODE(MKLDNNSoftMaxNode, Softmax);
    MKLDNN_NODE(MKLDNNEmbeddingBagPackedSumNode, EmbeddingBagPackedSum);
    MKLDNN_NODE(MKLDNNInputNode, Input);
    MKLDNN_NODE(MKLDNNInputNode, Output);
    MKLDNN_NODE(MKLDNNMemoryInputNode, MemoryInput);
    MKLDNN_NODE(MKLDNNMemoryOutputNode, MemoryOutput);
    MKLDNN_NODE(MKLDNNTileNode, Tile);
    MKLDNN_NODE(MKLDNNDFTNode, DFT);
    MKLDNN_NODE(MKLDNNGatherTreeNode, GatherTree);
    MKLDNN_NODE(MKLDNNSpaceToDepthNode, SpaceToDepth);
    MKLDNN_NODE(MKLDNNFullyConnectedNode, FullyConnected);
    MKLDNN_NODE(MKLDNNCTCGreedyDecoderNode, CTCGreedyDecoder);
    MKLDNN_NODE(MKLDNNTransposeNode, Transpose);
    MKLDNN_NODE(MKLDNNDeformableConvolutionNode, DeformableConvolution);
    MKLDNN_NODE(MKLDNNReorgYoloNode, ReorgYolo);
    MKLDNN_NODE(MKLDNNEmbeddingSegmentsSumNode, EmbeddingSegmentsSum);
    MKLDNN_NODE(MKLDNNSelectNode, Select);
    MKLDNN_NODE(MKLDNNShapeOfNode, ShapeOf);
    MKLDNN_NODE(MKLDNNExperimentalDetectronGenerateProposalsSingleImageNode, ExperimentalDetectronGenerateProposalsSingleImage);
    MKLDNN_NODE(MKLDNNReverseSequenceNode, ReverseSequence);
    MKLDNN_NODE(MKLDNNFakeQuantizeNode, FakeQuantize);
    MKLDNN_NODE(MKLDNNNonMaxSuppressionNode, NonMaxSuppression);
    MKLDNN_NODE(MKLDNNExperimentalDetectronPriorGridGeneratorNode, ExperimentalDetectronPriorGridGenerator);
    MKLDNN_NODE(MKLDNNGatherNDNode, GatherND);
    MKLDNN_NODE(MKLDNNLogSoftmaxNode, LogSoftmax);
    MKLDNN_NODE(MKLDNNPSROIPoolingNode, PSROIPooling);
    MKLDNN_NODE(MKLDNNRNN, RNNCell);
    MKLDNN_NODE(MKLDNNRNN, RNNSeq);
    MKLDNN_NODE(MKLDNNCTCLossNode, CTCLoss);
    MKLDNN_NODE(MKLDNNSplitNode, Split);
    MKLDNN_NODE(MKLDNNDetectionOutputNode, DetectionOutput);
    MKLDNN_NODE(MKLDNNGatherElementsNode, GatherElements);
    MKLDNN_NODE(MKLDNNCTCGreedyDecoderSeqLenNode, CTCGreedyDecoderSeqLen);
    MKLDNN_NODE(MKLDNNBucketizeNode, Bucketize);
    MKLDNN_NODE(MKLDNNExperimentalDetectronROIFeatureExtractorNode, ExperimentalDetectronROIFeatureExtractor);
    MKLDNN_NODE(MKLDNNMathNode, Math);
    MKLDNN_NODE(MKLDNNMultiClassNmsNode, MulticlassNms);
    MKLDNN_NODE(MKLDNNConvertNode, Convert);
    MKLDNN_NODE(MKLDNNEmbeddingBagOffsetSumNode, EmbeddingBagOffsetsSum);
    MKLDNN_NODE(MKLDNNRollNode, Roll);
    MKLDNN_NODE(MKLDNNPadNode, Pad);
    MKLDNN_NODE(MKLDNNReshapeNode, Reshape);
    MKLDNN_NODE(MKLDNNMVNNode, MVN);
    MKLDNN_NODE(MKLDNNMatMulNode, MatMul);
    MKLDNN_NODE(MKLDNNScatterUpdateNode, ScatterUpdate);
    MKLDNN_NODE(MKLDNNScatterUpdateNode, ScatterElementsUpdate);
    MKLDNN_NODE(MKLDNNScatterUpdateNode, ScatterNDUpdate);
    MKLDNN_NODE(MKLDNNInterpolateNode, Interpolate);
    MKLDNN_NODE(MKLDNNROIPoolingNode, ROIPooling);
    MKLDNN_NODE(MKLDNNTensorIteratorNode, TensorIterator);
    MKLDNN_NODE(MKLDNNConcatNode, Concatenation);
    MKLDNN_NODE(MKLDNNExtractImagePatchesNode, ExtractImagePatches);
    MKLDNN_NODE(MKLDNNOneHotNode, OneHot);
    MKLDNN_NODE(MKLDNNExperimentalDetectronDetectionOutputNode, ExperimentalDetectronDetectionOutput);
    MKLDNN_NODE(MKLDNNROIAlignNode, ROIAlign);
    MKLDNN_NODE(MKLDNNShuffleChannelsNode, ShuffleChannels);
    MKLDNN_NODE(MKLDNNDepthToSpaceNode, DepthToSpace);
    MKLDNN_NODE(MKLDNNDeconvolutionNode, Deconvolution);
    MKLDNN_NODE(MKLDNNGatherNode, Gather);
    MKLDNN_NODE(MKLDNNRegionYoloNode, RegionYolo);
    MKLDNN_NODE(MKLDNNRangeNode, Range);
    MKLDNN_NODE(MKLDNNTopKNode, TopK);
    MKLDNN_NODE(MKLDNNStridedSliceNode, StridedSlice);
    MKLDNN_NODE(MKLDNNGRNNode, GRN);
    MKLDNN_NODE(MKLDNNNonZeroNode, NonZero);
    MKLDNN_NODE(MKLDNNSnippetNode, Subgraph);
    MKLDNN_NODE(MKLDNNColorConvertNode, ColorConvert);
    MKLDNN_NODE(MKLDNNPriorBoxNode, PriorBox);
    MKLDNN_NODE(MKLDNNPriorBoxClusteredNode, PriorBoxClustered);
}
