/*==============================================================================
Copyright(c) 2020 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and / or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
============================================================================*/


#include "GmmCachePolicyConditionals.h"

#define EDRAM (SKU(FtrEDram))
#define FBLLC (SKU(FtrFrameBufferLLC))
#define L1    (!WA(Wa_1606955757))

//Macros for segment-preference
#define NoP    0x0
#define SYS    0x1
#define LOC    0x2
#define LoP    0x3
#define SyP    0x4

// Cache Policy Definition
// L3_SCC = L3 skip caching control (disabled if L3_SCC = 0)
// HDCL1 = HDC L1 cache control (1 = cached in HDC L1, 0 = not cached in HDC L1)
// Faster PushWrite(Gen10+) used iff !WT, eLLC-only cacheable - Globally visible surface (eg display surface) should be marked WT
// GO = Global observable point for L3-uncached (0=Default is L3, 1= Memory)// GO = Global observable point for L3-uncached (0=Default is L3, 1= Memory)
// UcLookup = Snoop L3 for uncached (0=Default is no-snoop, 1 =Snoop)
// L1CC: L1 cache control (0: WBP write bypass mode, 1: UC uncached, 2: WB Write back, 3:WT write-through, 4: WS Write-Streaming) : Valid only for DG2
//***********************************************************************************************************************************************************/
//                   USAGE TYPE                                                               , L3 , L3_SCC, HDCL1, GO,  UcLookup, L1CC)
/************************************************************************************************************************************************************/

// KMD Usages
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_BATCH_BUFFER                                          , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_COMP_FRAME_BUFFER                                     , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CONTEXT_SWITCH_BUFFER                                 , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CURSOR                                                , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DISPLAY_STATIC_IMG_FOR_SMOOTH_ROTATION_BUFFER         , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DUMMY_PAGE                                            , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_GDI_SURFACE                                           , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_GENERIC_KMD_RESOURCE                                  , 0  ,  0   ,    0,    0,   1,    1);
// GMM_RESOURCE_USAGE_GFX_RING is only used if WaEnableRingHostMapping is enabled.
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_GFX_RING                                              , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_GTT_TRANSFER_REGION                                   , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HW_CONTEXT                                            , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STATE_MANAGER_KERNEL_STATE                            , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_KMD_STAGING_SURFACE                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MBM_BUFFER                                            , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_NNDI_BUFFER                                           , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OVERLAY_MBM                                           , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PRIMARY_SURFACE                                       , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SCREEN_PROTECTION_INTERMEDIATE_SURFACE                , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SHADOW_SURFACE                                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SM_SCRATCH_STATE                                      , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STATUS_PAGE                                           , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TIMER_PERF_QUEUE                                      , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_UNKNOWN                                               , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_UNMAP_PAGING_RESERVED_GTT_DMA_BUFFER                  , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VSC_BATCH_BUFFER                                      , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_WA_BATCH_BUFFER                                       , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_KMD_OCA_BUFFER                                        , 0  ,  0   ,    0,    0,   1,    1);

//
// 3D Usages
//
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_UMD_BATCH_BUFFER                                      , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_BINDING_TABLE_POOL                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CCS                                                   , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CONSTANT_BUFFER_POOL                                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DEPTH_BUFFER                                          , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DISPLAYABLE_RENDER_TARGET                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_GATHER_POOL                                           , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_SURFACE_STATE                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_DYNAMIC_STATE                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_GENERAL_STATE                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_GENERAL_STATE_UC                                 , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_STATELESS_DATA_PORT                              , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_STATELESS_DATA_PORT_L1_CACHED                    , 1  ,  0   ,   L1,    0,   1,    2);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_INDIRECT_OBJECT                                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HEAP_INSTRUCTION                                      , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HIZ                                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_INDEX_BUFFER                                          , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_INDEX_BUFFER_L3_COHERENT_UC                           , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_INDEX_BUFFER_L3_CACHED                                , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MCS                                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PUSH_CONSTANT_BUFFER                                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PULL_CONSTANT_BUFFER                                  , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_QUERY                                                 , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_RENDER_TARGET                                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SHADER_RESOURCE                                       , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STAGING                                               , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STENCIL_BUFFER                                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STREAM_OUTPUT_BUFFER                                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILE_POOL                                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SHADER_RESOURCE_LLC_BYPASS                            , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MOCS_62                                               , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_L3_EVICTION                                           , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_L3_EVICTION_SPECIAL                                   , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PROCEDURAL_TEXTURE                                    , 1  ,  0   ,    0,    0,   1,    1);

