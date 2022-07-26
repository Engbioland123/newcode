; Generated by holtek-gcc v3.19, Tue Jul 26 12:07:02 2022
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 32
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 718

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [32]

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
___intc0 equ [32]
___sadc0 equ [109]
___sadc1 equ [110]
___pcs0 equ [343]
___sadol equ [107]
___sadoh equ [108]
public _Samlpe_Adc1
#pragma debug scope 2 1
#line 14 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
_Samlpe_Adc1 .section 'code'
_Samlpe_Adc1 proc
    local _Samlpe_Adc1_2 db 1 dup(?)	; 0,1
	mov _Samlpe_Adc1_2[0],a
#pragma debug variable 8 2 _Samlpe_Adc1_2+0 "ch"
#line 18 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,[32]
	and a,1
	mov ra,a
#line 19 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [32].0
#line 21 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,63
	mov [109],a
#line 22 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,239
	mov [110],a
#line 25 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,_Samlpe_Adc1_2[0]
	sub a,0
	sz z
	jmp _L3
	sub a,(1)-(0)
	sz z
	jmp _L4
#line 25 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,_Samlpe_Adc1_2[0]
	sub a,2
	sz z
	jmp _L5
	sub a,(3)-(2)
	sz z
	jmp _L6
	mov a,_Samlpe_Adc1_2[0]
	sub a,4
	sz z
	jmp _L7
	sub a,(5)-(4)
	sz z
	jmp _L8
	mov a,_Samlpe_Adc1_2[0]
	sub a,6
	sz z
	jmp _L9
	mov a,_Samlpe_Adc1_2[0]
	sub a,7
	snz z
	jmp _L2
#line 35 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,159
	andm a,[110]
	jmp _L2
_L3:
#line 28 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,240
	andm a,[109]
	lset [343].5
	lset [343].4
	jmp _L2
_L4:
#line 29 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,241
	andm a,[109]
	lset [343].7
	lset [343].6
	jmp _L2
_L5:
#line 30 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,242
	andm a,[109]
	lset [343].1
	lset [343].0
	jmp _L2
_L6:
#line 31 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,243
	andm a,[109]
	lset [343].3
	lset [343].2
	jmp _L2
_L7:
#line 32 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,63
	andm a,[110]
	jmp _L2
_L8:
#line 33 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,95
	andm a,[110]
	jmp _L2
_L9:
#line 34 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [110].7
_L2:
#line 37 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [109].7
#line 38 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	set [109].7
#line 39 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [109].7
_L12:
#line 40 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	sz [109].6
	jmp _L12
#line 46 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,[108]
	mov rc,a
	clr rb
#line 47 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,[107]
	addm a,rb
	sz c
	inc rc
#line 48 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,rb
	mov rd,a
	mov a,rc
	mov re,a
	clr c
	rrc re
	rrc rd
	clr c
	rrc re
	rrc rd
	mov a,rd
	mov _ADCVALV[0],a
	mov a,re
	mov _ADCVALV[1],a
#line 49 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [32].0
	mov a,ra
	orm a,[32]
#line 51 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,_ADCVALV[0]
	mov ra,a
	mov a,_ADCVALV[1]
	mov rb,a
	ret
_Samlpe_Adc1 endp
#line 51 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
#pragma debug scope 1 1
public _Samlpe_Adc
#pragma debug scope 3 1
#line 60 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
_Samlpe_Adc .section 'code'
_Samlpe_Adc proc
    local _Samlpe_Adc_2 db 1 dup(?)	; 0,1
	mov ra,a
	mov _Samlpe_Adc_2[0],a
#pragma debug variable 8 3 _Samlpe_Adc_2+0 "ch"
#line 63 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,63
	mov [109],a
#line 64 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,239
	mov [110],a
#line 67 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,ra
	sub a,0
	sz z
	jmp _L16
	sub a,(1)-(0)
	sz z
	jmp _L17
#line 67 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,ra
	sub a,2
	sz z
	jmp _L18
	sub a,(3)-(2)
	sz z
	jmp _L19
	mov a,ra
	sub a,4
	sz z
	jmp _L20
	sub a,(5)-(4)
	sz z
	jmp _L21
	mov a,ra
	sub a,6
	sz z
	jmp _L22
	mov a,ra
	sub a,7
	snz z
	jmp _L15
#line 77 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,159
	andm a,[110]
	jmp _L15
