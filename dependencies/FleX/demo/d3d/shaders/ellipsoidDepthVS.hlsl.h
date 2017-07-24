#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
//
// Buffer Definitions: 
//
// cbuffer constBuf
// {
//
//   struct FluidShaderConst
//   {
//       
//       float4x4 modelViewProjection;  // Offset:    0
//       float4x4 modelView;            // Offset:   64
//       float4x4 projection;           // Offset:  128
//       float4x4 inverseModelView;     // Offset:  192
//       float4x4 inverseProjection;    // Offset:  256
//       float4 invTexScale;            // Offset:  320
//       float3 invViewport;            // Offset:  336
//       float _pad0;                   // Offset:  348
//       float blurRadiusWorld;         // Offset:  352
//       float blurScale;               // Offset:  356
//       float blurFalloff;             // Offset:  360
//       int debug;                     // Offset:  364
//       float3 lightPos;               // Offset:  368
//       float _pad1;                   // Offset:  380
//       float3 lightDir;               // Offset:  384
//       float _pad2;                   // Offset:  396
//       float4x4 lightTransform;       // Offset:  400
//       float4 color;                  // Offset:  464
//       float4 clipPosToEye;           // Offset:  480
//       float spotMin;                 // Offset:  496
//       float spotMax;                 // Offset:  500
//       float ior;                     // Offset:  504
//       float _pad3;                   // Offset:  508
//       float4 shadowTaps[12];         // Offset:  512
//
//   } gParams;                         // Offset:    0 Size:   704
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// constBuf                          cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyz 
// U                        0   xyzw        1     NONE   float   xyzw
// V                        0   xyzw        2     NONE   float   xyzw
// W                        0   xyzw        3     NONE   float   xyzw
// SV_VertexID              0   x           4   VERTID    uint       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// POSITION                 0   xyzw        0     NONE   float   xyzw
// TEXCOORD                 0   xyzw        1     NONE   float   xyzw
// TEXCOORD                 1   xyzw        2     NONE   float   xyzw
// TEXCOORD                 2   xyzw        3     NONE   float   xyzw
// TEXCOORD                 3   xyzw        4     NONE   float   xyzw
// TEXCOORD                 4   xyzw        5     NONE   float   xyzw
// TEXCOORD                 5   xyzw        6     NONE   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[16], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyzw
dcl_input v2.xyzw
dcl_input v3.xyzw
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_output o2.xyzw
dcl_output o3.xyzw
dcl_output o4.xyzw
dcl_output o5.xyzw
dcl_output o6.xyzw
dcl_temps 4
mov o0.xyz, v0.xyzx
mov o0.w, l(1.000000)
mul r0.xyz, v2.wwww, v2.xyzx
mul r1.xyzw, r0.yyyy, cb0[1].wxxy
mad r1.xyzw, cb0[0].wxxy, r0.xxxx, r1.xyzw
mad r0.xyzw, cb0[2].wxxy, r0.zzzz, r1.xyzw
mul r1.x, r0.w, r0.w
mul r0.xyzw, r0.xxzx, r0.xyzw
mul r1.yzw, v1.wwww, v1.xxyz
mul r2.xyzw, r1.zzzz, cb0[1].wxxy
mad r2.xyzw, cb0[0].wxxy, r1.yyyy, r2.xyzw
mad r2.xyzw, cb0[2].wxxy, r1.wwww, r2.xyzw
mad r1.x, r2.w, r2.w, r1.x
mad r0.xyzw, r2.xyzw, r2.xxzx, r0.xyzw
mul r1.yzw, v3.wwww, v3.xxyz
mul r2.xyzw, r1.zzzz, cb0[1].wxxy
mad r2.xyzw, cb0[0].wxxy, r1.yyyy, r2.xyzw
mad r2.xyzw, cb0[2].wxxy, r1.wwww, r2.xyzw
mad r1.x, r2.w, r2.w, r1.x
mad r0.xyzw, r2.xyzw, r2.xxzx, r0.xyzw
mul r2.xyzw, v0.yyyy, cb0[1].wxxy
mad r2.xyzw, cb0[0].wxxy, v0.xxxx, r2.xyzw
mad r2.xyzw, cb0[2].wxxy, v0.zzzz, r2.xyzw
add r2.xyzw, r2.xyzw, cb0[3].wxxy
mad r1.x, -r2.w, r2.w, r1.x
mad r0.xyzw, -r2.xyzw, r2.xxzx, r0.xyzw
mul r1.yzw, r0.yyxw, l(0.000000, -2.000000, 4.000000, -2.000000)
mul r2.xy, r1.ywyy, r1.ywyy
mad r2.y, -r1.z, r1.x, r2.y
mad r1.z, -r1.z, r0.z, r2.x
sqrt r2.x, r2.y
ge r2.y, r2.y, l(0.000000)
lt r2.zw, l(0.000000, 0.000000, -0.000000, -0.000000), r0.yyyw
movc r2.zw, r2.zzzw, l(0,0,-1.000000,-1.000000), l(0,0,1.000000,1.000000)
mad r1.w, r2.w, r2.x, r1.w
mul r1.w, r1.w, l(-0.500000)
div r3.w, r1.w, r0.x
div r3.z, r1.x, r1.w
lt r1.x, r3.z, r3.w
movc r1.xw, r1.xxxx, r3.zzzw, r3.wwwz
and r1.xw, r1.xxxw, r2.yyyy
eq r2.xyw, r0.xyxw, l(0.000000, -0.000000, 0.000000, -0.000000)
and r0.yw, r2.yyyw, r2.xxxx
movc o1.zw, r0.wwww, l(0,0,0,0), r1.xxxw
sqrt r0.w, r1.z
ge r1.x, r1.z, l(0.000000)
mad r0.w, r2.z, r0.w, r1.y
mul r0.w, r0.w, l(-0.500000)
div r2.xy, r0.zwzz, r0.wxww
lt r0.x, r2.x, r2.y
movc r0.xz, r0.xxxx, r2.xxyx, r2.yyxy
and r0.xz, r0.xxzx, r1.xxxx
movc o1.xy, r0.yyyy, l(0,0,0,0), r0.xzxx
mov o2.w, -cb0[12].w
div r0.xyz, v1.xyzx, v1.wwww
dp3 r0.w, r0.xyzx, v0.xyzx
mov r0.w, -r0.w
dp4 o2.x, r0.xyzw, cb0[12].xyzw
div r1.xyz, v2.xyzx, v2.wwww
dp3 r1.w, r1.xyzx, v0.xyzx
mov r1.w, -r1.w
dp4 o2.y, r1.xyzw, cb0[12].xyzw
div r2.xyz, v3.xyzx, v3.wwww
dp3 r2.w, r2.xyzx, v0.xyzx
mov r2.w, -r2.w
dp4 o2.z, r2.xyzw, cb0[12].xyzw
mov o3.w, -cb0[13].w
dp4 o3.x, r0.xyzw, cb0[13].xyzw
dp4 o3.y, r1.xyzw, cb0[13].xyzw
dp4 o3.z, r2.xyzw, cb0[13].xyzw
dp4 o4.x, r0.xyzw, cb0[14].xyzw
dp4 o5.x, r0.xyzw, cb0[15].xyzw
dp4 o4.y, r1.xyzw, cb0[14].xyzw
dp4 o5.y, r1.xyzw, cb0[15].xyzw
dp4 o4.z, r2.xyzw, cb0[14].xyzw
dp4 o5.z, r2.xyzw, cb0[15].xyzw
mov o4.w, -cb0[14].w
mov o5.w, -cb0[15].w
mul r0.xyzw, v0.yyyy, cb0[1].xyzw
mad r0.xyzw, cb0[0].xyzw, v0.xxxx, r0.xyzw
mad r0.xyzw, cb0[2].xyzw, v0.zzzz, r0.xyzw
add r0.xyzw, r0.xyzw, cb0[3].xyzw
div o6.xyzw, r0.xyzw, r0.wwww
ret 
// Approximately 84 instruction slots used
#endif

