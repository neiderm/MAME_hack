/* Tweaked modes definitions */

/* ------------------------------------------------------------------------------------------------------- */
/* NOTES:                                                                                                  */
/* all horizontal/vertical retrace and blanking timings are genereted by - center_mode()        in video.c */
/* all 'scanline' versions of tweaked modes are generated by             - make_scanline_mode() in video.c */
/* ------------------------------------------------------------------------------------------------------- */

/* PC Monitor Tweaked Modes */
/* ------------------------ */


/* 224x288 - vertical mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 35.0KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Linear */
/* Notes: uses a very high horizontal scanrate to fit 288 display lines into 60Hz refresh cycle */
Register scr224x288[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x5f},{ 0x3d4, 0x01, 0x37},
	{ 0x3d4, 0x02, 0x38},{ 0x3d4, 0x03, 0x82},{ 0x3d4, 0x04, 0x49},
	{ 0x3d4, 0x05, 0x9a},{ 0x3d4, 0x06, 0x53},{ 0x3d4, 0x07, 0xf0},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x61},{ 0x3d4, 0x10, 0x40},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0x3f},{ 0x3d4, 0x13, 0x1c},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0x40},{ 0x3d4, 0x16, 0x4a},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};

/* 240x256 - vertical mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 32.4KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Linear */
/* Notes: uses a high horizontal scanrate to fit 256 display lines into 60Hz refresh cycle */
Register scr240x256[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3D4, 0x00, 0x67},{ 0x3d4, 0x01, 0x3b},
	{ 0x3d4, 0x02, 0x40},{ 0x3D4, 0x03, 0x42},{ 0x3d4, 0x04, 0x4e},
	{ 0x3d4, 0x05, 0x9a},{ 0x3D4, 0x06, 0x23},{ 0x3d4, 0x07, 0xb2},
	{ 0x3d4, 0x08, 0x00},{ 0x3D4, 0x09, 0x61},{ 0x3d4, 0x10, 0x0a},
	{ 0x3d4, 0x11, 0xac},{ 0x3D4, 0x12, 0xff},{ 0x3d4, 0x13, 0x1e},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0x07},{ 0x3D4, 0x16, 0x11},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};

/* 256x240 - horizontal mode */
/* Dot Clock - 25MHz */
/* Horizontal Scanrate ~ 34.7KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Linear */
Register scr256x240[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x55},{ 0x3d4, 0x01, 0x3f},
	{ 0x3d4, 0x02, 0x80},{ 0x3d4, 0x03, 0x90},{ 0x3d4, 0x04, 0x49},
	{ 0x3d4, 0x05, 0x80},{ 0x3D4, 0x06, 0x43},{ 0x3d4, 0x07, 0xb2},
	{ 0x3d4, 0x08, 0x00},{ 0x3D4, 0x09, 0x61},{ 0x3d4, 0x10, 0x04},
	{ 0x3d4, 0x11, 0xac},{ 0x3D4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x20},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0x07},{ 0x3D4, 0x16, 0x11},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};

/* 256x256 - vertical mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 31KHz*/
/* Vertical Refresh Rate ~57Hz */
/* Mode Type - Linear */
/* Notes: uses a faster dot clock than horizontal the 256x256 mode to make a thinner display */
Register scr256x256[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3D4, 0x00, 0x6c},{ 0x3d4, 0x01, 0x3f},
	{ 0x3d4, 0x02, 0x40},{ 0x3D4, 0x03, 0x42},{ 0x3d4, 0x04, 0x51},
	{ 0x3d4, 0x05, 0x9a},{ 0x3D4, 0x06, 0x23},{ 0x3d4, 0x07, 0xb2},
	{ 0x3d4, 0x08, 0x00},{ 0x3D4, 0x09, 0x61},{ 0x3d4, 0x10, 0x0a},
	{ 0x3d4, 0x11, 0xac},{ 0x3D4, 0x12, 0xff},{ 0x3d4, 0x13, 0x20},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0x07},{ 0x3D4, 0x16, 0x11},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};

