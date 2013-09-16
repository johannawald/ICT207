#pragma once

enum TextureCodes { NONE,
					GRASS, //1 
				    GRASS_2, 
				    GRASS_HILL, 
				    PAVEMENT, 
				    PAVEMENT_TOP, 
				    PAVEMENTSIDE_LEFT,
				    PAVEMENTSIDE_RIGHT, 
				    PAVEMENTSIDE_TOP, 
				    PAVEMENT_CORNER_1, 
				    PAVEMENT_CORNER_2, 
				    PAVEMENT_FLIP, 
				    PAVEMENT_TOP_FLIP, 
				    PAVEMENT_16, 
				    DOORPAVE_1, 
				    WALL_BRICK_YZ, 
				    WALL_BRICK_XY, 
				    WALL_BRICK_XY_87WIDTH, 
				    WALL_BRICK_GAP_YZ, 
				    WALL_BRICK_GAP2_YZ,
				    WALL_BRICK_USD_YZ, 
				    WALL_BRICK_XY_END, 
				    WALL_BRICK_YZ_END, 
				    WALL_GAP_1, 
				    WALL_BRICK_3_4, 
 				    SHADOW_BRICK, 
 				    WINDOWPOST_CHANC_FRONT, //		26
					WINDOWPOST_CHANC_RIGHT, //	    27
					WINDOWPOST_CHANC_LEFT, //	    28
					WINDOWLEDGE_CHANC_FRONT, //		29
					WINDOWLEDGE_CHANC_TOP, //		30
					WINDOWPOST_PHYSSCI_FRONT, //	31
					WINDOWPOST_PHYSSCI_RIGHT, //	32
					WINDOWPOST_PHYSSCI_LEFT, //		33
					WINDOWPOST_LIB_FRONT, //		34
					WINDOWPOST_LIB_LEFT, //			35
					WINDOWPOST_LIB_RIGHT, //		36
					DOOR_POST_SECURITY, //			37
					WINDOWLEDGE_PS_FRONT, //		38
					WINDOWLEDGE_PS_TOP, //			39
					WINDOWLEDGE_PS_BOTT, //			40
					WINDOWLEDGE_LIB_A, //			41
					WINDOWLEDGE_LIB_B, //			42
					WINDOWLEDGE_LIB_TOP_A, //		43
					WINDOWLEDGE_LIB_TOP_B, //		44
					WINDOW_LEDGE_END_1, //			45
					WINDOW_LEDGE_END_2, //			46
					MAIN_POST, //					47
					MAIN_POST_2, //					48
					DOOR_POST_CHANC, //				49
					DOOR_SIDEPOST_CHANC, //			50
					PURPLE_POST, //					51
					PURPLE_POSTSIDE, //				52
					RED_POST, //					53
					RED_POSTSIDE, //				54
					ROOF_TOP, //					55
					ROOF_TOP_LIB, //				56
					ROOF_PLANKS, //					57
					ROOF_BEAM_1, //					58
					ROOF_PLANKS_2, //				59
					ROOF_BEAM_2, //					60
					BELOW_ROOF_FILL, //				61
					ROOF_BEAM_3, //					62
					ROOF_BEAM_4, //					63
					ROOF_BEAM_3_TOP, //				64
					KBLT, //						65
					KBLT_EDGE, //					66
					KBLT_EDGE_2, //					67
					KBLT_EDGE_CORNER, //			68
					KBLT_SIDE_1, //					69
					KBLT_SIDE_2, //					70
					NEXUS_SIGN, //					71
					NEXUS_SIDE, //					72
					SECURITY_SIGN, //				73
					SECURITY_SIGN_2, //				74
					SIGN_1, //						75
					SIGN_1_SIDE_1, //				76
					SIGN_1_SIDE_2, //				77
					SIGN_2, //						78
					SIGN_2_SIDE, //					79
					PSC_SIGN, //					80
					PSC_SIGN_2, //					81
					CO_SIGN, //						82
					STA_TRAVEL, //					83
					STA_TRAVEL_EDGE, //				84
					STA_TRAVEL_BRACKET, //			85
					STA_TRAVEL_2, //				86
					STA_TRAVEL_BOTTOM, //			87
					TOILET_MEN, //					88
					TOILET_WOMEN, //				89
					GS_SIGN, //						90
					GS_SIGN_2, //					91
					GS_SIGN_EDGE, //				92
					MAP_2, //						93
					GLASS_BOARD, //					94
					GLASS_BOARD_2, //				95
					GLASS_BOARD_3, //				96
					GLASS_B_SIDE, //				97
					RUSTY_MAN, //					98
					NO_SMOKE_SIGN, //				99
					CARPET, //						100
					DRINKS_SIDE, //				101
					DRINKS_TOP, //					102
					DRINKS_EDGE, //					103
					DRINKS_SIDE_2, //				104
					COKE_MACHINE, //				105
					COFFEE_MACHINE, //				106
					SWEET_MACHINE, //				107
					MACHINE_SIDES, //				108
					MACHINE_SIDES_2, //				109
					TELEPHONE_BACK, //				110
					TELEPHONE_FRONT, //				111
					TELEPHONE_SIDE_1, //			112
					TELEPHONE_FRONT_2, //			113
					TELEPHONE_MAIN_SIDE, //			114
					TELEPHONE_TOP_1, //				115
					TELEPHONE_SIDE_2, //			116
					TELEPHONE_TOP_2, //				117
					TELEPHONE_BOTTOM, //			118
					TELEPHONE_FILL, //				119
					TELEPHONE_FRONT_3, //			120
					STEPS_LIBRARY, //				121
					STEPS_LIBRARY_TOP, //			122
					STEP_PAVING_1, //				123
					STEP_EDGE, //					124
					WINDOW_1, //					125
					WINDOW_2, //					126
					WINDOW_3, //					127
					WINDOW_4, //					128
					WINDOW_5, //					129
					WINDOW_6, //					130
					WINDOW_7, //					131
					WINDOW_8, //					132
					WINDOW_9, //					133
					WINDOW_10, //					134
					WINDOW_11, //					135
					WINDOW_12, //					136
					WINDOW_13, //					137
					WINDOW_14, //					138
					WINDOW_14B, //					139
					WINDOW_15, //				140
					WINDOW_16, //				141
					WINDOW_17, //					142
					WINDOW_2B, //					143
					WINDOW_2C, //					144
					WINDOW_2US, //					145
					WINDOW_3B	, //				146
					WINDOW_2USB, //					147
					WINDOW_LIB_1	, //			148
					WINDOW_LIB_1A		, //		149
					WINDOW_LIB_1B			, //	150
					WINDOW_LIB_1C				, //151
					WINDOW_LIB_US_A, //				152
					WINDOW_LIB_US_B	, //			153
					WINDOW_LIB_DOOR_1, //			154
					WINDOW_LIB_DOOR_2, //			155
					WINDOW_LIB_LONG	, //			156
					ENTRANCE		, //			157
					ENTRANCE_2		, //			158
					EXIT_EAST		, //			159
					CHANC_DOOR_1				, //160
					CHANC_DOOR_2				, //161
					WINDOW_2D, //					162
					WINDOW_2E, //					163
					WINDOW_1B, //					164