_L16:
#line 70 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,240
	andm a,[109]
	lset [343].5
	lset [343].4
	jmp _L15
_L17:
#line 71 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,241
	andm a,[109]
	lset [343].7
	lset [343].6
	jmp _L15
_L18:
#line 72 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,242
	andm a,[109]
	lset [343].1
	lset [343].0
	jmp _L15
_L19:
#line 73 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,243
	andm a,[109]
	lset [343].3
	lset [343].2
	jmp _L15
_L20:
#line 74 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,63
	andm a,[110]
	jmp _L15
_L21:
#line 75 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,95
	andm a,[110]
	jmp _L15
_L22:
#line 76 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [110].7
_L15:
#line 79 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [109].7
#line 80 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	set [109].7
#line 81 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	clr [109].7
_L25:
#line 82 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	sz [109].6
	jmp _L25
#line 88 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,[108]
	mov rc,a
	clr rb
#line 89 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,[107]
	addm a,rb
	sz c
	inc rc
#line 91 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
	mov a,rb
	mov ra,a
	mov a,rc
	mov rb,a
	clr c
	rrc rb
	rrc ra
	clr c
	rrc rb
	rrc ra
	ret
_Samlpe_Adc endp
#line 91 "k:\55555555555555\test\saier-a600n-2260-usa4g-aal-bg95-ui-v1.0-6\ADC.c"
#pragma debug scope 1 1
#pragma debug struct_begin 42 "__intc0_bits"
#pragma debug field 21 8 0 1 "__emi" ;0,1
#pragma debug field 21 8 0 1 "__int0e" ;1,1
#pragma debug field 21 8 0 1 "__int1e" ;2,1
#pragma debug field 21 8 0 1 "__ade" ;3,1
#pragma debug field 21 8 0 1 "__int0f" ;4,1
#pragma debug field 21 8 0 1 "__int1f" ;5,1
#pragma debug field 21 8 0 1 "__adf" ;6,1
#pragma debug field 21 8 0 1 ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___intc0 "__intc0" 1
#pragma debug variable 8 1 ___sadol "__sadol" 1
#pragma debug variable 8 1 ___sadoh "__sadoh" 1
#pragma debug struct_begin 44 "__sadc0_bits"
#pragma debug field 21 8 0 1 "__sacs0" ;0,1
#pragma debug field 21 8 0 1 "__sacs1" ;1,1
#pragma debug field 21 8 0 1 "__sacs2" ;2,1
#pragma debug field 21 8 0 1 "__sacs3" ;3,1
#pragma debug field 21 8 0 1 "__adrfs" ;4,1
#pragma debug field 21 8 0 1 "__adcen" ;5,1
#pragma debug field 21 8 0 1 "__adbz" ;6,1
#pragma debug field 21 8 0 1 "__start" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___sadc0 "__sadc0" 1
#pragma debug struct_begin 46 "__sadc1_bits"
#pragma debug field 21 8 0 1 "__sacks0" ;0,1
#pragma debug field 21 8 0 1 "__sacks1" ;1,1
#pragma debug field 21 8 0 1 "__sacks2" ;2,1
#pragma debug field 21 8 0 1 "__savrs0" ;3,1
#pragma debug field 21 8 0 1 "__savrs1" ;4,1
#pragma debug field 21 8 0 1 "__sains0" ;5,1
#pragma debug field 21 8 0 1 "__sains1" ;6,1
#pragma debug field 21 8 0 1 "__sains2" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___sadc1 "__sadc1" 1
#pragma debug struct_begin 48 "__pcs0_bits"
#pragma debug field 21 8 0 1 "__pcs00" ;0,1
#pragma debug field 21 8 0 1 "__pcs01" ;1,1
#pragma debug field 21 8 0 1 "__pcs02" ;2,1
#pragma debug field 21 8 0 1 "__pcs03" ;3,1
#pragma debug field 21 8 0 1 "__pcs04" ;4,1
#pragma debug field 21 8 0 1 "__pcs05" ;5,1
#pragma debug field 21 8 0 1 "__pcs06" ;6,1
#pragma debug field 21 8 0 1 "__pcs07" ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___pcs0 "__pcs0" 1

; output external variables
extern _ADCVALV:byte

; 
; Generated by holtek-gcc v3.19, Tue Jul 26 12:07:02 2022
; Rebuild 718
; end of file
