/******************************************************************************
*  G711_Plane.s developed by Microchip Technology Inc. 
*  Copyright (c) 2005 by Microchip. All rights are reserved. 
*  
*  This Copyright notice may not be removed or modified without prior written 
*  consent of Microchip Technology Inc. 
******************************************************************************/

/******************************************************************************
*  G711_Plane.s
*
*  Description:
*    This file is generated by dsPIC33F Speech Encoder Utility Version 1.00
*    It contains the ALAW compressed data for a 8kHz,16-bit speech signal.The
*    output array represents a 64kbps encoded bit stream.
*
*    Speech Encoder Utility settings:
*       Input Source:  Plane.wav
*       Output Array:  G711_Plane
*       Array Size:    4098 bytes                
*       Target Memory: Program Memory
*       LAW:           ALAW
******************************************************************************/

/* There are 1366 elements in the data array. */
   
/* Data file for storing 24-bit constants in program memory */

.global _G711_Plane

.section .G711, code
_G711_Plane:
.pword 0x55D555,  0x555555,  0x555555,  0x555555,  0x555555,  0x555555
.pword 0x555555,  0x555555,  0x555555,  0x555555,  0x555555,  0x555555
.pword 0x555555,  0x555555,  0x545555,  0x545455,  0x555454,  0x555555
.pword 0x555555,  0x555555,  0x555555,  0x555555,  0xD555D5,  0xD5D555
.pword 0x55D555,  0xD555D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5
.pword 0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0x55D555,  0xD555D5,  0xD5D555
.pword 0x55D5D5,  0x555555,  0xD55555,  0x55D5D5,  0xD5D5D5,  0xD5D5D5
.pword 0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5
.pword 0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD555D5
.pword 0x55D555,  0xD55555,  0x555555,  0x555555,  0x555555,  0x555555
.pword 0x555555,  0x555555,  0xD55555,  0x55D555,  0xD555D5,  0xD5D555
.pword 0x55D555,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5,  0xD5D5D5
.pword 0xD5D5D5,  0xD5D5D5,  0xD555D5,  0xD5D5D5,  0xD6D7D5,  0xD4D4D7
.pword 0xD5D5D4,  0xD4D4D4,  0xD4D4D4,  0xD7D4D4,  0xD7D7D7,  0xD6D6D6
.pword 0xD0D0D1,  0xD4D6D0,  0x5455D5,  0x565657,  0x515656,  0x565156
.pword 0x525051,  0x45595C,  0x4C4346,  0x754A49,  0x747575,  0x777777
.pword 0x707370,  0x777676,  0x474148,  0x505947,  0xC4DBD3,  0xCCCFC2
.pword 0xCFC8CF,  0xF4F4C9,  0xF5F5F5,  0xF0F7F4,  0xF9F9FC,  0xE0E1E5
.pword 0xEDE3E0,  0xE9E9EF,  0xECEDEF,  0xEDECEF,  0xE6E0E2,  0xE6E7E7
.pword 0xFEFBE4,  0xF5F3FC,  0x53D5DA,  0x774C5A,  0x78797D,  0x676664
.pword 0x666667,  0x646766,  0x666664,  0x606166,  0x616666,  0x666661
.pword 0x646666,  0x7A7B7A,  0x7D7A65,  0x474E77,  0x5C505E,  0x4E4C44
.pword 0x505246,  0xDED053,  0xDCD0D2,  0xC1DADB,  0xDAC6C3,  0xC1C3C7
.pword 0xCDCDC1,  0xCACDC3,  0xCBCBF7,  0xF4F4F5,  0xF5CACB,  0xF7F7F5
.pword 0xF4F4F7,  0xCBCBF4,  0xCEF5F4,  0xC2C3C0,  0xDCC7CC,  0xD4D7D1
.pword 0x5E5C54,  0x5B5858,  0x444242,  0x754B42,  0x737674,  0x707073
.pword 0x7D7F72,  0x7D7D72,  0x70727C,  0x757576,  0x4E4A74,  0x5D4442
.pword 0xD55153,  0x55D1D7,  0x585050,  0x5B5E5B,  0x525D5E,  0xD5D757
.pword 0x565455,  0x5D5655,  0x5C5C5C,  0x5F4545,  0x555453,  0xC5DDD4
.pword 0xCBC1C7,  0xF1F1F1,  0xF9FFFD,  0xE4E5FB,  0xE7E4E5,  0xE7E7E6
.pword 0xE7E7E7,  0xF8FBE4,  0xFFFFF9,  0xF2F3FD,  0xF6F0F2,  0xCDC9F4
.pword 0xDCD8C6,  0xD7D6D2,  0x595D56,  0x47455A,  0x4E4E43,  0x76754E
.pword 0x767671,  0x737371,  0x7D7273,  0x7F7C7C,  0x7D7D7C,  0x7D7D7C
.pword 0x7C7D7C,  0x7C7C7D,  0x7D7D7C,  0x727372,  0x727272,  0x727272
.pword 0x727D72,  0x707176,  0x707070,  0x767170,  0x757477,  0x494A75
.pword 0x49494E,  0x4E4D4F,  0x4A754A,  0x754A4A,  0x4F4875,  0x595B46
.pword 0x505D5F,  0xD7D554,  0xDBDCD1,  0xC1C7C5,  0xC9CDC0,  0xC8CBCB
.pword 0xCFCEC9,  0xCECFCF,  0xCEC9C9,  0xC2CCCE,  0xCDCDC3,  0xCECDC2
.pword 0xF7F7F5,  0xF3F1F7,  0xFCFDF2,  0xFEFEFE,  0xFFFFFE,  0xF2FDFC
.pword 0xF4F1F3,  0xC6C2C9,  0xDFD9DA,  0xD4D7D3,  0xD7D6D7,  0xDFD2D6
.pword 0xC9C3C5,  0xFFF3F4,  0xE5E5F8,  0xE4E4E4,  0xF9E5E5,  0xCDF4F2
.pword 0x4557DE,  0x78734B,  0x6E6367,  0x17146A,  0x141717,  0x656F15
.pword 0xE8FF5F,  0x989F90,  0x9A859A,  0x919C98,  0xDAFBEE,  0x68674B
.pword 0x1A1F11,  0x010704,  0x030000,  0x1F0700,  0x93F263,  0x8D8084
.pword 0x8D8C8D,  0x9B8683,  0xDDE796,  0x7C7275,  0x63647F,  0x626F6F
.pword 0x666766,  0x176862,  0x071B1D,  0x070300,  0xE07D12,  0x849A92
.pword 0x868687,  0x998487,  0x959692,  0xEDE9E8,  0x4EC6FA,  0x6D607B
.pword 0x101468,  0x041B1F,  0x0D0301,  0x05020C,  0x9EE46C,  0x8D8281
.pword 0x83828D,  0x9D8581,  0xFAE395,  0xC0F6FD,  0x647457,  0x6E6D63
.pword 0x13176B,  0x06051E,  0x080E02,  0x17010E,  0x879DF1,  0x8D8283
.pword 0x80828D,  0xE89D84,  0xFBF8E7,  0xD9F2FA,  0x677E4C,  0x6B6C60
.pword 0x181D16,  0x0D0104,  0x0A3508,  0x551F0C,  0x838692,  0x8D8282
.pword 0x878382,  0xF9E89F,  0xE3E5F0,  0xDCFEE0,  0x677B4A,  0x146C61
.pword 0x051E13,  0x090206,  0x0A3435,  0x956001,  0x828384,  0x8C8D82
.pword 0x85808D,  0xF3E497,  0x95E9E4,  0x45F1EC,  0x747372,  0x14607C
.pword 0x051812,  0x0A0C01,  0x093737,  0x86EC13,  0x808C8C,  0x8D8381
.pword 0x918483,  0x95FDFA,  0x9A8798,  0x79DF95,  0x707478,  0x1E116D
.pword 0x07051B,  0x33370C,  0x153532,  0xB4B587,  0x808388,  0x858D8D
.pword 0xC451ED,  0x838797,  0xF99086,  0xF5F5C6,  0x636552,  0x78487A
.pword 0x080110,  0x3D3037,  0x4D353D,  0xB3B28B,  0x988488,  0xF89D9B
.pword 0x905671,  0x8F8882,  0xCEEA84,  0x64705A,  0x776162,  0x11785A
.pword 0x0A0C07,  0x3B3C31,  0x9A0939,  0xB4BCB2,  0x878780,  0x107693
.pword 0x899B76,  0x848088,  0xE19A86,  0x101B15,  0x40F44E,  0x121315
.pword 0x370D1B,  0x3A3B3F,  0x81003F,  0xB7BCBD,  0x9B808F,  0x666FF9
.pword 0x898D96,  0x8D808D,  0x60928D,  0x571018,  0x6659F9,  0x687D66
.pword 0x360B06,  0x25393D,  0x820F3B,  0x8BB2BF,  0x848283,  0x6F1F55
.pword 0x888A9A,  0x8E8681,  0x1D9089,  0xEF1601,  0x624A95,  0x79E7D5
.pword 0x350A01,  0x253C37,  0x9D3124,  0x8AB2BD,  0x828A8E,  0x6F1AD6
.pword 0x8EB587,  0x8A8087,  0x7384B5,  0xE46712,  0x7773FF,  0xD795E1
.pword 0x0F0219,  0x3A3D35,  0x1B3F25,  0xB1B288,  0x89B4B4,  0x6A6A91
.pword 0x8E8F96,  0xB58C82,  0xC381B5,  0x466814,  0xF1CFF6,  0xF397EA
.pword 0x071869,  0x3D3702,  0x323939,  0xB28F1A,  0x8BB5B1,  0x699582
.pword 0x8F9263,  0x898D8E,  0x858BB5,  0x6862F7,  0xE75E60,  0xE0E9EE
.pword 0x1F61C0,  0x340E01,  0x383E33,  0x82063C,  0x8BB4B0,  0xE98CB5
.pword 0x926F16,  0x818082,  0x8FB58E,  0x78DE93,  0x656B6E,  0xEFE2C4
.pword 0x6458F3,  0x0E0613,  0x3F3034,  0x343938,  0xB5B7E8,  0x8E888F
.pword 0x101593,  0x8781EC,  0xB58C85,  0xF4938F,  0x1A6BD1,  0xE2D313
.pword 0xC75FF3,  0x0668CD,  0x340E0C,  0x39383D,  0x811A33,  0x8B89B5
.pword 0x5C848B,  0x9E5717,  0x829B85,  0x84888A,  0x5FF8ED,  0x67051F
.pword 0xDFEFEE,  0xCEEECF,  0x030112,  0x3C370F,  0x303F3E,  0x8A8018
.pword 0x89898C,  0x6F5785,  0x859AFF,  0xB58C85,  0xCB9F8E,  0x164EDD
.pword 0xE87510,  0xC3CE95,  0x17D8E0,  0x0F0105,  0x3F3D37,  0x01323F
.pword 0x808E85,  0x848B8E,  0xE766DA,  0x9F9D98,  0x8C8A8D,  0xFAEC9E
.pword 0x181F7C,  0xFADA69,  0xECE4FD,  0x1D6DF6,  0x0B0305,  0x3D3337
.pword 0x6C363C,  0x848183,  0x968F89,  0x93DD76,  0x87909E,  0x818B8A
.pword 0xC4E090,  0x141262,  0xCDFED1,  0xE4E3F6,  0x166C4C,  0x0A0D05
.pword 0x3D3336,  0xE30B3D,  0x838583,  0xEC8DB4,  0x9E95CD,  0x8C9391
.pword 0x878CB5,  0x70EA99,  0x60121D,  0xE3DA77,  0xE7E8EA,  0x177CDF
.pword 0x0C0005,  0x323334,  0x6C3433,  0x849B85,  0x908C8B,  0x9E94E1
.pword 0x829C9C,  0x868F8B,  0x7BEF98,  0x6E1611,  0xE24C62,  0xE7E395
.pword 0x6ED6E4,  0x03041E,  0x33310A,  0x0F3333,  0x979BE3,  0x878B80
.pword 0x9E95EF,  0x849298,  0x818989,  0xD89C84,  0x691116,  0xC81012
.pword 0xE3E295,  0x54E995,  0x19106B,  0x370B03,  0x333331,  0x91DB09
.pword 0x8887E7,  0x92E884,  0x999A85,  0x8E8B81,  0x9B8180,  0x136EFD
.pword 0x6B1710,  0xE2ED50,  0xEF94EC,  0x6E7DC0,  0x0F0713,  0x313735
.pword 0x183630,  0x96ED94,  0x9C8F89,  0x86869F,  0x8E8684,  0x808288
.pword 0x7B9586,  0x141210,  0xC36F69,  0xEC9491,  0xC29496,  0x1D6864
.pword 0x0B0C06,  0x303137,  0xC90631,  0x8DE55A,  0x859E8D,  0x868083
.pword 0x8E8983,  0x878083,  0x1778E9,  0x1B1C12,  0xF44010,  0x9391E1
.pword 0xC7E394,  0x1F6A7C,  0x0A0204,  0x303637,  0x7C0130,  0x82F56E
.pword 0x819C80,  0x83828F,  0x8C888C,  0x858181,  0x1661FA,  0x19061A
.pword 0xF04160,  0x929F96,  0xE19491,  0x6C70DB,  0x0D0712,  0x31370B
.pword 0x1C3732,  0x9E6A6B,  0x86848F,  0x8C8B8A,  0x898B8E,  0x868183
.pword 0x634196,  0x040712,  0x66111C,  0x9D91E4,  0x929899,  0xDAE5EA
.pword 0x1B167A,  0x370B03,  0x323231,  0x1E1D0E,  0x8082DF,  0xB48A87
.pword 0xB58888,  0x868288,  0x559286,  0x041163,  0x040601,  0xFF7810
.pword 0x989990,  0xE89C9B,  0x7BF4E6,  0x031B16,  0x30360B,  0x363F3D
.pword 0x6C0507,  0x818D87,  0xB4B1B5,  0x8AB4B5,  0x87868D,  0x62D692
.pword 0x0D0610,  0x1E0102,  0x91F562,  0x87849B,  0x929E85,  0x72F395
.pword 0x0D0516,  0x323135,  0x31383E,  0x610700,  0x8F8983,  0xB6B2B1
.pword 0xB5B1B6,  0x84818D,  0x6F4097,  0x0C001D,  0x070002,  0x94701F
.pword 0x8E8199,  0x80808C,  0xF6E885,  0x011270,  0x323709,  0x3A383F
.pword 0x06083C,  0xB58417,  0xBFB08A,  0xB0B0B2,  0x818FB7,  0x72E89A
.pword 0x031817,  0x0F0F0F,  0x63070C,  0x839EE3,  0x8F8989,  0x9F868D
.pword 0x6DF595,  0x0B0318,  0x3E3D31,  0x3F3A38,  0x15070A,  0xB7B485
.pword 0xBEB8B2,  0xB1BDBD,  0x988189,  0x1665E3,  0x0F0318,  0x0D0C0C
.pword 0x651105,  0x8D86E8,  0x8BB589,  0x9B808D,  0x685FEC,  0x350C05
.pword 0x3E3D31,  0x393B39,  0x110636,  0xB1B494,  0xBBB8B3,  0xB3BDBF
.pword 0x9E868B,  0x1066E6,  0x0C0118,  0x02020D,  0x151C06,  0x829044
.pword 0xB7B588,  0x828EB4,  0x7CE185,  0x0F046A,  0x3D3635,  0x383E3F
.pword 0x353F38,  0x846605,  0xBCB0B6,  0xBDB9BA,  0x80B7B2,  0x72E89F
.pword 0x041E10,  0x000D02,  0x180103,  0xF96717,  0x8C869C,  0x8F8989
.pword 0x9D8782,  0x154DE1,  0x09031B,  0x333134,  0x3D3D32,  0x053432
.pword 0x88E861,  0xBCB0B1,  0xB0B2B9,  0x998CB6,  0x69F491,  0x041C10
.pword 0x040701,  0x6A1F04,  0xEBD666,  0x82849C,  0x8E8E89,  0x9B808F
.pword 0x7DFB90,  0x001915,  0x37350E,  0x303131,  0x0C3630,  0x9F4316
.pword 0xB6B7B5,  0xB6BDBC,  0x87B5B6,  0x4AEB92,  0x1F1715,  0x1B0504
.pword 0x10181A,  0x5F626A,  0x9FEAE6,  0x808381,  0x858382,  0xF7969D
.pword 0x1C6C7A,  0x090D01,  0x363734,  0x363136,  0x6F070A,  0x8B85C3
.pword 0xB3B78A,  0xB5B5B6,  0x979D82,  0x6A60FC,  0x051916,  0x1A181B
.pword 0x14161F,  0xCA4562,  0x9395E5,  0x80809A,  0x858087,  0xF2E8E8
.pword 0x10156E,  0x0D0D01,  0x35350B,  0x353734,  0x690709,  0x8C9DD7
.pword 0xB68A8E,  0x8A8BB4,  0x919C8D,  0x6072E2,  0x1E126F,  0x191F1C
.pword 0x14161D,  0xD9746C,  0x90E8FC,  0x87859F,  0x988484,  0xFF9593
.pword 0x16614D,  0x000418,  0x090F0D,  0x090808,  0x180D0E,  0x915567
.pword 0x8F8D82,  0x8C8AB4,  0x938389,  0x74EC96,  0x116067,  0x12121C
.pword 0x15101C,  0x75626A,  0xE1C8D7,  0x9394EB,  0x9B8598,  0x979E99
.pword 0x40FCE6,  0x12146E,  0x060705,  0x020203,  0x030D0D,  0x611B01
.pword 0x84E05C,  0x898080,  0x8C8288,  0x919E82,  0x77C094,  0x116E76
.pword 0x101616,  0x6F6816,  0xD47460,  0xEFE5C2,  0x9094E8,  0x9E9D93
.pword 0x96919C,  0xD3F7EE,  0x176873,  0x051B13,  0x060705,  0x060607
.pword 0x120507,  0xE65A7B,  0x848598,  0x86828D,  0x938680,  0xC19591
.pword 0x62445F,  0x156815,  0x6E1516,  0x70606E,  0xF65440,  0xEDE7E5
.pword 0x9194EB,  0x969093,  0xF3E395,  0x6D7F57,  0x1E1315,  0x04051B
.pword 0x070707,  0x050407,  0x77611D,  0x999DF6,  0x838098,  0x868187
.pword 0x96919D,  0x5057F3,  0x696A67,  0x15176A,  0x606F6F,  0x554771
.pword 0xE7E5F6,  0xEAE8ED,  0x979495,  0xE9EA97,  0xD0F4E0,  0x6E664F
.pword 0x13116A,  0x1C1C13,  0x1C1C1D,  0x1C1C1C,  0x4B6416,  0x9D94DB
.pword 0x818492,  0x868785,  0x91919C,  0xC1C3E1,  0x63634B,  0x686863
.pword 0x606263,  0x5A427C,  0xFDF0D8,  0xE2E0FB,  0xEBE8EC,  0xE99494
.pword 0xC2E0EF,  0x634A52,  0x10156B,  0x1F1D1C,  0x1E1E19,  0x1F1919
.pword 0x776310,  0x93E8DD,  0x868592,  0x848485,  0x97969C,  0xD1DAE1
.pword 0x6C6374,  0x156B6D,  0x63626C,  0x5B4C78,  0xFEF0DF,  0xE2E0E5
.pword 0xE3E0E0,  0xE0E4E1,  0xF7FDE0,  0x725BF4,  0x6E6770,  0x146E6C
.pword 0x146815,  0x171514,  0x171711,  0x4E6715,  0x94E155,  0x9B9D97
.pword 0x999E9E,  0xEA9492,  0xDBF7E3,  0x647D53,  0x626164,  0x656561
.pword 0x594D7F,  0xF1C254,  0xE4FBF2,  0xE5E5E4,  0xE7E4E5,  0xF8E5E5
.pword 0x53DDCE,  0x657B71,  0x696963,  0x15156B,  0x171415,  0x171714
.pword 0x736015,  0xEEF047,  0x9C96EB,  0x9C929C,  0xEE9592,  0xD9FDE2
.pword 0x7A4955,  0x666564,  0x7E6561,  0x534A7F,  0xF0C7D6,  0xE4F8FE
.pword 0xE4E7E6,  0xF7FFE5,  0xC2F1F7,  0xDACAC6,  0x53D257,  0x4E4975
.pword 0x7D797D,  0x67677B,  0x6D6367,  0x6E6C62,  0x666D6F,  0xC15F71
.pword 0xEBEFE4,  0x909097,  0x979190,  0xE4E2E8,  0x5BD3F6,  0x677974
.pword 0x616166,  0x796566,  0x584E73,  0xC1DC57,  0xF4CAC9,  0xE4FAFD
.pword 0xF8E5E5,  0x5DDCF4,  0x607B4B,  0x17156F,  0x161616,  0x141616
.pword 0x626B15,  0x514879,  0xEDE7F4,  0x9694E8,  0x949796,  0xE6EFEA
.pword 0x5FC6FD,  0x647977,  0x616061,  0x7E6566,  0x417573,  0xD2555C
.pword 0xCACCC4,  0xF3F0F7,  0xF6F0F3,  0xC5CCF5,  0x5D54D2,  0x41475B
.pword 0x5E4546,  0xDCD450,  0xCDC1DA,  0xCACBC9,  0xF5F5F5,  0xF4F4F4
.pword 0xF3F6F4,  0xF9F9FF,  0xFFF8F8,  0xCCF6F2,  0x4750DF,  0x79734A
.pword 0x666664,  0x616161,  0x676666,  0x4F7C65,  0xF3C551,  0xEAECE7
.pword 0x909197,  0x979190,  0xE4EC95,  0x5BDCF6,  0x657E77,  0x666167
.pword 0x796567,  0x427472,  0xC5D15C,  0xF2F7CE,  0xF9F9FF,  0xF7F2FE
.pword 0xD5D9CC,  0x754D59,  0x727271,  0x777072,  0x464C4A,  0x545259
.pword 0xDFD3D7,  0xC8CDC4,  0xFDF0F4,  0xF2FDFD,  0xDBCEF6,  0x4A5BD5
.pword 0x677A72,  0x6D6360,  0x63626D,  0x676160,  0x7F7B65,  0x534C71
.pword 0xF8F4D8,  0xEBECE1,  0x959495,  0xE2E9EA,  0xCCFFE7,  0x7446D7
.pword 0x7A787D,  0x7B6565,  0x77727E,  0x5F464B,  0xC6DFD5,  0xF0F7C9
.pword 0xF9FCF2,  0xFFF9F9,  0xC8F6F3,  0x58D5DA,  0x657D4A,  0x6F6261
.pword 0x6A6B69,  0x686B6A,  0x606C69,  0x5C747A,  0xE6FCC1,  0x94EAEF
.pword 0x949797,  0xE1EFEA,  0x53C3FC,  0x677E75,  0x626361,  0x616362
.pword 0x7C7B67,  0x5F4D77,  0xCCDBD7,  0xF3F6F5,  0xFDFFFD,  0xF7F1F3
.pword 0xDDC7CE,  0x754650,  0x657973,  0x626066,  0x6D6262,  0x63626D
.pword 0x656660,  0x4F717E,  0xF5D952,  0xE3E7FF,  0xE8E9EF,  0xECE9E8
.pword 0xFFE4E0,  0x56D8F5,  0x754C5A,  0x757474,  0x47434E,  0x535C58
.pword 0x565650,  0x5A5E53,  0x737543,  0x616479,  0x6E6C62,  0x6C6968
.pword 0x4A7861,  0xE7F1D1,  0x9795EF,  0x969191,  0xEE9597,  0xCDFCE1
.pword 0x734C54,  0x666478,  0x666161,  0x7F6567,  0x5D4C71,  0xF7C2DD
.pword 0xFAF9FC,  0xFDF8FA,  0xD1C1F4,  0x774C5F,  0x7B7E7D,  0x787A7A
.pword 0x76727F,  0x594D75,  0xDED156,  0xCEC3C7,  0xF5F5CB,  0xCCC9CA
.pword 0xDEC5C0,  0xD6D1D3,  0x5454D4,  0x565757,  0x5D5051,  0x5B595F
.pword 0x404744,  0x424D4D,  0x40434D,  0x454641,  0x525F5B,  0xD0D556
.pword 0xC3C5DF,  0xF6F4C9,  0xFCF2F3,  0xFEFEFE,  0xFCFFFE,  0xF7F0F2
.pword 0xC7CDCB,  0x57D6DF,  0x46585D,  0x4B4E4D,  0x747475,  0x717677
.pword 0x767671,  0x767676,  0x4B7477,  0x47434F,  0x545258,  0xC4DCD1
.pword 0xF7CACD,  0xFFFDF3,  0xF9FEFE,  0xFCFEFE,  0xCAF6F3,  0xDFC4CD
.pword 0x5254D1,  0x414559,  0x484F4D,  0x45454F,  0x4C4F4F,  0x7C7D77
.pword 0x787C72,  0x707279,  0x407471,  0x515F5E,  0xC2C6DC,  0xF2F6C9
.pword 0xFEFCFC,  0xFFF9F8,  0xFCFEFE,  0xF6F1F0,  0xC6C0C8,  0xD0DFC5
.pword 0x54D6D1,  0x5E5D53,  0x4C4347,  0x767449,  0x7D7370,  0x7D7D7C
.pword 0x737D7D,  0x4B7476,  0x5B464D,  0xD1575C,  0xC0DBDC,  0xF7F5C9
.pword 0xF0F0F1,  0xF3F3F3,  0xF1F1F0,  0xCBF4F6,  0xC0CFC9,  0xDFD8C4
.pword 0x54D4D0,  0x455953,  0x484F40,  0x767475,  0x737370,  0x737373
.pword 0x717070,  0x4B7577,  0x47434E,  0x565C5B,  0xDED3D7,  0xC3C7C5
.pword 0xCAC9CF,  0xF4F4F5,  0xF4F4F4,  0xCBF5F4,  0xCFC9C9,  0xC7C1C3
.pword 0xDCD9DA,  0x57D4D3,  0x5F5056,  0x445B59,  0x484E43,  0x75754B
.pword 0x484B4A,  0x4C4E49,  0x444142,  0x5D5E5B,  0x545650,  0xDDD3D4
.pword 0xDBD9DD,  0xC5DBDB,  0xC4C4C4,  0xC1C0C1,  0xC6C6C1,  0xC5C5C7
.pword 0xDCD8C5,  0xD3DDDC,  0xD7D6D6,  0x515154,  0x5B595D,  0x464445
.pword 0x424242,  0x4F4F4D,  0x4F4F4F,  0x43424D,  0x474641,  0x595B45
.pword 0x525C5C,  0x575751,  0xD6D755,  0xD6D7D7,  0xD1D1D1,  0xD0D3D3
.pword 0xD3D0D1,  0xD3D0D0,  0xD7D7D1,  0xD7D6D6,  0xD5D4D4,  0x575455
.pword 0x525051,  0x5D5252,  0x5F5F5C,  0x5E5E5E,  0x5E5E5E,  0x5C5C5C
.pword 0x53525C,  0x575053,  0x555757,  0xD7D5D5,  0xD3D1D6,  0xD2DDD2
.pword 0xDDDDDD,  0xDCDCDD,  0xDCDFDF,  0xDCDFDC,  0xD2D2DD,  0xD1D6D0
.pword 0xD5D7D1,  0x54D5D5,  0x545757,  0x515156,  0x535350,  0x505050
.pword 0x505050,  0x525353,  0x535353,  0x505053,  0x565053,  0x565656
.pword 0x575454,  0x565754,  0x5C5D50,  0x595E5F,  0x595959,  0x595959
.pword 0x5E5959,  0x59595E,  0x5F5F5E,  0x5E5E5E,  0x5E595E,  0x5F5F5E
.pword 0x5D5C5C,  0x5D5D5C,  0x53525D,  0x505353,  0x515156,  0x515651
.pword 0x545756,  0x555554,  0xD555D5,  0xD7D7D4,  0xD0D6D7,  0xD3D1D1
.pword 0xD3D0D3,  0xD0D3D2,  0xD2D3D3,  0xD2D2D3,  0xD2D2D2,  0xD2D2D2
.pword 0xD2D2D2,  0xD2D3D3,  0xD0D3D2,  0xD3D3D3,  0xD1D0D0,  0xD0D6D1
.pword 0xD1D1D1,  0xD1D1D1,  0xD0D1D1,  0xD0D0D3,  0xD1D0D0,  0xD1D1D6
.pword 0xD1D1D1,  0xD6D1D0,  0xD7D6D6,  0xD7D7D7,  0xD7D7D7,  0xD7D7D7
.pword 0xD7D4D4,  0xD7D4D4,  0xD4D7D7,  0xD4D7D4,  0xD4D4D4,  0xD7D4D4
.pword 0x5455D5,  0x505157,  0x525252,  0x5F5C5D,  0x5E5E5F,  0x5E5E5E
.pword 0x5C5C5E,  0x525C5C,  0x505353,  0x000057        
