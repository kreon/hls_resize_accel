/*
 * Copyright 2022 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _XF_RESIZE_CONFIG_
#define _XF_RESIZE_CONFIG_

#include "hls_stream.h"
#include "ap_int.h"
#include "common/xf_common.hpp"
#include "imgproc/xf_resize.hpp"

#define WIDTH 800
// Maximum Input image width
#define HEIGHT 600
// Maximum Input image height

#define NEWWIDTH 1280
// Maximum output image width
#define NEWHEIGHT 720
// Maximum output image height

#define XF_CV_DEPTH_IN 2
#define XF_CV_DEPTH_OUT 2

#define NPPCX XF_NPPC1

#define IN_TYPE XF_8UC1
#define OUT_TYPE IN_TYPE//XF_8UC1

#define CV_IN_TYPE CV_8UC1
#define CV_OUT_TYPE CV_IN_TYPE//CV_16UC1

// For Nearest Neighbor & Bilinear Interpolation, max down scale factor 2 for all 1-pixel modes, and for upscale in x
// direction
#define MAXDOWNSCALE 2

#define RGB 0
#define GRAY 1

/* Interpolation type*/
#define INTERPOLATION 1
// 0 - Nearest Neighbor Interpolation
// 1 - Bilinear Interpolation
// 2 - AREA Interpolation

#define XF_USE_URAM 0

/* Input image Dimensions */

#define INPUT_PTR_WIDTH 24
#define OUTPUT_PTR_WIDTH 24
#define PTR_WIDTH   INPUT_PTR_WIDTH

typedef ap_axiu<PTR_WIDTH, 0, 0, 0> trans_pkt;

void resize_accel(hls::stream<trans_pkt>& inStreamTop,//ap_uint<INPUT_PTR_WIDTH>* img_inp,
                  hls::stream<trans_pkt>& outStreamTop,//ap_uint<OUTPUT_PTR_WIDTH>* img_out,
                  int rows_in,
                  int cols_in,
                  int rows_out,
                  int cols_out);

#endif