// Tiled Resource
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_DEPTH_BUFFER                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_HIZ                                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_MCS                                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_CCS                                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_RENDER_TARGET                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_RENDER_TARGET_AND_SHADER_RESOURCE               , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_SHADER_RESOURCE                                 , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILED_UAV                                             , 1  ,  0   ,    0,    0,   1,    1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_UAV                                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VERTEX_BUFFER                                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VERTEX_BUFFER_L3_COHERENT_UC                          , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VERTEX_BUFFER_L3_CACHED                               , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OGL_WSTN_VERTEX_BUFFER                                , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_POSH_VERTEX_BUFFER                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_RENDER_TARGET_AND_SHADER_RESOURCE                     , 1  ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_WDDM_HISTORY_BUFFER                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CONTEXT_SAVE_RESTORE                                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PTBR_PAGE_POOL                                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PTBR_BATCH_BUFFER                                     , 1  ,  0   ,    0,    0,   1,    1);

//
// CM USAGES
//
//                   USAGE TYPE                                                               , L3 , L3_SCC, HDCL1, GO, UcLookup,  L1CC)
DEFINE_CACHE_ELEMENT(CM_RESOURCE_USAGE_SurfaceState,                                            1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(CM_RESOURCE_USAGE_L1_Enabled_SurfaceState,                                 1  ,  0   ,    1,    0,   1,    2);
DEFINE_CACHE_ELEMENT(CM_RESOURCE_USAGE_StateHeap,                                               1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(CM_RESOURCE_USAGE_NO_L3_SurfaceState,                                      0  ,  0   ,    1,    0,   1,    1);
DEFINE_CACHE_ELEMENT(CM_RESOURCE_USAGE_NO_CACHE_SurfaceState,                                   0  ,  0   ,    0,    1,   0,    1);

//
// MP USAGES
//
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_BEGIN,                                                   0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_DEFAULT,                                                 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_DEFAULT_FF,                                              0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_DEFAULT_RCS,                                             0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_SurfaceState,                                            1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_SurfaceState_FF,                                         0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_SurfaceState_RCS,                                        1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(MP_RESOURCE_USAGE_END,                                                     0  ,  0   ,    0,    1,   0,    1);

// MHW - SFC
DEFINE_CACHE_ELEMENT(MHW_RESOURCE_USAGE_Sfc_CurrentOutputSurface,                               0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MHW_RESOURCE_USAGE_Sfc_AvsLineBufferSurface,                               0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(MHW_RESOURCE_USAGE_Sfc_IefLineBufferSurface,                               0  ,  0   ,    0,    1,   0,    1);

//Media GMM Resource USAGES
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PRE_DEBLOCKING_CODEC                                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_POST_DEBLOCKING_CODEC                                 , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_ORIGINAL_UNCOMPRESSED_PICTURE_ENCODE                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_ORIGINAL_UNCOMPRESSED_PICTURE_DECODE                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_STREAMOUT_DATA_CODEC                                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_INTRA_ROWSTORE_SCRATCH_BUFFER_CODEC                   , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DEBLOCKINGFILTER_ROWSTORE_SCRATCH_BUFFER_CODEC        , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_REFERENCE_PICTURE_CODEC                               , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MACROBLOCK_STATUS_BUFFER_CODEC                        , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MFX_INDIRECT_BITSTREAM_OBJECT_DECODE                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MFX_INDIRECT_MV_OBJECT_CODEC                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MFD_INDIRECT_IT_COEF_OBJECT_DECODE                    , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MFC_INDIRECT_PAKBASE_OBJECT_CODEC                     , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_BSDMPC_ROWSTORE_SCRATCH_BUFFER_CODEC                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MPR_ROWSTORE_SCRATCH_BUFFER_CODEC                     , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_BITPLANE_READ_CODEC                                   , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_AACSBIT_VECTOR_CODEC                                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DIRECTMV_BUFFER_CODEC                                 , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_CURR_ENCODE                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_REF_ENCODE                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MV_DATA_ENCODE                                , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_HME_DOWNSAMPLED_ENCODE                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_HME_DOWNSAMPLED_ENCODE_FF                     , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_HME_DOWNSAMPLED_ENCODE_DST                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ME_DISTORTION_ENCODE                          , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_BRC_ME_DISTORTION_ENCODE                      , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PAK_OBJECT_ENCODE                                     , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_FLATNESS_CHECK_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MBENC_CURBE_ENCODE                            , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VDENC_ROW_STORE_BUFFER_CODEC                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VDENC_STREAMIN_CODEC                                  , 0  ,  0   ,    0,    1,   0,    1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_MD_CODEC                                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_SAO_CODEC                                         , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_MV_CODEC                                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_STATUS_ERROR_CODEC                                , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_LCU_ILDB_STREAMOUT_CODEC                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VP9_PROBABILITY_BUFFER_CODEC                          , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VP9_SEGMENT_ID_BUFFER_CODEC                           , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VP9_HVD_ROWSTORE_BUFFER_CODEC                         , 0  ,  0   ,    0,    1,   0,    1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MACROBLOCK_ILDB_STREAM_OUT_BUFFER_CODEC               , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SSE_SRC_PIXEL_ROW_STORE_BUFFER_CODEC                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SLICE_STATE_STREAM_OUT_BUFFER_CODEC                   , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CABAC_SYNTAX_STREAM_OUT_BUFFER_CODEC                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PRED_COL_STORE_BUFFER_CODEC                           , 0  ,  0   ,    0,    1,   0,    1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_UNCACHED                                      , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ELLC_ONLY                                     , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ELLC_LLC_ONLY                                 , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ELLC_LLC_L3                                   , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_CCS_MEDIA_WRITABLE                                    , 0  ,  0   ,    0,    1,   0,    1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_BRC_HISTORY_ENCODE                            , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_SOFTWARE_SCOREBOARD_ENCODE                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ME_MV_DATA_ENCODE                             , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MV_DISTORTION_ENCODE                          , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_4XME_DISTORTION_ENCODE                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_INTRA_DISTORTION_ENCODE                       , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MB_STATS_ENCODE                                       , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_PAK_STATS_ENCODE                              , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_PIC_STATE_READ_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_PIC_STATE_WRITE_ENCODE                        , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_COMBINED_ENC_ENCODE                           , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_BRC_CONSTANT_DATA_ENCODE                      , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_INTERMEDIATE_CU_RECORD_SURFACE_ENCODE         , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_SCRATCH_ENCODE                                , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_LCU_LEVEL_DATA_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_HISTORY_INPUT_ENCODE                      , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_HISTORY_OUTPUT_ENCODE                     , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_DEBUG_ENCODE                                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_CONSTANT_TABLE_ENCODE                     , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_CU_RECORD_ENCODE                          , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_MV_TEMPORAL_BUFFER_ENCODE                 , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_CU_PACKET_FOR_PAK_ENCODE                  , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_BCOMBINED1_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_ENC_BCOMBINED2_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_FRAME_STATS_STREAMOUT_DATA_CODEC                      , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DEBLOCKINGFILTER_ROWSTORE_TILE_LINE_BUFFER_CODEC      , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_DEBLOCKINGFILTER_ROWSTORE_TILE_COLUMN_BUFFER_CODEC    , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_MD_TILE_LINE_CODEC                                , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_MD_TILE_COLUMN_CODEC                              , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_SAO_TILE_LINE_CODEC                               , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HCP_SAO_TILE_COLUMN_CODEC                             , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_VP9_PROBABILITY_COUNTER_BUFFER_CODEC                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_HUC_VIRTUAL_ADDR_REGION_BUFFER_CODEC                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SIZE_STREAMOUT_CODEC                                  , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_COMPRESSED_HEADER_BUFFER_CODEC                        , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_PROBABILITY_DELTA_BUFFER_CODEC                        , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILE_RECORD_BUFFER_CODEC                              , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_TILE_SIZE_STAS_BUFFER_CODEC                           , 0  ,  0   ,    0,    1,   0,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MAD_ENCODE                                    , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_PAK_IMAGESTATE_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MBENC_BRC_ENCODE                              , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_MB_BRC_CONST_ENCODE                           , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_BRC_MB_QP_ENCODE                              , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_BRC_ROI_ENCODE                                , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_MBDISABLE_SKIPMAP_CODEC                               , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_SLICE_MAP_ENCODE                              , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_WP_DOWNSAMPLED_ENCODE                         , 1  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_SURFACE_VDENC_IMAGESTATE_ENCODE                       , 0  ,  0   ,    0,    1,   0,    1);

/**********************************************************************************/

//
// OCL Usages
//
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_BUFFER                                            , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_BUFFER_CONST                                      , 1 ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_BUFFER_CSR_UC                                     , 0 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_BUFFER_CACHELINE_MISALIGNED                       , 0 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_IMAGE                                             , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_INLINE_CONST                                      , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_INLINE_CONST_HDC                                  , 1 ,  0   ,    1,    0,   1,    0);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_SCRATCH                                           , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_PRIVATE_MEM                                       , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_PRINTF_BUFFER                                     , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_STATE_HEAP_BUFFER                                 , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_SYSTEM_MEMORY_BUFFER                              , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_SYSTEM_MEMORY_BUFFER_CACHELINE_MISALIGNED         , 0 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_ISH_HEAP_BUFFER                                   , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_TAG_MEMORY_BUFFER                                 , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_TEXTURE_BUFFER                                    , 1 ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_OCL_SELF_SNOOP_BUFFER                                 , 1 ,  0   ,    0,    0,   1,    1);
/**********************************************************************************/

// Cross Adapter
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_XADAPTER_SHARED_RESOURCE                              , 1  ,  0   ,    0,    0,   1,   1);

DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_KMD_NULL_CONTEXT_BB                                   , 0  ,  0   ,    0,    0,   1,    1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_COMMAND_STREAMER                                      , 0  ,  0   ,    0,    1,   1,    1);

/**********************************************************************************/
// Uncacheable copies
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_COPY_SOURCE                                           , 0   , 0    ,   0  ,  1 ,  0,   1);
DEFINE_CACHE_ELEMENT(GMM_RESOURCE_USAGE_COPY_DEST                                             , 0   , 0    ,   0  ,  1 ,  0,   1);

#include "GmmCachePolicyUndefineConditionals.h"