/* 256x256 - horizontal mode */
/* Dot Clock - 25MHz */
/* Horizontal Scanrate ~34.7KHz*/
/* Vertical Refresh Rate ~57Hz */
/* Mode Type - Linear */
Register scr256x256hor[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x55},{ 0x3d4, 0x01, 0x3f},
	{ 0x3d4, 0x02, 0x40},{ 0x3d4, 0x03, 0x90},{ 0x3d4, 0x04, 0x49},
	{ 0x3d4, 0x05, 0x80},{ 0x3D4, 0x06, 0x60},{ 0x3d4, 0x07, 0xb2},
	{ 0x3d4, 0x08, 0x00},{ 0x3D4, 0x09, 0x61},{ 0x3d4, 0x10, 0x28},
	{ 0x3d4, 0x11, 0xac},{ 0x3D4, 0x12, 0xff},{ 0x3d4, 0x13, 0x20},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0x07},{ 0x3D4, 0x16, 0x11},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};


/* 288x224 - horizontal mode */
/* Dot Clock - 25MHz */
/* Horizontal Scanrate ~31.2KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Linear */
Register scr288x224[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5f},{ 0x3d4, 0x01, 0x47},
	{ 0x3d4, 0x02, 0x49},{ 0x3d4, 0x03, 0x90},{ 0x3d4, 0x04, 0x50},
	{ 0x3d4, 0x05, 0x80},{ 0x3d4, 0x06, 0x0c},{ 0x3d4, 0x07, 0x3e},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x41},{ 0x3d4, 0x10, 0xd8},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0xbf},{ 0x3d4, 0x13, 0x24},
	{ 0x3d4, 0x14, 0x40},{ 0x3d4, 0x15, 0xc2},{ 0x3d4, 0x16, 0xf4},
	{ 0x3d4, 0x17, 0xa3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x0e}
};

/* 240x320 - vertical mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~36.8KHz*/
/* Vertical Refresh Rate ~56Hz */
/* Mode Type - Planar */
/* Notes: uses a very high horizontal scanrate to fit 320 display lines into 56Hz refresh cycle */
Register scr240x320[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x5a},{ 0x3d4, 0x01, 0x3b},
	{ 0x3d4, 0x02, 0x3c},{ 0x3d4, 0x03, 0x96},{ 0x3d4, 0x04, 0x47},
	{ 0x3d4, 0x05, 0x14},{ 0x3d4, 0x06, 0x8c},{ 0x3d4, 0x07, 0xf0},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x61},{ 0x3d4, 0x10, 0x80},
	{ 0x3d4, 0x11, 0x92},{ 0x3d4, 0x12, 0x7f},{ 0x3d4, 0x13, 0x1e},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x80},{ 0x3d4, 0x16, 0x84},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

/* 320x240 - horizontal mode */
/* Dot Clock - 25MHz */
/* Horizontal Scanrate ~ 31.2KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Planar */
Register scr320x240[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5f},{ 0x3d4, 0x01, 0x4f},
	{ 0x3d4, 0x02, 0x50},{ 0x3d4, 0x03, 0x82},{ 0x3d4, 0x04, 0x54},
	{ 0x3d4, 0x05, 0x80},{ 0x3d4, 0x06, 0x0c},{ 0x3d4, 0x07, 0x3e},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x41},{ 0x3d4, 0x10, 0xe9},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x28},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe7},{ 0x3d4, 0x16, 0x06},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

/* 336x240 - horizontal mode */
/* Dot Clock - 25MHz */
/* Horizontal Scanrate ~ 31.2KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Planar */
Register scr336x240[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5f},{ 0x3d4, 0x01, 0x53},
	{ 0x3d4, 0x02, 0x56},{ 0x3d4, 0x03, 0x80},{ 0x3d4, 0x04, 0x57},
	{ 0x3d4, 0x05, 0x9b},{ 0x3d4, 0x06, 0x0c},{ 0x3d4, 0x07, 0x3e},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x41},{ 0x3d4, 0x10, 0xe5},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x2a},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe8},{ 0x3d4, 0x16, 0x02},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

/* 384x224 - horizontal mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 31KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Planar */
/* Notes: this mode is basically identical to 384x240, but allows VGA triple buffering */
Register scr384x224[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6c},{ 0x3d4, 0x01, 0x5f},
	{ 0x3d4, 0x02, 0x61},{ 0x3d4, 0x03, 0x8b},{ 0x3d4, 0x04, 0x62},
	{ 0x3d4, 0x05, 0x86},{ 0x3d4, 0x06, 0x0c},{ 0x3d4, 0x07, 0x3e},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x41},{ 0x3d4, 0x10, 0xd8},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0xbf},{ 0x3d4, 0x13, 0x30},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xc2},{ 0x3d4, 0x16, 0xf4},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

