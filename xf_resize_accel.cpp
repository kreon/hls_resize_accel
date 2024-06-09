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

#include "xf_resize_accel_config.h"

//static constexpr int __XF_DEPTH = (HEIGHT * WIDTH * (XF_PIXELWIDTH(IN_TYPE, NPPCX)) / 8) / (INPUT_PTR_WIDTH / 8);
//static constexpr int __XF_DEPTH_OUT = \
    (NEWHEIGHT * NEWWIDTH * (XF_PIXELWIDTH(IN_TYPE, NPPCX)) / 8) / (OUTPUT_PTR_WIDTH / 8);

void resize_accel(hls::stream<trans_pkt>& inStreamTop,//ap_uint<INPUT_PTR_WIDTH>* img_inp,
                  hls::stream<trans_pkt>& outStreamTop,//ap_uint<OUTPUT_PTR_WIDTH>* img_out,
                  int rows_in,
                  int cols_in,
                  int rows_out,
                  int cols_out) {
// clang-format off
    //#pragma HLS INTERFACE m_axi     port=img_inp  offset=slave bundle=gmem1 depth=__XF_DEPTH
    //#pragma HLS INTERFACE m_axi     port=img_out  offset=slave bundle=gmem2 depth=__XF_DEPTH_OUT
    #pragma HLS INTERFACE axis register_mode = both register port = inStreamTop
    #pragma HLS INTERFACE axis register_mode = both register port = outStreamTop
    #pragma HLS INTERFACE s_axilite port=rows_in              
    #pragma HLS INTERFACE s_axilite port=cols_in              
    #pragma HLS INTERFACE s_axilite port=rows_out              
    #pragma HLS INTERFACE s_axilite port=cols_out              
    #pragma HLS INTERFACE s_axilite port=return
    // clang-format on

    xf::cv::Mat<IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN> in_mat(rows_in, cols_in);
    xf::cv::Mat<OUT_TYPE, NEWHEIGHT, NEWWIDTH, NPPCX, XF_CV_DEPTH_OUT> out_mat(rows_out, cols_out);

// clang-format off
    #pragma HLS DATAFLOW
    // clang-format on

    //template <int PTR_WIDTH, int MAT_T, int ROWS, int COLS, int NPC>
    //xf::cv::axiStrm2xfMat(hls::stream<ap_axiu<PTR_WIDTH, 0, 0, 0> >& srcPtr, xf::cv::Mat<MAT_T,ROWS,COLS,NPC>& dstMat)
    xf::cv::axiStrm2xfMat<INPUT_PTR_WIDTH, IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN>(inStreamTop, in_mat);
    //xf::cv::Array2xfMat<INPUT_PTR_WIDTH, IN_TYPE, HEIGHT, WIDTH, NPPCX, XF_CV_DEPTH_IN>(img_inp, in_mat);
    //template <int PTR_WIDTH, int MAT_T, int ROWS, int COLS, int NPC>
    //void Array2xfMat(ap_uint< PTR_WIDTH > *srcPtr, xf::cv::Mat<MAT_T,ROWS,COLS,NPC,XFCVDEPTH>& dstMat)
    xf::cv::resize<INTERPOLATION, IN_TYPE, HEIGHT, WIDTH, NEWHEIGHT, NEWWIDTH, NPPCX, XF_USE_URAM, MAXDOWNSCALE,
                   XF_CV_DEPTH_IN, XF_CV_DEPTH_OUT>(in_mat, out_mat);
    //xf::cv::xfMat2Array<OUTPUT_PTR_WIDTH, OUT_TYPE, NEWHEIGHT, NEWWIDTH, NPPCX, XF_CV_DEPTH_OUT>(out_mat, img_out);
    xf::cv::xfMat2axiStrm<OUTPUT_PTR_WIDTH, OUT_TYPE, NEWHEIGHT, NEWWIDTH, NPPCX, XF_CV_DEPTH_OUT>(out_mat, outStreamTop);
}