const BYTE g_ellipsoidDepthVS[] =
{
     68,  88,  66,  67, 251, 213, 
    215, 144,  39,  19, 119, 132, 
      9, 110,  41, 184,   9, 243, 
    116,  11,   1,   0,   0,   0, 
    184,  17,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    112,   4,   0,   0,  20,   5, 
      0,   0, 224,   5,   0,   0, 
     28,  17,   0,   0,  82,  68, 
     69,  70,  52,   4,   0,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   0,   1,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    254, 255,   0,   1,   0,   0, 
      0,   4,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     92,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  99, 111, 110, 115, 
    116,  66, 117, 102,   0, 171, 
    171, 171,  92,   0,   0,   0, 
      1,   0,   0,   0, 128,   0, 
      0,   0, 192,   2,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 168,   0,   0,   0, 
      0,   0,   0,   0, 192,   2, 
      0,   0,   2,   0,   0,   0, 
    220,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    103,  80,  97, 114,  97, 109, 
    115,   0,  70, 108, 117, 105, 
    100,  83, 104,  97, 100, 101, 
    114,  67, 111, 110, 115, 116, 
      0, 109, 111, 100, 101, 108, 
     86, 105, 101, 119,  80, 114, 
    111, 106, 101,  99, 116, 105, 
    111, 110,   0, 102, 108, 111, 
     97, 116,  52, 120,  52,   0, 
    171, 171,   3,   0,   3,   0, 
      4,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 213,   0, 
      0,   0, 109, 111, 100, 101, 
    108,  86, 105, 101, 119,   0, 
    112, 114, 111, 106, 101,  99, 
    116, 105, 111, 110,   0, 105, 
    110, 118, 101, 114, 115, 101, 
     77, 111, 100, 101, 108,  86, 
    105, 101, 119,   0, 105, 110, 
    118, 101, 114, 115, 101,  80, 
    114, 111, 106, 101,  99, 116, 
    105, 111, 110,   0, 105, 110, 
    118,  84, 101, 120,  83,  99, 
     97, 108, 101,   0, 102, 108, 
    111,  97, 116,  52,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  72,   1,   0,   0, 
    105, 110, 118,  86, 105, 101, 
    119, 112, 111, 114, 116,   0, 
    102, 108, 111,  97, 116,  51, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,   1, 
      0,   0,  95, 112,  97, 100, 
     48,   0, 102, 108, 111,  97, 
    116,   0,   0,   0,   3,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 178,   1, 
      0,   0,  98, 108, 117, 114, 
     82,  97, 100, 105, 117, 115, 
     87, 111, 114, 108, 100,   0, 
     98, 108, 117, 114,  83,  99, 
     97, 108, 101,   0,  98, 108, 
    117, 114,  70,  97, 108, 108, 
    111, 102, 102,   0, 100, 101, 
     98, 117, 103,   0, 105, 110, 
    116,   0,   0,   0,   2,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   8,   2, 
      0,   0, 108, 105, 103, 104, 
    116,  80, 111, 115,   0,  95, 
    112,  97, 100,  49,   0, 108, 
    105, 103, 104, 116,  68, 105, 
    114,   0,  95, 112,  97, 100, 
     50,   0, 108, 105, 103, 104, 
    116,  84, 114,  97, 110, 115, 
    102, 111, 114, 109,   0,  99, 
    111, 108, 111, 114,   0,  99, 
    108, 105, 112,  80, 111, 115, 
     84, 111,  69, 121, 101,   0, 
    115, 112, 111, 116,  77, 105, 
    110,   0, 115, 112, 111, 116, 
     77,  97, 120,   0, 105, 111, 
    114,   0,  95, 112,  97, 100, 
     51,   0, 115, 104,  97, 100, 
    111, 119,  84,  97, 112, 115, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
     12,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     72,   1,   0,   0, 193,   0, 
      0,   0, 224,   0,   0,   0, 
      0,   0,   0,   0,   4,   1, 
      0,   0, 224,   0,   0,   0, 
     64,   0,   0,   0,  14,   1, 
      0,   0, 224,   0,   0,   0, 
    128,   0,   0,   0,  25,   1, 
      0,   0, 224,   0,   0,   0, 
    192,   0,   0,   0,  42,   1, 
      0,   0, 224,   0,   0,   0, 
      0,   1,   0,   0,  60,   1, 
      0,   0,  80,   1,   0,   0, 
     64,   1,   0,   0, 116,   1, 
      0,   0, 136,   1,   0,   0, 
     80,   1,   0,   0, 172,   1, 
      0,   0, 184,   1,   0,   0, 
     92,   1,   0,   0, 220,   1, 
      0,   0, 184,   1,   0,   0, 
     96,   1,   0,   0, 236,   1, 
      0,   0, 184,   1,   0,   0, 
    100,   1,   0,   0, 246,   1, 
      0,   0, 184,   1,   0,   0, 
    104,   1,   0,   0,   2,   2, 
      0,   0,  12,   2,   0,   0, 
    108,   1,   0,   0,  48,   2, 
      0,   0, 136,   1,   0,   0, 
    112,   1,   0,   0,  57,   2, 
      0,   0, 184,   1,   0,   0, 
    124,   1,   0,   0,  63,   2, 
      0,   0, 136,   1,   0,   0, 
    128,   1,   0,   0,  72,   2, 
      0,   0, 184,   1,   0,   0, 
    140,   1,   0,   0,  78,   2, 
      0,   0, 224,   0,   0,   0, 
    144,   1,   0,   0,  93,   2, 
      0,   0,  80,   1,   0,   0, 
    208,   1,   0,   0,  99,   2, 
      0,   0,  80,   1,   0,   0, 
    224,   1,   0,   0, 112,   2, 
      0,   0, 184,   1,   0,   0, 
    240,   1,   0,   0, 120,   2, 
      0,   0, 184,   1,   0,   0, 
    244,   1,   0,   0, 128,   2, 
      0,   0, 184,   1,   0,   0, 
    248,   1,   0,   0, 132,   2, 
      0,   0, 184,   1,   0,   0, 
    252,   1,   0,   0, 138,   2, 
      0,   0, 152,   2,   0,   0, 
      0,   2,   0,   0,   5,   0, 
      0,   0,   1,   0, 176,   0, 
      0,   0,  24,   0, 188,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    176,   0,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  54,  46,  51, 
     46,  57,  54,  48,  48,  46, 
     49,  54,  51,  56,  52,   0, 
    171, 171,  73,  83,  71,  78, 
    156,   0,   0,   0,   5,   0, 
      0,   0,   8,   0,   0,   0, 
    128,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   7,   0,   0, 
    137,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  15,  15,   0,   0, 
    139,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  15,  15,   0,   0, 
    141,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,  15,  15,   0,   0, 
    143,   0,   0,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,   4,   0, 
      0,   0,   1,   0,   0,   0, 
     80,  79,  83,  73,  84,  73, 
     79,  78,   0,  85,   0,  86, 
      0,  87,   0,  83,  86,  95, 
     86, 101, 114, 116, 101, 120, 
     73,  68,   0, 171,  79,  83, 
     71,  78, 196,   0,   0,   0, 
      7,   0,   0,   0,   8,   0, 
      0,   0, 176,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,  15,   0, 
      0,   0, 185,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      6,   0,   0,   0,  15,   0, 
      0,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0,  84, 
     69,  88,  67,  79,  79,  82, 
     68,   0, 171, 171,  83,  72, 
     69,  88,  52,  11,   0,   0, 
     80,   0,   1,   0, 205,   2, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     16,   0,   0,   0,  95,   0, 
      0,   3, 114,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      1,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      2,   0,   0,   0,  95,   0, 
      0,   3, 242,  16,  16,   0, 
      3,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      0,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      2,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      3,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      4,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      5,   0,   0,   0, 101,   0, 
      0,   3, 242,  32,  16,   0, 
      6,   0,   0,   0, 104,   0, 
      0,   2,   4,   0,   0,   0, 
     54,   0,   0,   5, 114,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   5, 
    130,  32,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0, 128,  63,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      0,   0,   0,   0, 246,  31, 
     16,   0,   2,   0,   0,   0, 
     70,  18,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  54, 132, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  54, 132, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,   6,   2, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    226,   0,  16,   0,   1,   0, 
      0,   0, 246,  31,  16,   0, 
      1,   0,   0,   0,   6,  25, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   2,   0,   0,   0, 
    166,  10,  16,   0,   1,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  86,   5,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     54, 132,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  50,   0, 
      0,   9,  18,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
      6,   2,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      1,   0,   0,   0, 246,  31, 
     16,   0,   3,   0,   0,   0, 
      6,  25,  16,   0,   3,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 166,  10,  16,   0, 
      1,   0,   0,   0,  54, 132, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      2,   0,   0,   0,  54, 132, 
     32,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,   6,   2,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   8, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     86,  21,  16,   0,   0,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  54, 132,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   6,  16,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     54, 132,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
    166,  26,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   8, 242,   0,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     54, 132,  32,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     50,   0,   0,  10,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16, 128,  65,   0,   0,   0, 
      2,   0,   0,   0,   6,   2, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,  10, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  12,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0, 192,   0,   0, 
    128,  64,   0,   0,   0, 192, 
     56,   0,   0,   7,  50,   0, 
     16,   0,   2,   0,   0,   0, 
    214,   5,  16,   0,   1,   0, 
      0,   0, 214,   5,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10,  34,   0,  16,   0, 
      2,   0,   0,   0,  42,   0, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  10, 
     66,   0,  16,   0,   1,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     75,   0,   0,   5,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   2,   0, 
      0,   0,  29,   0,   0,   7, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     49,   0,   0,  10, 194,   0, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0, 128,   0,   0, 
      0, 128,  86,  13,  16,   0, 
      0,   0,   0,   0,  55,   0, 
      0,  15, 194,   0,  16,   0, 
      2,   0,   0,   0, 166,  14, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128, 191,   0,   0, 
    128, 191,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,  50,   0, 
      0,   9, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0, 191,  14,   0,   0,   7, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     14,   0,   0,   7,  66,   0, 
     16,   0,   3,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  49,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   3,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,  55,   0,   0,   9, 
    146,   0,  16,   0,   1,   0, 
      0,   0,   6,   0,  16,   0, 
      1,   0,   0,   0, 166,  14, 
     16,   0,   3,   0,   0,   0, 
    246,  11,  16,   0,   3,   0, 
      0,   0,   1,   0,   0,   7, 
    146,   0,  16,   0,   1,   0, 
      0,   0,   6,  12,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   2,   0,   0,   0, 
     24,   0,   0,  10, 178,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  12,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0, 128,   0,   0,   0,   0, 
      0,   0,   0, 128,   1,   0, 
      0,   7, 162,   0,  16,   0, 
      0,   0,   0,   0,  86,  13, 
     16,   0,   2,   0,   0,   0, 
      6,   0,  16,   0,   2,   0, 
      0,   0,  55,   0,   0,  12, 
    194,  32,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,  12,  16,   0,   1,   0, 
      0,   0,  75,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  29,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  50,   0,   0,   9, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0, 191, 
     14,   0,   0,   7,  50,   0, 
     16,   0,   2,   0,   0,   0, 
    230,  10,  16,   0,   0,   0, 
      0,   0,  54,  15,  16,   0, 
      0,   0,   0,   0,  49,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   2,   0, 
      0,   0,  55,   0,   0,   9, 
     82,   0,  16,   0,   0,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,   6,   1, 
     16,   0,   2,   0,   0,   0, 
     86,   4,  16,   0,   2,   0, 
      0,   0,   1,   0,   0,   7, 
     82,   0,  16,   0,   0,   0, 
      0,   0,   6,   2,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   1,   0,   0,   0, 
     55,   0,   0,  12,  50,  32, 
     16,   0,   1,   0,   0,   0, 
     86,   5,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 134,   0, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   7, 130,  32, 
     16,   0,   2,   0,   0,   0, 
     58, 128,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,  14,   0, 
      0,   7, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
    246,  31,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,  18, 
     16,   0,   0,   0,   0,   0, 
     54,   0,   0,   6, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     17,   0,   0,   8,  18,  32, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  12,   0, 
      0,   0,  14,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      2,   0,   0,   0, 246,  31, 
     16,   0,   2,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   6, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  17,   0, 
      0,   8,  34,  32,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
     14,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  18,  16,   0,   3,   0, 
      0,   0, 246,  31,  16,   0, 
      3,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   6, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,  17,   0,   0,   8, 
     66,  32,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,  54,   0, 
      0,   7, 130,  32,  16,   0, 
      3,   0,   0,   0,  58, 128, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  17,   0,   0,   8, 
     18,  32,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     13,   0,   0,   0,  17,   0, 
      0,   8,  34,  32,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  13,   0,   0,   0, 
     17,   0,   0,   8,  66,  32, 
     16,   0,   3,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  17,   0,   0,   8, 
     18,  32,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     14,   0,   0,   0,  17,   0, 
      0,   8,  18,  32,  16,   0, 
      5,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     17,   0,   0,   8,  34,  32, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   0,  17,   0,   0,   8, 
     34,  32,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  17,   0, 
      0,   8,  66,  32,  16,   0, 
      4,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  14,   0,   0,   0, 
     17,   0,   0,   8,  66,  32, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   2,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  54,   0,   0,   7, 
    130,  32,  16,   0,   4,   0, 
      0,   0,  58, 128,  32, 128, 
     65,   0,   0,   0,   0,   0, 
      0,   0,  14,   0,   0,   0, 
     54,   0,   0,   7, 130,  32, 
     16,   0,   5,   0,   0,   0, 
     58, 128,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  56,   0, 
      0,   8, 242,   0,  16,   0, 
      0,   0,   0,   0,  86,  21, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     50,   0,   0,  10, 242,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 166,  26, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,   0,   0,   0,   8, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  14,   0, 
      0,   7, 242,  32,  16,   0, 
      6,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 148,   0, 
      0,   0,  84,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  11,   0,   0,   0, 
     70,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0
};