/* 384x240 - horizontal mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 31KHz*/
/* Vertical Refresh Rate ~60Hz */
/* Mode Type - Planar */
Register scr384x240[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6c},{ 0x3d4, 0x01, 0x5f},
	{ 0x3d4, 0x02, 0x61},{ 0x3d4, 0x03, 0x8b},{ 0x3d4, 0x04, 0x62},
	{ 0x3d4, 0x05, 0x86},{ 0x3d4, 0x06, 0x0c},{ 0x3d4, 0x07, 0x3e},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x41},{ 0x3d4, 0x10, 0xe9},
	{ 0x3d4, 0x11, 0xac},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x30},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe8},{ 0x3d4, 0x16, 0x04},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

/* 384x256 - horizontal mode */
/* Dot Clock - 28MHz */
/* Horizontal Scanrate ~ 31KHz*/
/* Vertical Refresh Rate ~57Hz */
/* Mode Type - Planar */
Register scr384x256[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6c},{ 0x3d4, 0x01, 0x5f},
	{ 0x3d4, 0x02, 0x61},{ 0x3d4, 0x03, 0x8b},{ 0x3d4, 0x04, 0x62},
	{ 0x3d4, 0x05, 0x86},{ 0x3D4, 0x06, 0x23},{ 0x3d4, 0x07, 0x36},
	{ 0x3d4, 0x08, 0x00},{ 0x3D4, 0x09, 0x61},{ 0x3d4, 0x10, 0xff},
	{ 0x3d4, 0x11, 0xac},{ 0x3D4, 0x12, 0xff},{ 0x3d4, 0x13, 0x30},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x07},{ 0x3D4, 0x16, 0x11},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};




/* Arcade Monitor/TV Tweaked Modes */
/* --------------------------------*/

Register scr224x288_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5d},{ 0x3d4, 0x01, 0x37},
	{ 0x3d4, 0x02, 0x37},{ 0x3d4, 0x03, 0x82},{ 0x3d4, 0x04, 0x42},
	{ 0x3d4, 0x05, 0x96},{ 0x3d4, 0x06, 0x38},{ 0x3d4, 0x07, 0x1f},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x21},
	{ 0x3d4, 0x11, 0xbf},{ 0x3d4, 0x12, 0x1f},{ 0x3d4, 0x13, 0x1c},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x22},{ 0x3d4, 0x16, 0x28},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

Register scr256x240_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5d},{ 0x3d4, 0x01, 0x3f},
	{ 0x3d4, 0x02, 0x40},{ 0x3d4, 0x03, 0x97},{ 0x3d4, 0x04, 0x47},
	{ 0x3d4, 0x05, 0x13},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xf2},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xef},{ 0x3d4, 0x13, 0x20},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xf0},{ 0x3d4, 0x16, 0xf2},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

Register scr256x256_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5d},{ 0x3d4, 0x01, 0x3f},
	{ 0x3d4, 0x02, 0x40},{ 0x3d4, 0x03, 0x97},{ 0x3d4, 0x04, 0x47},
	{ 0x3d4, 0x05, 0x13},{ 0x3d4, 0x06, 0x17},{ 0x3d4, 0x07, 0x1d},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x00},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xff},{ 0x3d4, 0x13, 0x20},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x01},{ 0x3d4, 0x16, 0x0c},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

Register scr288x224_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0x5d},{ 0x3d4, 0x01, 0x47},
	{ 0x3d4, 0x02, 0x47},{ 0x3d4, 0x03, 0x90},{ 0x3d4, 0x04, 0x4c},
	{ 0x3d4, 0x05, 0x16},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xeb},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x24},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe2},{ 0x3d4, 0x16, 0x02},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};



Register scr320x240_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x69},{ 0x3d4, 0x01, 0x4f},
	{ 0x3d4, 0x02, 0x4f},{ 0x3d4, 0x03, 0x91},{ 0x3d4, 0x04, 0x55},
	{ 0x3d4, 0x05, 0x1f},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xf2},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xef},{ 0x3d4, 0x13, 0x28},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xf0},{ 0x3d4, 0x16, 0xf2},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

/* PAL/SECAM version of above */
Register scr320x256_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x69},{ 0x3d4, 0x01, 0x4f},
	{ 0x3d4, 0x02, 0x4f},{ 0x3d4, 0x03, 0x91},{ 0x3d4, 0x04, 0x55},
	{ 0x3d4, 0x05, 0x1f},{ 0x3d4, 0x06, 0x17},{ 0x3d4, 0x07, 0x1d},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x00},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xff},{ 0x3d4, 0x13, 0x28},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x01},{ 0x3d4, 0x16, 0x0c},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

