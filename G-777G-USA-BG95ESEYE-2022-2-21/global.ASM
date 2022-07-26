; Generated by holtek-gcc v3.18, Mon Sep 10 09:39:41 2018
; 
; Configuration:
;       without long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.18" "build 20130711"
; Rebuild 521

ir equ [2]
mp equ [3]
sbp equ [1]
acc equ [5]
bp equ [4]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
intc equ [11]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @HCCINIT, @HCCINIT0

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
public _Delay_25mSx
#pragma debug scope 2 1
#line 13 "D:\zhan\G-777-test\global.c"
_Delay_25mSx .section 'code'
_Delay_25mSx proc
    local _Delay_25mSx_2 db 1 dup(?)	; 0,1
	mov _Delay_25mSx_2[0],a
#pragma debug variable 8 2 _Delay_25mSx_2+0 "SEC"
#line 14 "D:\zhan\G-777-test\global.c"
	clr _i5[0]
	jmp _L2
_L3:
#line 16 "D:\zhan\G-777-test\global.c"
	mov a,25
	mov _me_delay_ms_2[0],a
	clr _me_delay_ms_2[1]
	fcall _me_delay_ms
#line 14 "D:\zhan\G-777-test\global.c"
	inc _i5[0]
_L2:
	mov a,_i5[0]
	sub a,_Delay_25mSx_2[0]
	snz c
	jmp _L3
	ret
_Delay_25mSx endp
#line 14 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
___adcr0 equ [68]
___adrh equ [67]
___adrl equ [61]
public _GlobFun_Adc
#pragma debug scope 3 1
#line 25 "D:\zhan\G-777-test\global.c"
_GlobFun_Adc .section 'code'
_GlobFun_Adc proc
    local _GlobFun_Adc_2 db 3 dup(?)	; 0,3
	mov _GlobFun_Adc_2[0],a
#pragma debug variable 8 3 _GlobFun_Adc_2+0 "T"
#line 26 "D:\zhan\G-777-test\global.c"
	clr _Adc_Data16T[0]
	clr _Adc_Data16T[1]
#line 29 "D:\zhan\G-777-test\global.c"
	clr _i1[0]
	jmp _L6
_L8:
#line 31 "D:\zhan\G-777-test\global.c"
	clr [68].7
#line 32 "D:\zhan\G-777-test\global.c"
;# 32 "D:\zhan\G-777-test\global.c" 1
	nop
#line 33 "D:\zhan\G-777-test\global.c"
	set [68].7
#line 34 "D:\zhan\G-777-test\global.c"
;# 34 "D:\zhan\G-777-test\global.c" 1
	nop
#line 35 "D:\zhan\G-777-test\global.c"
	clr [68].7
#line 40 "D:\zhan\G-777-test\global.c"
	fcall _me_delay_150us
#line 43 "D:\zhan\G-777-test\global.c"
	sz [68].6
	jmp _L7
#line 46 "D:\zhan\G-777-test\global.c"
	mov a,[67]
	mov _GlobFun_Adc_2[2],a
	clr _GlobFun_Adc_2[1]
	mov a,_GlobFun_Adc_2[2]
	mov rc,a
	mov a,[61]
	or a,_GlobFun_Adc_2[1]
	mov rb,a
#line 47 "D:\zhan\G-777-test\global.c"
	mov a,rb
	mov rd,a
	mov a,rc
	mov re,a
	mov a,4
_LI1:
	clr c
	rrc re
	rrc rd
	sdz acc
	jmp _LI1
	mov a,rd
	mov _Adc_DataTemp[0],a
	mov a,re
	mov _Adc_DataTemp[1],a
_L7:
#line 50 "D:\zhan\G-777-test\global.c"
	mov a,_Adc_DataTemp[0]
	addm a,_Adc_Data16T[0]
	mov a,_Adc_DataTemp[1]
	adcm a,_Adc_Data16T[1]
#line 29 "D:\zhan\G-777-test\global.c"
	inc _i1[0]
_L6:
	mov a,_i1[0]
	sub a,_GlobFun_Adc_2[0]
	snz c
	jmp _L8
	ret
_GlobFun_Adc endp
#line 29 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_Adc_Data16Tx16
#pragma debug scope 4 1
#line 59 "D:\zhan\G-777-test\global.c"
_GET_Adc_Data16Tx16 .section 'code'
_GET_Adc_Data16Tx16 proc
#line 61 "D:\zhan\G-777-test\global.c"
	mov a,16
	fcall _GlobFun_Adc
#line 62 "D:\zhan\G-777-test\global.c"
	clr _Adc_Data16Tx16[0]
	clr _Adc_Data16Tx16[1]
#line 64 "D:\zhan\G-777-test\global.c"
	clr _i2[0]
	jmp _L10