					ABOVE_WINDOW_BLOCK, //			165
					ABOVE_WINDOW_BLOCK_2, //		166
					ABOVE_WINDOW_BLOCK_3, //		167
					ABOVE_WINDOW_EDGE_3B, //		168
					ABOVE_WINDOW_BLOCK_XY_3, //		169
					ABOVE_LIB	, //				170
					ABOVE_UNDER_POSTS, //			171
					ABOVE_UNDER_POSTS_2	, //		172
					ABOVE_WINDOW_UNDER_LIB	, //	173
					ABOVE_WINDOW_BLOCK_CHANC	, //174
					ABOVE_WINDOW_EDGE_3B_LIB, //	175
					ABOVE_WINDOW_EDGE_4B_LIB, //	176
					ABOVE_UNDER_4B	, //			177
					ABOVE_CHANC_TEXT	, //		178
					ABOVE_CHANC_TEXT_2, //			179
					ABOVE_PHYS_SCI_TEXT, //			180
					ABOVE_CHANC_TEXT_3, //			181
					ABOVE_LIB_TEXT, //				182
					ABOVE_LIB_TEXT_2, //			183
					ABOVE_TICKETS_TEXT, //			184
					ABOVE_CHANC_EDGE, //			185
					TOILET_DOOR_TOP, //				186
					LIGHT, //						187
					LIGHT_SUPPORT, //				188
					LIGHT_SUPPORT_2, //				189
					BENCH_TOP, //					190
					BENCH_SIDE, //					191
					BENCH_SIDE_2, //				192
					BENCH_EDGE	, //				193
					BENCH_EDGE_TOP, //				194
					BENCH_EDGE_SIDE		, //		195
					BENCH_EDGE_TOP_2		, //	196
					BENCH_EDGE_2	, //			197
					BENCH_EDGE_3	, //			198

					NONE_WHY, //??

					TICKET_COUNTER_TOP, //			200
					TICKET_COUNTER_EDGE, //			201
					TICKET_COUNTER_EDGE_2, //		202
					TICKET_COUNTER_EDGE_3, //		203
					TICKET_LEDGE, //				204
					TICKET_LEDGE_EDGE, //			205
					TICKET_LEDGE_EDGE_2, //			206
				
					WALL_BRICK_STEPS_TOP, //		207
					WALL_BRICK_STEPS, //			208
					WALL_BRICK_STEPS_COVER, //		209
					WALL_BRICK_STEPS_EDGE, //		210
					WALL_BRICK_STEPS_EDGE_2, //		211
					 
					DRAINPIPE, //					212
					COUNTER_TOP, //					213
					COUNTER_SIDE	, //			214
					DOOR_POST_LIB, //				215
					WALL_BRICK_SEC_SIGN	, //		216
					MAP				,//			217
					WELCOME				,//		218
					EXIT				,//		219
					EXIT_WEST			,//		220
					
					
					STEP_WINDOW,//					221
					NO_EXIT,	//					222
					BANNER, // 223
					NUMBERPAD,	// 224
					VENDING_MACHINE  //225
};