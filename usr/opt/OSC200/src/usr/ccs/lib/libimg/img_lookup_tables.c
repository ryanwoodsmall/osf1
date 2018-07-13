#include <img/ImgDef.h>
#include <ImgDefP.h>
struct IMG_LUT_DSC
    {
    unsigned short int length;
    unsigned char      dtype;
    unsigned char      class;
    unsigned char      *addr;
    unsigned char      scale;
    unsigned char      digits;
    unsigned char      aflags;
    unsigned char      dimct;
    unsigned long int  arsize;
    };
#ifdef VMS
globaldef unsigned char IMG_AB_NOCHANGE[] =
#else
unsigned char IMG_AB_NOCHANGE[] =
#endif
    {
       0,   1,   2,   3,   4,   5,   6,   7,
       8,   9,  10,  11,  12,  13,  14,  15,
      16,  17,  18,  19,  20,  21,  22,  23,
      24,  25,  26,  27,  28,  29,  30,  31,
      32,  33,  34,  35,  36,  37,  38,  39,
      40,  41,  42,  43,  44,  45,  46,  47,
      48,  49,  50,  51,  52,  53,  54,  55,
      56,  57,  58,  59,  60,  61,  62,  63,
      64,  65,  66,  67,  68,  69,  70,  71,
      72,  73,  74,  75,  76,  77,  78,  79,
      80,  81,  82,  83,  84,  85,  86,  87,
      88,  89,  90,  91,  92,  93,  94,  95,
      96,  97,  98,  99, 100, 101, 102, 103,
     104, 105, 106, 107, 108, 109, 110, 111,
     112, 113, 114, 115, 116, 117, 118, 119,
     120, 121, 122, 123, 124, 125, 126, 127,
     128, 129, 130, 131, 132, 133, 134, 135,
     136, 137, 138, 139, 140, 141, 142, 143,
     144, 145, 146, 147, 148, 149, 150, 151,
     152, 153, 154, 155, 156, 157, 158, 159,
     160, 161, 162, 163, 164, 165, 166, 167,
     168, 169, 170, 171, 172, 173, 174, 175,
     176, 177, 178, 179, 180, 181, 182, 183,
     184, 185, 186, 187, 188, 189, 190, 191,
     192, 193, 194, 195, 196, 197, 198, 199,
     200, 201, 202, 203, 204, 205, 206, 207,
     208, 209, 210, 211, 212, 213, 214, 215,
     216, 217, 218, 219, 220, 221, 222, 223,
     224, 225, 226, 227, 228, 229, 230, 231,
     232, 233, 234, 235, 236, 237, 238, 239,
     240, 241, 242, 243, 244, 245, 246, 247,
     248, 249, 250, 251, 252, 253, 254, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_NOCHANGE =
#else
struct IMG_LUT_DSC IMG_R_NOCHANGE =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_NOCHANGE,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_BIN_RVSD[] =
#else
unsigned char IMG_AB_BIN_RVSD[] =
#endif
    {
       0, 128,  64, 192,  32, 160,  96, 224,
      16, 144,  80, 208,  48, 176, 112, 240,
       8, 136,  72, 200,  40, 168, 104, 232,
      24, 152,  88, 216,  56, 184, 120, 248,
       4, 132,  68, 196,  36, 164, 100, 228,
      20, 148,  84, 212,  52, 180, 116, 244,
      12, 140,  76, 204,  44, 172, 108, 236,
      28, 156,  92, 220,  60, 188, 124, 252,
       2, 130,  66, 194,  34, 162,  98, 226,
      18, 146,  82, 210,  50, 178, 114, 242,
      10, 138,  74, 202,  42, 170, 106, 234,
      26, 154,  90, 218,  58, 186, 122, 250,
       6, 134,  70, 198,  38, 166, 102, 230,
      22, 150,  86, 214,  54, 182, 118, 246,
      14, 142,  78, 206,  46, 174, 110, 238,
      30, 158,  94, 222,  62, 190, 126, 254,
       1, 129,  65, 193,  33, 161,  97, 225,
      17, 145,  81, 209,  49, 177, 113, 241,
       9, 137,  73, 201,  41, 169, 105, 233,
      25, 153,  89, 217,  57, 185, 121, 249,
       5, 133,  69, 197,  37, 165, 101, 229,
      21, 149,  85, 213,  53, 181, 117, 245,
      13, 141,  77, 205,  45, 173, 109, 237,
      29, 157,  93, 221,  61, 189, 125, 253,
       3, 131,  67, 195,  35, 163,  99, 227,
      19, 147,  83, 211,  51, 179, 115, 243,
      11, 139,  75, 203,  43, 171, 107, 235,
      27, 155,  91, 219,  59, 187, 123, 251,
       7, 135,  71, 199,  39, 167, 103, 231,
      23, 151,  87, 215,  55, 183, 119, 247,
      15, 143,  79, 207,  47, 175, 111, 239,
      31, 159,  95, 223,  63, 191, 127, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_BIN_RVSD =
#else
struct IMG_LUT_DSC IMG_R_BIN_RVSD =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_BIN_RVSD,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_NIB_RVSD[] =
#else
unsigned char IMG_AB_NIB_RVSD[] =
#endif
    {
       0,  16,  32,  48,  64,  80,  96, 112,
     128, 144, 160, 176, 192, 208, 224, 240,
       1,  17,  33,  49,  65,  81,  97, 113,
     129, 145, 161, 177, 193, 209, 225, 241,
       2,  18,  34,  50,  66,  82,  98, 114,
     130, 146, 162, 178, 194, 210, 226, 242,
       3,  19,  35,  51,  67,  83,  99, 115,
     131, 147, 163, 179, 195, 211, 227, 243,
       4,  20,  36,  52,  68,  84, 100, 116,
     132, 148, 164, 180, 196, 212, 228, 244,
       5,  21,  37,  53,  69,  85, 101, 117,
     133, 149, 165, 181, 197, 213, 229, 245,
       6,  22,  38,  54,  70,  86, 102, 118,
     134, 150, 166, 182, 198, 214, 230, 246,
       7,  23,  39,  55,  71,  87, 103, 119,
     135, 151, 167, 183, 199, 215, 231, 247,
       8,  24,  40,  56,  72,  88, 104, 120,
     136, 152, 168, 184, 200, 216, 232, 248,
       9,  25,  41,  57,  73,  89, 105, 121,
     137, 153, 169, 185, 201, 217, 233, 249,
      10,  26,  42,  58,  74,  90, 106, 122,
     138, 154, 170, 186, 202, 218, 234, 250,
      11,  27,  43,  59,  75,  91, 107, 123,
     139, 155, 171, 187, 203, 219, 235, 251,
      12,  28,  44,  60,  76,  92, 108, 124,
     140, 156, 172, 188, 204, 220, 236, 252,
      13,  29,  45,  61,  77,  93, 109, 125,
     141, 157, 173, 189, 205, 221, 237, 253,
      14,  30,  46,  62,  78,  94, 110, 126,
     142, 158, 174, 190, 206, 222, 238, 254,
      15,  31,  47,  63,  79,  95, 111, 127,
     143, 159, 175, 191, 207, 223, 239, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_NIB_RVSD =
#else
struct IMG_LUT_DSC IMG_R_NIB_RVSD =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_NIB_RVSD,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_LW_BIN[] =
#else
unsigned char IMG_AB_LW_BIN[] =
#endif
    {
       0,   1,   2,   7,   2,   5,   6,   7,
       8,   9,  18,  11,  12,  29,  14,  15,
      16,   9,  18,  11,  18,  21,  22,  23,
      24,  25,  26,  27,  28,  29,  30,  31,
      32,  33,  34,  35,  36,  37,  38,  39,
      40,  41,  42,  43,  44,  45,  46,  47,
      48,  49,  50,  51,  52,  53,  54,  55,
      56,  57,  58,  59,  60,  61,  62,  63,
      64,  65,  66,  67,  68,  69,  70,  71,
      72,  73,  74,  75,  76,  77,  78,  79,
      80,  81,  82,  83,  84,  85,  86,  87,
      88,  89,  90,  91,  92,  93,  94,  95,
      96,  97,  98,  99, 100, 101, 102, 103,
     104, 105, 106, 107, 108, 109, 110, 111,
     112, 113, 114, 115, 116, 117, 118, 119,
     120, 121, 122, 123, 124, 125, 126, 127,
     128, 129, 130, 131, 132, 133, 134, 135,
     136, 137, 138, 139, 140, 141, 142, 143,
     144, 145, 146, 147, 148, 149, 150, 151,
     152, 153, 154, 155, 156, 157, 158, 159,
     160, 161, 162, 163, 164, 165, 166, 167,
     168, 169, 170, 171, 172, 173, 174, 175,
     176, 177, 178, 179, 180, 181, 182, 183,
     184, 185, 186, 187, 188, 189, 190, 191,
     192, 193, 194, 195, 196, 197, 198, 199,
     200, 201, 202, 203, 204, 205, 206, 207,
     208, 209, 210, 211, 212, 213, 214, 215,
     216, 217, 218, 219, 220, 221, 222, 223,
     224, 225, 226, 227, 228, 229, 230, 231,
     232, 233, 234, 235, 236, 237, 238, 239,
     240, 241, 242, 243, 244, 245, 246, 247,
     248, 249, 250, 251, 252, 253, 254, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_LW_BIN =
#else
struct IMG_LUT_DSC IMG_R_LW_BIN =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_LW_BIN,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_LW_BIN_RVSD[] =
#else
unsigned char IMG_AB_LW_BIN_RVSD[] =
#endif
    {
       0, 128,  64, 192,  32, 160,  96, 224,
      16, 144,  80, 208,  48, 176, 112, 240,
       8, 136,  72, 200,  40, 168, 104, 232,
      24, 152,  88, 216,  56, 184, 120, 248,
       2, 132,  68, 196,  36, 164, 100, 228,
      18, 148,  84, 212,  52, 180, 116, 244,
      12, 140,  76, 204,  44, 172, 108, 236,
      28, 156,  92, 220,  60, 188, 124, 252,
       2, 130,  66, 194,  34, 162,  98, 226,
      18, 146,  82, 210,  50, 178, 114, 242,
      18, 138,  74, 202,  42, 170, 106, 234,
      26, 154,  90, 218,  58, 186, 122, 250,
       6, 134,  70, 198,  38, 166, 102, 230,
      22, 150,  86, 214,  54, 182, 118, 246,
      14, 142,  78, 206,  46, 174, 110, 238,
      30, 158,  94, 222,  62, 190, 126, 254,
       1, 129,  65, 193,  33, 161,  97, 225,
       9, 145,  81, 209,  49, 177, 113, 241,
       9, 137,  73, 201,  41, 169, 105, 233,
      25, 153,  89, 217,  57, 185, 121, 249,
       5, 133,  69, 197,  37, 165, 101, 229,
      21, 149,  85, 213,  53, 181, 117, 245,
      29, 141,  77, 205,  45, 173, 109, 237,
      29, 157,  93, 221,  61, 189, 125, 253,
       2, 131,  67, 195,  35, 163,  99, 227,
      11, 147,  83, 211,  51, 179, 115, 243,
      11, 139,  75, 203,  43, 171, 107, 235,
      27, 155,  91, 219,  59, 187, 123, 251,
       7, 135,  71, 199,  39, 167, 103, 231,
      23, 151,  87, 215,  55, 183, 119, 247,
      15, 143,  79, 207,  47, 175, 111, 239,
      31, 159,  95, 223,  63, 191, 127, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_LW_BIN_RVSD =
#else
struct IMG_LUT_DSC IMG_R_LW_BIN_RVSD =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_LW_BIN_RVSD,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_TRASH_BIN[] =
#else
unsigned char IMG_AB_TRASH_BIN[] =
#endif
    {
       0,   1,   2,   3,   4,   5,   6,   7,
       8,   9,  10,  11,  12,  13,  14,  15,
      16,  17,  18,  19,  20,  21,  22,  23,
      24,  25,  26,  27,  28,  29,  30,  31,
      32,  33,  34,  35,  36,  37,  38,  39,
      40,  41,  42,  43,  44,  45,  46,  47,
      48,  49,  50,  51,  52,  53,  54,  55,
      56,  57,  58,  59,  60,  61,  62,  63,
      64,  65,  66,  67,  68,  69,  70,  71,
      72,  73,  74,  75,  76,  77,  78,  79,
      80,  81,  82,  83,  84,   0,  86,  87,
      88,  89,  90,  91,  92,  93,  94,  95,
      96,  97,  98,  99, 100, 101, 102, 103,
     104, 105, 106, 107, 108, 109, 110, 111,
     112, 113, 114, 115, 116, 117, 118, 119,
     120, 121, 122, 123, 124, 125, 126, 127,
     128, 129, 130, 131, 132, 133, 134, 135,
     136, 137, 138, 139, 140, 141, 142, 143,
     144, 145, 146, 147, 148, 149, 150, 151,
     152, 153, 154, 155, 156, 157, 158, 159,
     160, 161, 162, 163, 164, 165, 166, 167,
     168, 169,   0, 171, 172, 173, 174, 175,
     176, 177, 178, 179, 180, 181, 182, 183,
     184, 185, 186, 187, 188, 189, 190, 191,
     192, 193, 194, 195, 196, 197, 198, 199,
     200, 201, 202, 203, 204, 205, 206, 207,
     208, 209, 210, 211, 212, 213, 214, 215,
     216, 217, 218, 219, 220, 221, 222, 223,
     224, 225, 226, 227, 228, 229, 230, 231,
     232, 233, 234, 235, 236, 237, 238, 239,
     240, 241, 242, 243, 244, 245, 246, 247,
     248, 249, 250, 251, 252, 253, 254, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_TRASH_BIN =
#else
struct IMG_LUT_DSC IMG_R_TRASH_BIN =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_TRASH_BIN,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_RGB332_Y8_LUT[] =
#else
unsigned char IMG_AB_RGB332_Y8_LUT[] =
#endif
    {
       0,  10,  19,  29,  21,  31,  41,  50,
      43,  52,  62,  72,  64,  74,  84,  93,
      86,  95, 105, 115, 107, 117, 126, 136,
     128, 138, 148, 157, 150, 159, 169, 179,
      11,  21,  30,  40,  32,  42,  52,  61,
      54,  63,  73,  83,  75,  85,  94, 104,
      96, 106, 116, 125, 118, 127, 137, 147,
     139, 149, 159, 168, 161, 170, 180, 190,
      22,  31,  41,  51,  43,  53,  63,  72,
      65,  74,  84,  94,  86,  96, 105, 115,
     107, 117, 127, 136, 129, 138, 148, 158,
     150, 160, 169, 179, 171, 181, 191, 201,
      33,  42,  52,  62,  54,  64,  73,  83,
      75,  85,  95, 105,  97, 107, 116, 126,
     118, 128, 138, 147, 140, 149, 159, 169,
     161, 171, 180, 190, 182, 192, 202, 211,
      44,  53,  63,  73,  65,  75,  84,  94,
      86,  96, 106, 115, 108, 117, 127, 137,
     129, 139, 148, 158, 150, 160, 170, 180,
     172, 182, 191, 201, 193, 203, 213, 222,
      54,  64,  74,  84,  76,  86,  95, 105,
      97, 107, 117, 126, 119, 128, 138, 148,
     140, 150, 159, 169, 161, 171, 181, 190,
     183, 192, 202, 212, 204, 214, 224, 233,
      65,  75,  85,  94,  87,  96, 106, 116,
     108, 118, 128, 137, 130, 139, 149, 159,
     151, 161, 170, 180, 172, 182, 192, 201,
     194, 203, 213, 223, 215, 225, 234, 244,
      76,  86,  96, 105,  98, 107, 117, 127,
     119, 129, 138, 148, 140, 150, 160, 169,
     162, 171, 181, 191, 183, 193, 203, 212,
     205, 214, 224, 234, 226, 236, 245, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_RGB332_Y8_LUT =
#else
struct IMG_LUT_DSC IMG_R_RGB332_Y8_LUT =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_RGB332_Y8_LUT,0,0,0,1,256};
#ifdef VMS
globaldef unsigned char IMG_AB_RGB332_Y1_LUT[] =
#else
unsigned char IMG_AB_RGB332_Y1_LUT[] =
#endif
    {
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0,   0,
       0, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0,   0,   0, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,   0, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0,   0, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
       0,   0,   0,   0,   0,   0,   0,   0,
       0, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_RGB332_Y1_LUT =
#else
struct IMG_LUT_DSC IMG_R_RGB332_Y1_LUT =
#endif
    {1,DSC_K_DTYPE_BU,DSC_K_CLASS_A,IMG_AB_RGB332_Y1_LUT,0,0,0,1,256};
#ifdef VMS
globaldef unsigned int IMG_AL_ONES_ASCENDING[] =
#else
unsigned int  IMG_AL_ONES_ASCENDING[] =
#endif
    {
             0,         1,         3,         7,
            15,        31,        63,       127,
           255,       511,      1023,      2047,
          4095,      8191,     16383,     32767,
         65535,    131071,    262143,    524287,
       1048575,   2097151,   4194303,   8388607,
      16777215,  33554431,  67108863, 134217727,
     268435455, 536870911,1073741823,2147483647,
    4294967295
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_ONES_ASCENDING =
#else
struct IMG_LUT_DSC IMG_R_ONES_ASCENDING =
#endif
    {4,DSC_K_DTYPE_LU,DSC_K_CLASS_A,(unsigned char *) IMG_AL_ONES_ASCENDING,0,0,0,1,132};
#ifdef VMS
globaldef unsigned int  IMG_AL_ONES_DESCENDING[] =
#else
unsigned int IMG_AL_ONES_DESCENDING[] =
#endif
    {
             0,2147483648,3221225472,3758096384,
    4026531840,4160749568,4227858432,4261412864,
    4278190080,4286578688,4290772992,4292870144,
    4293918720,4294443008,4294705152,4294836224,
    4294901760,4294934528,4294950912,4294959104,
    4294963200,4294965248,4294966272,4294966784,
    4294967040,4294967168,4294967232,4294967264,
    4294967280,4294967288,4294967292,4294967294,
    4294967295
    };
#ifdef VMS
globaldef struct IMG_LUT_DSC IMG_R_ONES_DESCENDING =
#else
struct IMG_LUT_DSC IMG_R_ONES_DESCENDING =
#endif
    {4,DSC_K_DTYPE_LU,DSC_K_CLASS_A,(unsigned char *) IMG_AL_ONES_DESCENDING,0,0,0,1,132};
#ifdef VMS
globaldef unsigned long int _ImgAL_DDIFAccessTable[] =
#else
unsigned long int _ImgAL_DDIFAccessTable[] =
#endif
    {
           513,       514,       515,       516,
           770,       771,       772,       773,
          1026,      6245,      6246,      6247,
          6248,      6249,      6250,      6251,
          6252,      6255,      6256,      6257,
          6258,      6259,      6226,      6227,
          6228,      6229,      6230,      6231,
          6232,      6233,      6234,      6236,
          6237,      6238,      6239,      6240,
          6241,      6242,      6243,      5633,
          5634,      5635,      5636,      5637,
          5638,      5639,      5640,      5641,
          5642,      5643,      5644,      5645,
          5646,      6274,      6275,      6276
    };
#ifdef VMS
globaldef unsigned short int IMG_AW_ASCII_HEX[] =
#else
unsigned short int IMG_AW_ASCII_HEX[] =
#endif
    {
         12336,     12592,     12848,     13104,
         13360,     13616,     13872,     14128,
         14384,     14640,     24880,     25136,
         25392,     25648,     25904,     26160,
         12337,     12593,     12849,     13105,
         13361,     13617,     13873,     14129,
         14385,     14641,     24881,     25137,
         25393,     25649,     25905,     26161,
         12338,     12594,     12850,     13106,
         13362,     13618,     13874,     14130,
         14386,     14642,     24882,     25138,
         25394,     25650,     25906,     26162,
         12339,     12595,     12851,     13107,
         13363,     13619,     13875,     14131,
         14387,     14643,     24883,     25139,
         25395,     25651,     25907,     26163,
         12340,     12596,     12852,     13108,
         13364,     13620,     13876,     14132,
         14388,     14644,     24884,     25140,
         25396,     25652,     25908,     26164,
         12341,     12597,     12853,     13109,
         13365,     13621,     13877,     14133,
         14389,     14645,     24885,     25141,
         25397,     25653,     25909,     26165,
         12342,     12598,     12854,     13110,
         13366,     13622,     13878,     14134,
         14390,     14646,     24886,     25142,
         25398,     25654,     25910,     26166,
         12343,     12599,     12855,     13111,
         13367,     13623,     13879,     14135,
         14391,     14647,     24887,     25143,
         25399,     25655,     25911,     26167,
         12344,     12600,     12856,     13112,
         13368,     13624,     13880,     14136,
         14392,     14648,     24888,     25144,
         25400,     25656,     25912,     26168,
         12345,     12601,     12857,     13113,
         13369,     13625,     13881,     14137,
         14393,     14649,     24889,     25145,
         25401,     25657,     25913,     26169,
         12385,     12641,     12897,     13153,
         13409,     13665,     13921,     14177,
         14433,     14689,     24929,     25185,
         25441,     25697,     25953,     26209,
         12386,     12642,     12898,     13154,
         13410,     13666,     13922,     14178,
         14434,     14690,     24930,     25186,
         25442,     25698,     25954,     26210,
         12387,     12643,     12899,     13155,
         13411,     13667,     13923,     14179,
         14435,     14691,     24931,     25187,
         25443,     25699,     25955,     26211,
         12388,     12644,     12900,     13156,
         13412,     13668,     13924,     14180,
         14436,     14692,     24932,     25188,
         25444,     25700,     25956,     26212,
         12389,     12645,     12901,     13157,
         13413,     13669,     13925,     14181,
         14437,     14693,     24933,     25189,
         25445,     25701,     25957,     26213,
         12390,     12646,     12902,     13158,
         13414,     13670,     13926,     14182,
         14438,     14694,     24934,     25190,
         25446,     25702,     25958,     26214
    };
#ifdef VMS
globaldef unsigned short int IMG_AW_ASCII_HEX_RVSD[] =
#else
unsigned short int IMG_AW_ASCII_HEX_RVSD[] =
#endif
    {
         12336,     12344,     12340,     12387,
         12338,     12385,     12342,     12389,
         12337,     12345,     12341,     12388,
         12339,     12386,     12343,     12390,
         14384,     14392,     14388,     14435,
         14386,     14433,     14390,     14437,
         14385,     14393,     14389,     14436,
         14387,     14434,     14391,     14438,
         13360,     13368,     13364,     13411,
         13362,     13409,     13366,     13413,
         13361,     13369,     13365,     13412,
         13363,     13410,     13367,     13414,
         25392,     25400,     25396,     25443,
         25394,     25441,     25398,     25445,
         25393,     25401,     25397,     25444,
         25395,     25442,     25399,     25446,
         12848,     12856,     12852,     12899,
         12850,     12897,     12854,     12901,
         12849,     12857,     12853,     12900,
         12851,     12898,     12855,     12902,
         24880,     24888,     24884,     24931,
         24882,     24929,     24886,     24933,
         24881,     24889,     24885,     24932,
         24883,     24930,     24887,     24934,
         13872,     13880,     13876,     13923,
         13874,     13921,     13878,     13925,
         13873,     13881,     13877,     13924,
         13875,     13922,     13879,     13926,
         25904,     25912,     25908,     25955,
         25906,     25953,     25910,     25957,
         25905,     25913,     25909,     25956,
         25907,     25954,     25911,     25958,
         12592,     12600,     12596,     12643,
         12594,     12641,     12598,     12645,
         12593,     12601,     12597,     12644,
         12595,     12642,     12599,     12646,
         14640,     14648,     14644,     14691,
         14642,     14689,     14646,     14693,
         14641,     14649,     14645,     14692,
         14643,     14690,     14647,     14694,
         13616,     13624,     13620,     13667,
         13618,     13665,     13622,     13669,
         13617,     13625,     13621,     13668,
         13619,     13666,     13623,     13670,
         25648,     25656,     25652,     25699,
         25650,     25697,     25654,     25701,
         25649,     25657,     25653,     25700,
         25651,     25698,     25655,     25702,
         13104,     13112,     13108,     13155,
         13106,     13153,     13110,     13157,
         13105,     13113,     13109,     13156,
         13107,     13154,     13111,     13158,
         25136,     25144,     25140,     25187,
         25138,     25185,     25142,     25189,
         25137,     25145,     25141,     25188,
         25139,     25186,     25143,     25190,
         14128,     14136,     14132,     14179,
         14130,     14177,     14134,     14181,
         14129,     14137,     14133,     14180,
         14131,     14178,     14135,     14182,
         26160,     26168,     26164,     26211,
         26162,     26209,     26166,     26213,
         26161,     26169,     26165,     26212,
         26163,     26210,     26167,     26214
    };