_L11:
#line 66 "D:\zhan\G-777-test\global.c"
	mov a,16
	fcall _GlobFun_Adc
#line 67 "D:\zhan\G-777-test\global.c"
	mov a,_Adc_Data16T[0]
	mov rb,a
	mov a,_Adc_Data16T[1]
	mov rc,a
	mov a,4
_LI2:
	clr c
	rrc rc
	rrc rb
	sdz acc
	jmp _LI2
	mov a,rb
	mov _Adc_DataTemp[0],a
	mov a,rc
	mov _Adc_DataTemp[1],a
#line 68 "D:\zhan\G-777-test\global.c"
	mov a,rb
	addm a,_Adc_Data16Tx16[0]
	mov a,rc
	adcm a,_Adc_Data16Tx16[1]
#line 64 "D:\zhan\G-777-test\global.c"
	inc _i2[0]
_L10:
	mov a,15
	sub a,_i2[0]
	sz c
	jmp _L11
	ret
_GET_Adc_Data16Tx16 endp
#line 64 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_Adc_Data16Tx8
#pragma debug scope 5 1
#line 82 "D:\zhan\G-777-test\global.c"
_GET_Adc_Data16Tx8 .section 'code'
_GET_Adc_Data16Tx8 proc
#line 84 "D:\zhan\G-777-test\global.c"
	mov a,4
	fcall _GlobFun_Adc
#line 85 "D:\zhan\G-777-test\global.c"
	clr _Adc_Data16Tx16[0]
	clr _Adc_Data16Tx16[1]
#line 87 "D:\zhan\G-777-test\global.c"
	clr _i2[0]
	jmp _L13
_L14:
#line 89 "D:\zhan\G-777-test\global.c"
	mov a,16
	fcall _GlobFun_Adc
#line 90 "D:\zhan\G-777-test\global.c"
	mov a,_Adc_Data16T[0]
	mov rb,a
	mov a,_Adc_Data16T[1]
	mov rc,a
	mov a,4
_LI3:
	clr c
	rrc rc
	rrc rb
	sdz acc
	jmp _LI3
	mov a,rb
	mov _Adc_DataTemp[0],a
	mov a,rc
	mov _Adc_DataTemp[1],a
#line 91 "D:\zhan\G-777-test\global.c"
	mov a,rb
	addm a,_Adc_Data16Tx16[0]
	mov a,rc
	adcm a,_Adc_Data16Tx16[1]
#line 87 "D:\zhan\G-777-test\global.c"
	inc _i2[0]
_L13:
	mov a,7
	sub a,_i2[0]
	sz c
	jmp _L14
	ret
_GET_Adc_Data16Tx8 endp
#line 87 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_BG_Data16
#pragma debug scope 6 1
#line 101 "D:\zhan\G-777-test\global.c"
_GET_BG_Data16 .section 'code'
_GET_BG_Data16 proc
#line 102 "D:\zhan\G-777-test\global.c"
	clr [68].2
#line 103 "D:\zhan\G-777-test\global.c"
	clr [68].1
#line 104 "D:\zhan\G-777-test\global.c"
	set [68].0
#line 105 "D:\zhan\G-777-test\global.c"
	mov a,16
	fcall _GlobFun_Adc
	ret
_GET_BG_Data16 endp
#line 105 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_BG_Data256
#pragma debug scope 7 1
#line 113 "D:\zhan\G-777-test\global.c"
_GET_BG_Data256 .section 'code'
_GET_BG_Data256 proc
#line 114 "D:\zhan\G-777-test\global.c"
	clr [68].2
#line 115 "D:\zhan\G-777-test\global.c"
	clr [68].1
#line 116 "D:\zhan\G-777-test\global.c"
	set [68].0
#line 117 "D:\zhan\G-777-test\global.c"
	fcall _GET_Adc_Data16Tx16
	ret
_GET_BG_Data256 endp
#line 117 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_BG_Data128
#pragma debug scope 8 1
#line 125 "D:\zhan\G-777-test\global.c"
_GET_BG_Data128 .section 'code'
_GET_BG_Data128 proc
#line 126 "D:\zhan\G-777-test\global.c"
	clr [68].2
#line 127 "D:\zhan\G-777-test\global.c"
	clr [68].1
#line 128 "D:\zhan\G-777-test\global.c"
	set [68].0
#line 129 "D:\zhan\G-777-test\global.c"
	fcall _GET_Adc_Data16Tx8
	ret
_GET_BG_Data128 endp
#line 129 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _GET_NTC_Data
#pragma debug scope 9 1
#line 137 "D:\zhan\G-777-test\global.c"
_GET_NTC_Data .section 'code'
_GET_NTC_Data proc
#line 138 "D:\zhan\G-777-test\global.c"
	clr [68].2