Register scr352x240_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6a},{ 0x3d4, 0x01, 0x57},
	{ 0x3d4, 0x02, 0x57},{ 0x3d4, 0x03, 0x81},{ 0x3d4, 0x04, 0x59},
	{ 0x3d4, 0x05, 0x03},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xf2},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xef},{ 0x3d4, 0x13, 0x2c},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xf0},{ 0x3d4, 0x16, 0xf2},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};


/* PAL/SECAM version of above */
Register scr352x256_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6a},{ 0x3d4, 0x01, 0x57},
	{ 0x3d4, 0x02, 0x57},{ 0x3d4, 0x03, 0x81},{ 0x3d4, 0x04, 0x59},
	{ 0x3d4, 0x05, 0x03},{ 0x3d4, 0x06, 0x17},{ 0x3d4, 0x07, 0x1d},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x00},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xff},{ 0x3d4, 0x13, 0x2c},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x01},{ 0x3d4, 0x16, 0x0c},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

/* 368x224 mode put back in - as it allows triple buffering */
Register scr368x224_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6a},{ 0x3d4, 0x01, 0x5b},
	{ 0x3d4, 0x02, 0x5b},{ 0x3d4, 0x03, 0x87},{ 0x3d4, 0x04, 0x5c},
	{ 0x3d4, 0x05, 0x03},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xeb},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x2e},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe2},{ 0x3d4, 0x16, 0x02},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

Register scr368x240_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6a},{ 0x3d4, 0x01, 0x5b},
	{ 0x3d4, 0x02, 0x5b},{ 0x3d4, 0x03, 0x87},{ 0x3d4, 0x04, 0x5c},
	{ 0x3d4, 0x05, 0x03},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xf2},
	{ 0x3d4, 0x11, 0xa4},{ 0x3d4, 0x12, 0xef},{ 0x3d4, 0x13, 0x2e},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xf0},{ 0x3d4, 0x16, 0xf2},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};


Register scr368x256_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe7},{ 0x3d4, 0x00, 0x6a},{ 0x3d4, 0x01, 0x5b},
	{ 0x3d4, 0x02, 0x5b},{ 0x3d4, 0x03, 0x87},{ 0x3d4, 0x04, 0x5c},
	{ 0x3d4, 0x05, 0x03},{ 0x3d4, 0x06, 0x17},{ 0x3d4, 0x07, 0x1d},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x00},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xff},{ 0x3d4, 0x13, 0x2e},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x01},{ 0x3d4, 0x16, 0x0c},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x09},{ 0x3c4, 0x04, 0x06}
};

/* next 2 modes are for double monitor games and 'half y' modes */
Register scr512x224_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0xbf},{ 0x3d4, 0x01, 0x7f},
	{ 0x3d4, 0x02, 0x7f},{ 0x3d4, 0x03, 0x94},{ 0x3d4, 0x04, 0x90},
	{ 0x3d4, 0x05, 0x84},{ 0x3d4, 0x06, 0x09},{ 0x3d4, 0x07, 0x11},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0xeb},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xdf},{ 0x3d4, 0x13, 0x40},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0xe2},{ 0x3d4, 0x16, 0x02},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};

Register scr512x256_15KHz[] =
{
	{ 0x3c2, 0x00, 0xe3},{ 0x3d4, 0x00, 0xbf},{ 0x3d4, 0x01, 0x7f},
	{ 0x3d4, 0x02, 0x7f},{ 0x3d4, 0x03, 0x94},{ 0x3d4, 0x04, 0x90},
	{ 0x3d4, 0x05, 0x84},{ 0x3d4, 0x06, 0x17},{ 0x3d4, 0x07, 0x1d},
	{ 0x3d4, 0x08, 0x00},{ 0x3d4, 0x09, 0x40},{ 0x3d4, 0x10, 0x00},
	{ 0x3d4, 0x11, 0xa2},{ 0x3d4, 0x12, 0xff},{ 0x3d4, 0x13, 0x40},
	{ 0x3d4, 0x14, 0x00},{ 0x3d4, 0x15, 0x01},{ 0x3d4, 0x16, 0x0c},
	{ 0x3d4, 0x17, 0xe3},{ 0x3c4, 0x01, 0x01},{ 0x3c4, 0x04, 0x06}
};
