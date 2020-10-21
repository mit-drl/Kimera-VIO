/* ----------------------------------------------------------------------------
 * Copyright 2017, Massachusetts Institute of Technology,
 * Cambridge, MA 02139
 * All Rights Reserved
 * Authors: Luca Carlone, et al. (see THANKS for the full author list)
 * See LICENSE for the license information
 * -------------------------------------------------------------------------- */

/**
 * @file   StereoPipeline.h
 * @brief  Implements StereoVIO pipeline workflow.
 * @author Antoni Rosinol
 * @author Marcus Abate
 */

#pragma once

#include "kimera-vio/dataprovider/StereoDataProviderModule.h"
#include "kimera-vio/frontend/StereoCamera.h"
#include "kimera-vio/pipeline/Pipeline.h"

namespace VIO {

class StereoPipeline : public Pipeline {
 public:
  KIMERA_POINTER_TYPEDEFS(StereoPipeline);
  KIMERA_DELETE_COPY_CONSTRUCTORS(StereoPipeline);
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  /**
     * @brief StereoPipeline
     * @param params Vio parameters
     * @param visualizer Optional visualizer for visualizing 3D results
     * @param displayer Optional displayer for visualizing 2D results
     */
  StereoPipeline(const VioParams& params,
                 Visualizer3D::UniquePtr&& visualizer = nullptr,
                 DisplayBase::UniquePtr&& displayer = nullptr);

  ~StereoPipeline() = default;

 public:
  inline void fillRightFrameQueue(Frame::UniquePtr right_frame) {
    CHECK(data_provider_module_);
    CHECK(right_frame);
    StereoDataProviderModule::UniquePtr stereo_dataprovider =
        VIO::safeCast<MonoDataProviderModule, StereoDataProviderModule>(
            std::move(data_provider_module_));
    stereo_dataprovider->fillRightFrameQueue(std::move(right_frame));
    data_provider_module_ =
        VIO::safeCast<StereoDataProviderModule, MonoDataProviderModule>(
            std::move(stereo_dataprovider));
  }
  inline void fillRightFrameQueueBlockingIfFull(Frame::UniquePtr right_frame) {
    CHECK(data_provider_module_);
    CHECK(right_frame);
    StereoDataProviderModule::UniquePtr stereo_dataprovider =
        VIO::safeCast<MonoDataProviderModule, StereoDataProviderModule>(
            std::move(data_provider_module_));
    stereo_dataprovider->fillRightFrameQueueBlockingIfFull(
        std::move(right_frame));
    data_provider_module_ =
        VIO::safeCast<StereoDataProviderModule, MonoDataProviderModule>(
            std::move(stereo_dataprovider));
  }

 protected:
  //! Definition of sensor rig used
  StereoCamera::ConstPtr stereo_camera_;
};

}  // namespace VIO