#line 139 "D:\zhan\G-777-test\global.c"
	clr [68].1
#line 140 "D:\zhan\G-777-test\global.c"
	clr [68].0
#line 142 "D:\zhan\G-777-test\global.c"
	fcall _GET_Adc_Data16Tx16
#line 144 "D:\zhan\G-777-test\global.c"
	mov a,73
	mov _Adc_DataTemp[0],a
	mov a,10
	mov _Adc_DataTemp[1],a
#line 145 "D:\zhan\G-777-test\global.c"
	mov a,_Adc_Data16Tx16[0]
	mov rb,a
	mov a,_Adc_Data16Tx16[1]
	mov rc,a
	mov a,144
	sub a,rb
	mov a,164
	sbc a,rc
	sz c
	jmp _L19
#line 147 "D:\zhan\G-777-test\global.c"
	mov a,9
	mov _Temperature[0],a
	jmp _L18
_L19:
	mov a,73
	mov rd,a
	mov a,10
	mov re,a
	mov a,_Temperature[0]
	mov rh,a
#line 151 "D:\zhan\G-777-test\global.c"
	clr ra
_L21:
	mov a,31
	sub a,ra
	snz c
	jmp _L24
#line 153 "D:\zhan\G-777-test\global.c"
	mov a,low offset _NTC_table
	add a,ra
	mov mp,a
	mov a,high offset _NTC_table
	clr sbp
	adcm a,sbp
	fcall _Crom2Prom
	mov rf,a
	mov a,rd
	sub a,rf
	mov rd,a
	mov a,re
	clr re
	sbcm a,re
#line 154 "D:\zhan\G-777-test\global.c"
	swapa re
	and a,0f0h
	mov rg,a
	swapa rd
	and a,0fh
	orm a,rg
	swapa rd
	and a,0f0h
	mov rf,a
	mov a,rb
	sub a,rf
	mov a,rc
	sbc a,rg
	sz c
	jmp _L22
#line 156 "D:\zhan\G-777-test\global.c"
	mov a,ra
	add a,10
	mov rh,a
_L22:
	inc ra
	jmp _L21
_L24:
	mov a,rd
	mov _Adc_DataTemp[0],a
	mov a,re
	mov _Adc_DataTemp[1],a
	mov a,rh
	mov _Temperature[0],a
	mov a,ra
	mov _i2[0],a
_L18:
	ret
_GET_NTC_Data endp
#line 156 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
___pb equ [29]
public _GET_1_2VCC_Data256
#pragma debug scope 10 1
#line 169 "D:\zhan\G-777-test\global.c"
_GET_1_2VCC_Data256 .section 'code'
_GET_1_2VCC_Data256 proc
#line 170 "D:\zhan\G-777-test\global.c"
	clr [29].6
#line 172 "D:\zhan\G-777-test\global.c"
	clr [68].2
#line 173 "D:\zhan\G-777-test\global.c"
	set [68].1
#line 174 "D:\zhan\G-777-test\global.c"
	clr [68].0
#line 175 "D:\zhan\G-777-test\global.c"
	mov a,2
	fcall _Delay_25mSx
#line 177 "D:\zhan\G-777-test\global.c"
	fcall _GET_Adc_Data16Tx16
#line 182 "D:\zhan\G-777-test\global.c"
	set [29].6
	ret
_GET_1_2VCC_Data256 endp
#line 182 "D:\zhan\G-777-test\global.c"
#pragma debug scope 1 1
public _CTL_T_table
@crom	.section 'crom'
#line 81 "D:\zhan\G-777-test\global.h"
@crom	.section	'crom'
_CTL_T_table:
#pragma debug array 42 8 31 1
#pragma debug variable 42 1 _CTL_T_table "CTL_T_table"
	db 114
	db 114
	db 113
	db 112
	db 110
	db 109
	db 108
	db 105
	db 102
	db 101
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 98
	db 97
	db 95
	db 94
	db 92
	db 90
	db 89
	db 87
	db 86
	db 84
	db 83
	db 82
	db 81
	db 80
	db 79
public _BG_T_table
#line 47 "D:\zhan\G-777-test\global.h"
@crom	.section	'crom'
_BG_T_table:
#pragma debug variable 42 1 _BG_T_table "BG_T_table"
	db 111
	db 110
	db 108
	db 107
	db 106
	db 106
	db 105
	db 105
	db 104
	db 103
	db 103
	db 102
	db 102
	db 101
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
	db 100
public _NTC_table
#line 12 "D:\zhan\G-777-test\global.h"
@crom	.section	'crom'
_NTC_table:
#pragma debug array 43 8 32 1
#pragma debug variable 43 1 _NTC_table "NTC_table"
	db 0
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 39
	db 38
	db 38
	db 38
	db 37
	db 37
	db 37
	db 37
	db 36
	db 36
	db 35
	db 35
	db 35
	db 34
	db 34
	db 33
	db 33
#line 10 "D:\zhan\G-777-test\global.h"
public _Temperature
@HCCINIT0 .section 'data'
_Temperature	db 0
#pragma debug variable 8 1 _Temperature "Temperature"

@HCCINIT .section 'data'
#line 8 "D:\zhan\G-777-test\global.h"
public _BG_Val
@HCCINIT0 .section 'data'
_BG_Val	db 4 dup(0)
#pragma debug variable 14 1 _BG_Val "BG_Val"

@HCCINIT .section 'data'
#line 7 "D:\zhan\G-777-test\global.h"
public _i5
@HCCINIT0 .section 'data'
_i5	db 0
#pragma debug variable 8 1 _i5 "i5"

@HCCINIT .section 'data'
#line 7 "D:\zhan\G-777-test\global.h"
public _i4
@HCCINIT0 .section 'data'
_i4	db 0
#pragma debug variable 8 1 _i4 "i4"

@HCCINIT .section 'data'
#line 7 "D:\zhan\G-777-test\global.h"
public _i3
@HCCINIT0 .section 'data'
_i3	db 0
#pragma debug variable 8 1 _i3 "i3"

@HCCINIT .section 'data'
#line 7 "D:\zhan\G-777-test\global.h"
public _i2
@HCCINIT0 .section 'data'
_i2	db 0
#pragma debug variable 8 1 _i2 "i2"

@HCCINIT .section 'data'
#line 7 "D:\zhan\G-777-test\global.h"
public _i1
@HCCINIT0 .section 'data'
_i1	db 0
#pragma debug variable 8 1 _i1 "i1"

@HCCINIT .section 'data'
#line 5 "D:\zhan\G-777-test\global.h"
public _i16b
@HCCINIT0 .section 'data'
_i16b	db 2 dup(0)
#pragma debug variable 12 1 _i16b "i16b"

@HCCINIT .section 'data'
#line 5 "D:\zhan\G-777-test\global.h"
public _BG_AD
@HCCINIT0 .section 'data'
_BG_AD	db 2 dup(0)
#pragma debug variable 12 1 _BG_AD "BG_AD"

@HCCINIT .section 'data'
#line 5 "D:\zhan\G-777-test\global.h"
public _Adc_Data16Tx16
@HCCINIT0 .section 'data'
_Adc_Data16Tx16	db 2 dup(0)
#pragma debug variable 12 1 _Adc_Data16Tx16 "Adc_Data16Tx16"

@HCCINIT .section 'data'
#line 5 "D:\zhan\G-777-test\global.h"
public _Adc_Data16T
@HCCINIT0 .section 'data'
_Adc_Data16T	db 2 dup(0)
#pragma debug variable 12 1 _Adc_Data16T "Adc_Data16T"

@HCCINIT .section 'data'
#line 5 "D:\zhan\G-777-test\global.h"
public _Adc_DataTemp
@HCCINIT0 .section 'data'
_Adc_DataTemp	db 2 dup(0)
#pragma debug variable 12 1 _Adc_DataTemp "Adc_DataTemp"

@HCCINIT .section 'data'
#pragma debug struct_begin 44 "__pb_bits"
#pragma debug field 21 8 0 1 "__pb0" ;0,1
#pragma debug field 21 8 0 1 "__pb1" ;1,1
#pragma debug field 21 8 0 1 "__pb2" ;2,1
#pragma debug field 21 8 0 1 "__pb3" ;3,1
#pragma debug field 21 8 0 1 "__pb4" ;4,1
#pragma debug field 21 8 0 1 "__pb5" ;5,1
#pragma debug field 21 8 0 1 "__pb6" ;6,1
#pragma debug field 21 8 0 1 "__pb7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___pb "__pb" 1
#pragma debug variable 8 1 ___adrl "__adrl" 1
#pragma debug variable 8 1 ___adrh "__adrh" 1
#pragma debug struct_begin 46 "__adcr0_bits"
#pragma debug field 21 8 0 1 "__acs0" ;0,1
#pragma debug field 21 8 0 1 "__acs1" ;1,1
#pragma debug field 21 8 0 1 "__acs2" ;2,1
#pragma debug field 21 8 0 2 ;3,2
#pragma debug field 21 8 0 1 "__adoff" ;5,1
#pragma debug field 21 8 0 1 "__eocb" ;6,1
#pragma debug field 21 8 0 1 "__start" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___adcr0 "__adcr0" 1
extern _me_delay_ms_2:byte
extern _me_delay_ms:near
extern _me_delay_150us:near

; 
; Generated by holtek-gcc v3.18, Mon Sep 10 09:39:41 2018
; Rebuild 521
; end of file
