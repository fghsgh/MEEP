iterate <name,instruction>, call,rst 28h, jump,call 50h
  iterate separator, ,_
    macro b#separator#name? address*
      instruction
      dw address
    end macro
  end iterate
end iterate

define ti? ti
namespace ti?

;TI-83 Plus Include File
;05/07/2007

;System Variable Equates
;------------------------------
?XSCLt?                     := 2
?YSCLt?                     := 3
?XMINt?                     := 0Ah
?XMAXt?                     := 0Bh
?YMINt?                     := 0Ch
?YMAXt?                     := 0Dh
?TMINt?                     := 0Eh
?TMAXt?                     := 0Fh
?THETMINt?                  := 10h
?THETMAXt?                  := 11h
?TBLMINt?                   := 1Ah
?PLOTSTARTt?                := 1Bh
?NMAXt?                     := 1Dh
?NMINt?                     := 1Fh
?TBLSTEPt?                  := 21h
?TSTEPt?                    := 22h
?THETSTEPt?                 := 23h
?DELTAXt?                   := 26h
?DELTAYt?                   := 27h
?XFACTt?                    := 28h
?YFACTt?                    := 29h
?FINNt?                     := 2Bh
?FINIt?                     := 2Ch
?FINPVt?                    := 2Dh
?FINPMTt?                   := 2Eh
?FINFVt?                    := 2Fh
?FINPYt?                    := 30h
?FINCYt?                    := 31h
?PLOTSTEPt?                 := 34h
?XRESt?                     := 36h

;Run indicators
;------------------------------------
?busyPause?                 := 10101010b
?busyNormal?                := 11110000b

;Banked Call Equates/Macros
;-----------------------------------------------
?rBR_CALL?                  := 28h
?BRT_JUMP0?                 := 50h



;Common Restart Routines
;------------------------------
?rOP1TOOP2?                 := 08h
?rFINDSYM?                  := 10h
?rPUSHREALO1?               := 18h
?rMOV9TOOP1?                := 20h
?rFPADD?                    := 30h

;Error Handler Equates/Macros
;-------------------------------------------
?APP_PUSH_ERRORH?           := 59h
?APP_POP_ERRORH?            := 5Ch



;Page 1Bh ROM Calls
;--------------------------------
?JErrorNo?                  := 4000h
?FontHook?                  := 4003h
?call_character_hook?       := 4006h                    ;calls character(localize) hook
?ldHLind?                   := 4009h                    ;l=a=(hl),h=(hl+1)
?CpHLDE?                    := 400Ch
?DivHLBy10?                 := 400Fh
?DivHLByA?                  := 4012h
?kdbScan?                   := 4015h
?GetCSC?                    := 4018h                    ;key board scan codes
?coorMon?                   := 401Bh                    ;
?Mon?                       := 401Eh                    ;system monitor, customized through the context vectors
?monForceKey?               := 4021h                    ;
?sendKPress?                := 4024h
?JForceCmdNoChar?           := 4027h
?JForceCmd?                 := 402Ah                    ;
?sysErrHandler?             := 402Dh                    ;loads error context? sp=(onSP)
?newContext?                := 4030h                    ;(kbdKey)=0, loads context, restores page in 4000h-7fffh
?newContext0?               := 4033h                    ;loads context
?_cxPutAway?                := 4036h                    ;
?cxPutAway2?                := 4039h                    ;same but also does a B_CALL CanAlphIns
?_cxPPutAway?               := 403Ch
?_cxSizeWind?               := 403Fh
?cxErrEP?                   := 4042h
?_cxMain?                   := 4045h
?monErrHand?                := 4048h                    ;installs errorhandler to start of ROM call, loads error context, jumps to mon
?AppInit?                   := 404Bh                    ;loads vector data at hl to cxMain and the rest of the vectors
?resetRam?                  := 404Eh
?lcd_busy?                  := 4051h                    ;wait till bit 1 of port 2 is set
?Min?                       := 4054h                    ;op1 = lowest number between op1 and op2
?Max?                       := 4057h                    ;op1 = highest number between op1 and op2 
?Trunc?                     := 4060h
?InvSub?                    := 4063h
?Times2?                    := 4066h
?Plus1?                     := 4069h                    ;op1=op1+1
?Minus1?                    := 406Ch
?FPSub?                     := 406Fh
?FPAdd?                     := 4072h
?DToR?                      := 4075h
?RToD?                      := 4078h
?Cube?                      := 407Bh
?TimesPt5?                  := 407Eh
?FPSquare?                  := 4081h
?FPMult?                    := 4084h                    ;op1=op1*op2
?LJRND?                     := 4087h                    ;adjusts op1 if 0s precede the actual number... rounding? when
?InvOP1SC?                  := 408Ah
?InvOP1S?                   := 408Dh
?InvOP2S?                   := 4090h
?frac?                      := 4093h
?fprecip?                   := 4096h
?fpdiv?                     := 4099h
?SqRoot?                    := 409Ch
?RndGuard?                  := 409Fh
?RnFx?                      := 40A2h
?int?                       := 40A5h
?Round?                     := 40A8h
?LnX?                       := 40ABh
?LogX?                      := 40AEh
?LJNORND?                   := 40B1h                    ;like _LJRND but no rounding
?EToX?                      := 40B4h
?TenX?                      := 40B7h
?SinCosRad?                 := 40BAh
?Sin?                       := 40BDh
?cos?                       := 40C0h
?Tan?                       := 40C3h
?SinHCosH?                  := 40C6h
?TanH?                      := 40C9h
?cosh?                      := 40CCh
?SinH?                      := 40CFh
?ACosRad?                   := 40D2h
?ATanRad?                   := 40D5h
?ATan2Rad?                  := 40D8h
?ASinRad?                   := 40DBh
?ACos?                      := 40DEh
?ATan?                      := 40E1h
?ASin?                      := 40E4h
?ATan2?                     := 40E7h
?ATanH?                     := 40EAh
?ASinH?                     := 40EDh
?ACosH?                     := 40F0h
?PtoR?                      := 40F3h
?RToP?                      := 40F6h
?HLTimes9?                  := 40F9h
?CkOP1Cplx?                 := 40FCh
?CkOP1Real?                 := 40FFh
?Angle?                     := 4102h
?COP1Set0?                  := 4105h
?CpOP4OP3?                  := 4108h
?Mov9OP2Cp?                 := 410Bh
?AbsO1O2Cp?                 := 410Eh
?cpop1op2?                  := 4111h
?OP3ToOP4?                  := 4114h
?OP1ToOP4?                  := 4117h
?OP2ToOP4?                  := 411Ah
?OP4ToOP2?                  := 411Dh
?OP1ToOP3?                  := 4123h
?OP5ToOP2?                  := 4126h
?OP5ToOP6?                  := 4129h
?OP5ToOP4?                  := 412Ch
?OP1ToOP2?                  := 412Fh
?OP6ToOP2?                  := 4132h
?OP6ToOP1?                  := 4135h
?OP4ToOP1?                  := 4138h
?OP5ToOP1?                  := 413Bh
?OP3ToOP1?                  := 413Eh
?OP6ToOP5?                  := 4141h
?OP4ToOP5?                  := 4144h
?OP3ToOP5?                  := 4147h
?OP2ToOP5?                  := 414Ah
?OP2ToOP6?                  := 414Dh
?OP1ToOP6?                  := 4150h
?OP1ToOP5?                  := 4153h
?OP2ToOP1?                  := 4156h
?Mov11B?                    := 4159h
?Mov10B?                    := 415Ch
?Mov9B?                     := 415Fh
?mov9B2?                    := 4162h                    ;points to _mov9B
?Mov8B?                     := 4165h
?Mov7B?                     := 4168h
?Mov7B2?                    := 416Bh                    ;same pointer as _Mov7B
?OP2ToOP3?                  := 416Eh
?OP4ToOP3?                  := 4171h
?OP5ToOP3?                  := 4174h
?OP4ToOP6?                  := 4177h
?Mov9ToOP1?                 := 417Ah
?Mov9OP1OP2?                := 417Dh
?Mov9ToOP2?                 := 4180h
?MovFrOP1?                  := 4183h
?OP4Set1?                   := 4186h
?OP3Set1?                   := 4189h
?OP2Set8?                   := 418Ch
?OP2Set5?                   := 418Fh
?OP2SetA?                   := 4192h
?OP2Set4?                   := 4195h
?OP2Set3?                   := 4198h
?OP1Set1?                   := 419Bh
?OP1Set4?                   := 419Eh
?OP1Set3?                   := 41A1h
?OP3Set2?                   := 41A4h
?OP1Set2?                   := 41A7h
?OP2Set2?                   := 41AAh
?OP2Set1?                   := 41ADh
?Zero16D?                   := 41B0h
?OP5Set0?                   := 41B3h
?OP4Set0?                   := 41B6h
?OP3Set0?                   := 41B9h
?OP2Set0?                   := 41BCh
?OP1Set0?                   := 41BFh
?OPSet0?                    := 41C2h                    ;hl = location to write floating point 0
?ZeroOP1?                   := 41C5h
?ZeroOP2?                   := 41C8h
?ZeroOP3?                   := 41CBh
?ZeroOP?                    := 41CEh
?ClrLp?                     := 41D1h
?ShRAcc?                    := 41D4h                    ;move high nibble in a to low nibble
?ShLAcc?                    := 41D7h                    ;move low nibble in a to high nibble
?ShR18?                     := 41DAh                    ;insert a 0 nibble at high nibble of (hl), shift 9 bytes 1 nibble to right
?SHR18A?                    := 41DDh                    ;insert low nibble in a at high nibble of (hl), shift 9 bytes 1 nibble to right
?SHR16?                     := 41E0h                    ;insert a 0 nibble at highnibble of (hl), shift 8 bytes 1 nibble to right
?SHR14?                     := 41E3h                    ;insert low nibble in a at high nibble of (hl), shift 7 bytes 1 nibble to right
?SHL16?                     := 41E6h                    ;insert nibble of 0 in low nibble of (hl), shift 8 bytes (before and including (hl)) to the left 1 nibble
?SHL14?                     := 41E9h                    ;insert low nibble of a in low nibble of (hl), shift 7 bytes (before and including (hl)) to the left 1 nibble
?SRDO1?                     := 41ECh
?SHRDRND?                   := 41EFh
?MANTPA?                    := 41F2h                    ;adds the value of a to hl which points to the end of the bcd 7 bytes long
?ADDPROP?                   := 41F5h                    ;adds the value of a to hl which points to the end of the bcd (b bytes long)
?ADDPROPLP?                 := 41F8h                    ;adds the value of a and carry to hl which points to the end of the bcd (b bytes long)
?ADD16D?                    := 41FBh                    ;adds the bcd numbers at (hl-7) and (de-7)
?ADD14D?                    := 41FEh                    ;adds the bcd numbers at (hl-6) and (de-6)
?SUB16D?                    := 4201h                    ;subtracts bcd numbers at (hl-7) and (de-7)
?SUB14D?                    := 4204h                    ;subtracts bcd numbers at (hl-6) and (de-6)
?OP2ExOP6?                  := 4207h
?OP5ExOP6?                  := 420Ah
?OP1ExOP5?                  := 420Dh
?OP1ExOP6?                  := 4210h
?OP2ExOP4?                  := 4213h
?OP2ExOP5?                  := 4216h
?OP1ExOP3?                  := 4219h
?OP1ExOP4?                  := 421Ch
?OP1ExOP2?                  := 421Fh
?ExLp?                      := 4222h
?CkOP1C0?                   := 4225h
?CkOP1FP0?                  := 4228h
?CkOP2FP0?                  := 422Bh
?PosNo0Int?                 := 422Eh
?CKPosInt?                  := 4231h
?CKInt?                     := 4234h
?CKOdd?                     := 4237h
?CKOP1M?                    := 423Ah
?GETCONOP1?                 := 423Dh                    ;a=0 opX=57.29577951308232 (1 radian in degrees)
?GETCONOP2?                 := 4240h                    ;a=1 opX=1.570796326794897 (90 deg = pi/2)
                            ;a=2 opX=.7853981633974483 (45 deg = pi/4)
                            ;a=3 opX=.4342944819032518 (log e)
                            ;a=4 opX=3.141592653589800 (pi)
                            ;a=5 opX=.0174532925199433 (pi/180 = 1 degree in radians)
                            ;a=6 opX=2.302585092994046 (ln 10)
?PIDIV2?                    := 4243h                    ;not code, but a pointer to:                            .db 80h,15h,70h,79h,63h,26h,79h,48h,97h
?PIDIV4?                    := 4246h                    ;                                                                                                               .db 7fh,78h,53h,98h,16h,33h,97h,44h,83h
?PItimes2?                  := 4249h                    ;not code, but a pointer to a 2*pi in non-OP format (no exponent byte)
?PI?                        := 424Ch                    ;not code, but a pointer to a pi in non-OP format (no exponent byte)
?ExpToHex?                  := 424Fh
?OP1ExpToDec?               := 4252h
?ckop2pos?                  := 4255h
?CkOP1Pos?                  := 4258h
?ClrOP2S?                   := 425Bh
?ClrOP1S?                   := 425Eh
?FDIV100?                   := 4261h                    ;op1=op1/100
?FDIV10?                    := 4264h                    ;op1=op1/10
?DecO1Exp?                  := 4267h                    ;decrease exponent by 1, this can go from 0 to FF
?INCO1EXP?                  := 426Ah                    ;op1=op1*10
?INCEXP?                    := 426Dh                    ;hl points to the floating point's exponent to be multiplied by 10
?CkValidNum?                := 4270h
?GETEXP?                    := 4273h                    ;a=OP1's exponent, carry set if negative exponent, Z if e0
?HTimesL?                   := 4276h
?EOP1NotReal?               := 4279h
?ThetaName?                 := 427Ch
?RName?                     := 427Fh
?REGEQNAME?                 := 4282h
?RECURNNAME?                := 4285h
?XName?                     := 4288h
?YName?                     := 428Bh
?TName?                     := 428Eh
?REALNAME?                  := 4291h
?SETesTOfps?                := 4294h                    ;moves the word at fps to es
?markTableDirty?            := 4297h                    ;looks up table variable and marks VAT entry as "dirty" or selected
?OP1MOP2EXP?                := 429Ah                    ;op1's exponent = op1's expoent - op2's exponent
?OP1EXPMinusE?              := 429Dh                    ;a=(op1+1)-e
?CHKERRBREAK?               := 42A0h
?isA2ByteTok?               := 42A3h
?GETLASTENTRY?              := 42A6h
?GETLASTENTRYPTR?           := 42A9h
?REGCLRCHNG?                := 42ACh
?RESETWINTOP?               := 42AFh                    ;takes into account grfsplitoverride and grfsplit flags
?SetYUp?                    := 42B2h                    ;loads 7 to port 10... what does this do?
?SetXUp?                    := 42B5h                    ;loads 5 to port 10...
?ISO1NONTLSTorPROG?         := 42B8h                    ;checks if op1 contains a list, program, group, or appvar obj name
?ISO1NONTEMPLST?            := 42BBh                    ;checks if op1 contains a list (why would op1+1 contain 01, or 0d for a var name?)
?IS_A_LSTorCLST?            := 42BEh                    ;checks if a = 1 or 0Dh
?CHK_HL_999?                := 42C1h                    ;returns nc if less than 999, throws invalid dim error if greater than or equal to 999
?equ_or_newequ?             := 42C4h
?errd_op1notpos?            := 42C7h
?ErrD_OP1Not_R?             := 42CAh
?ErrD_OP1NotPosInt?         := 42CDh
?ErrD_OP1_LE_0?             := 42D0h
?ErrD_OP1_0?                := 42D3h
?FINDSYM_GET_SIZE?          := 42D6h                    ;like findsym, but on output hl is the size of the variable
?STO_STATVAR?               := 42D9h
?Rcl_StatVar?               := 42DCh
?CkOP2Real?                 := 42DFh
?GET_X_INDIRECT?            := 42E2h                    ;whatever this is, it uses the imathptrX locations
?MemChk?                    := 42E5h
?CMPPRGNAMLEN1?             := 42E8h                    ;gets variable name length from HL
?CMPPRGNAMLEN?              := 42EBh                    ;gets variable name length from OP1
?FINDPROGSYM?               := 42EEh                    ;find the program whose name is in op1 (see chkfindsym in SDK)
?ChkFindSym?                := 42F1h
?FindSym?                   := 42F4h
?InsertMem?                 := 42F7h
?INSERTMEMA?                := 42FAh                    ;not sure how this differs from insertmem
?EnoughMem?                 := 42FDh
?CMPMEMNEED?                := 4300h
?CREATEPVAR4?               := 4303h
?CREATEPVAR3?               := 4306h
?CREATEVAR3?                := 4309h
?CreateCplx?                := 430Ch
?CreateReal?                := 430Fh
?CreateTempRList?           := 4312h
?CreateRList?               := 4315h
?CREATETCLIST?              := 4318h
?CreateCList?               := 431Bh
?CreateTempRMat?            := 431Eh
?CreateRMat?                := 4321h
?CreateTempString?          := 4324h
?CreateStrng?               := 4327h
?Create0Equ?                := 432Ah
?CreateTempEqu?             := 432Dh
?CreateEqu?                 := 4330h
?CreatePict?                := 4333h
?CreateGDB?                 := 4336h
?CreateProg?                := 4339h
?CHKDEL?                    := 433Ch
?CHKDELA?                   := 433Fh
?ADJPARSER?                 := 4342h
?ADJMATH?                   := 4345h
?ADJM7?                     := 4348h
?DELMEMA?                   := 434Bh
?GET_FORM_NUM?              := 434Eh
?DelVar?                    := 4351h
?DELVARIO?                  := 4354h
?DelMem?                    := 4357h
?DELVAR3D?                  := 435Ah
?DELVAR3C?                  := 435Dh
?DELVAR3DC?                 := 4360h                    ;may be incorrect
?IsFixedName?               := 4363h
?DelVarEntry?               := 4366h
?DataSizeA?                 := 4369h
?DataSize?                  := 436Ch
?POPMCPLXO1?                := 436Fh
?POPMCPLX?                  := 4372h
?MOVCPLX?                   := 4375h
?popOP5?                    := 4378h
?popOP3?                    := 437Bh
?popOP1?                    := 437Eh
?PopRealO6?                 := 4381h
?PopRealO5?                 := 4384h
?PopRealO4?                 := 4387h
?PopRealO3?                 := 438Ah
?PopRealO2?                 := 438Dh
?PopRealO1?                 := 4390h
?PopReal?                   := 4393h
?FPOPCPLX?                  := 4396h
?FPOPREAL?                  := 4399h
?FPOPFPS?                   := 439Ch
?DeallocFPS?                := 439Fh
?DeallocFPS1?               := 43A2h
?AllocFPS?                  := 43A5h
?AllocFPS1?                 := 43A8h
?PushRealO6?                := 43ABh
?PushRealO5?                := 43AEh
?PushRealO4?                := 43B1h
?PushRealO3?                := 43B4h
?PushRealO2?                := 43B7h
?PushRealO1?                := 43BAh
?PushReal?                  := 43BDh
?PushOP5?                   := 43C0h
?PushOP3?                   := 43C3h
?PUSHMCPLXO3?               := 43C6h
?PushOP1?                   := 43C9h
?PUSHMCPLXO1?               := 43CCh
?PUSHMCPLX?                 := 43CFh
?ExMCplxO1?                 := 43D2h
?Exch9?                     := 43D5h
?CpyTo1FPS11?               := 43D8h
?CpyTo2FPS5?                := 43DBh
?CpyTo1FPS5?                := 43DEh
?CpyTo2FPS6?                := 43E1h
?CpyTo1FPS6?                := 43E4h
?CpyTo2FPS7?                := 43E7h
?CpyTo1FPS7?                := 43EAh
?CpyTo1FPS8?                := 43EDh
?CpyTo2FPS8?                := 43F0h
?CpyTo1FPS10?               := 43F3h
?CpyTo1FPS9?                := 43F6h
?CpyTo2FPS4?                := 43F9h
?CpyTo6FPS3?                := 43FCh
?CpyTo6FPS2?                := 43FFh
?CpyTo2FPS3?                := 4402h
?CPYCTO1FPS3?               := 4405h
?CpyTo1FPS3?                := 4408h
?CPYFPS3?                   := 440Bh
?CpyTo1FPS4?                := 440Eh
?CpyTo3FPS2?                := 4411h
?CpyTo5FPST?                := 4414h
?CpyTo6FPST?                := 4417h
?CpyTo4FPST?                := 441Ah
?CpyTo3FPST?                := 441Dh
?CpyTo2FPST?                := 4420h
?CpyTo1FPST?                := 4423h
?CPYFPST?                   := 4426h
?CpyStack?                  := 4429h
?CpyTo3FPS1?                := 442Ch
?CpyTo2FPS1?                := 442Fh
?CpyTo1FPS1?                := 4432h
?CPYFPS1?                   := 4435h
?CpyTo2FPS2?                := 4438h
?CpyTo1FPS2?                := 443Bh
?CPYFPS2?                   := 443Eh
?CpyO3ToFPST?               := 4441h
?CpyO2ToFPST?               := 4444h
?CpyO6ToFPST?               := 4447h
?CpyO1ToFPST?               := 444Ah
?CpyToFPST?                 := 444Dh
?CpyToStack?                := 4450h
?CpyO3ToFPS1?               := 4453h
?CpyO5ToFPS1?               := 4456h
?CpyO2ToFPS1?               := 4459h
?CpyO1ToFPS1?               := 445Ch
?CpyToFPS1?                 := 445Fh
?CpyO2ToFPS2?               := 4462h
?CpyO3ToFPS2?               := 4465h
?CpyO6ToFPS2?               := 4468h
?CpyO1ToFPS2?               := 446Bh
?CpyToFPS2?                 := 446Eh
?CpyO5ToFPS3?               := 4471h
?CpyO2ToFPS3?               := 4474h
?CpyO1ToFPS3?               := 4477h
?CpyToFPS3?                 := 447Ah
?CpyO1ToFPS6?               := 447Dh
?CpyO1ToFPS7?               := 4480h
?CpyO1ToFPS5?               := 4483h
?CpyO2ToFPS4?               := 4486h
?CpyO1ToFPS4?               := 4489h
?ErrNotEnoughMem?           := 448Ch                    ;only if not HL bytes free
?FPSMINUS9?                 := 448Fh
?HLMINUS9?                  := 4492h
?ErrOverflow?               := 4495h
?ErrDivBy0?                 := 4498h
?ErrSingularMat?            := 449Bh
?ErrDomain?                 := 449Eh
?ErrIncrement?              := 44A1h
?ErrNon_Real?               := 44A4h
?ErrSyntax?                 := 44A7h
?ErrDataType?               := 44AAh
?ErrArgument?               := 44ADh
?ErrDimMismatch?            := 44B0h
?ErrDimension?              := 44B3h
?ErrUndefined?              := 44B6h
?ErrMemory?                 := 44B9h
?ErrInvalid?                := 44BCh
?ErrBreak?                  := 44BFh
?ErrStat?                   := 44C2h
?ErrSignChange?             := 44C5h
?ErrIterations?             := 44C8h
?ErrBadGuess?               := 44CBh
?ErrTolTooSmall?            := 44CEh
?ErrStatPlot?               := 44D1h
?ErrLinkXmit?               := 44D4h
?JError?                    := 44D7h
?noErrorEntry?              := 44DAh
?pushErrorHandleR?          := 44DDh
?popErrorHandleR?           := 44E0h
?strcopy?                   := 44E3h
?strCat?                    := 44E6h
?isInSet?                   := 44E9h
?sDone?                     := 44ECh                    ;this should actually be called _SetEquToOP1
?serrort?                   := 44EFh
?sNameEq?                   := 44F2h
?sUnderScr?                 := 44F5h
?sFAIL?                     := 44F8h
?sName?                     := 44FBh
?sOK?                       := 44FEh
?PutMap?                    := 4501h
?PutC?                      := 4504h
?DispHL?                    := 4507h
?PutS?                      := 450Ah
?putpsb?                    := 450Dh
?PutPS?                     := 4510h
?wputps?                    := 4513h
?putbuf?                    := 4516h
?putbuf1?                   := 4519h
?wputc?                     := 451Ch
?wputs?                     := 451Fh
?wputsEOL?                  := 4522h                    ;displays string in HL in big font, and uses ... if too long
?wdispEOL?                  := 4525h
?whomeup?                   := 4528h
?setNumWindow?              := 452Bh                    ;based on current cursor position, sets winleft and similar (for input prompts)
?newline?                   := 452Eh
?moveDown?                  := 4531h
?scrollUp?                  := 4534h
?shrinkWindow?              := 4537h
?moveUp?                    := 453Ah
?scrollDown?                := 453Dh
?ClrLCDFull?                := 4540h
?ClrLCD?                    := 4543h
?ClrScrnFull?               := 4546h
?ClrScrn?                   := 4549h
?ClrTxtShd?                 := 454Ch
?ClrWindow?                 := 454Fh
?EraseEOL?                  := 4552h
?EraseEOW?                  := 4555h
?HomeUp?                    := 4558h
?getcurloc?                 := 455Bh
?VPutMap?                   := 455Eh
?VPutS?                     := 4561h
?VPutSN?                    := 4564h
?vputsnG?                   := 4567h
?vputsnT?                   := 456Ah
?RunIndicOn?                := 456Dh
?RunIndicOff?               := 4570h
?saveCmdShadow?             := 4573h
?saveShadow?                := 4576h
?rstrShadow?                := 4579h
?rstrpartial?               := 457Ch
?rstrCurRow?                := 457Fh
?rstrUnderMenu?             := 4582h
?rstrbotrow?                := 4585h
?saveTR?                    := 4588h                    ;save top right corner of LCD so 2nd arrow can be displayed, indicinuse flag must be set
?restoreTR?                 := 458Bh                    ;restore top right corner of LCD destroyed by an arrow. indicinuse flag must be set
?GetKeyPress?               := 458Eh
?GetTokLen?                 := 4591h                    ;input: hl=pointer to token. output: a=lenght of string, hl=pointer to string on page 1
?GET_TOK_STRNG?             := 4594h                    ;input: hl=pointer to token. output: op3=string of the token, a=length of string
?GETTOKSTRING?              := 4597h                    ;input: DE=token. output: hl=pointer to the string on page 1
?PUTBPATBUF2?               := 459Ah
?PUTBPATBUF?                := 459Dh
?putbPAT?                   := 45A0h
?putcCheckScrolL?           := 45A3h
?DispEOL?                   := 45A6h
?fdispEOL?                  := 45A9h
?MAKEROWCMD?                := 45ACh
?TOTOSTRP?                  := 45AFh
?SETVARNAME?                := 45B2h
?DispDone?                  := 45B5h
?finishoutput?              := 45B8h
?curBlink?                  := 45BBh
?CursorOff?                 := 45BEh
?hideCursor?                := 45C1h
?CursorOn?                  := 45C4h
?showCursor?                := 45C7h
?KeyToString?               := 45CAh
?PULLDOWNCHK?               := 45CDh                    ;something wrong here
?MenuCatCommon?             := 45D0h
?ZIfCatalog?                := 45D3h
?ZIfMatrixMenu?             := 45D6h                    ;_loadCurCat
?LoadMenuNum?               := 45D9h
?LoadMenuNumL?              := 45DCh
?MenCatRet?                 := 45DFh                    ;restores display as though a menu were just cleared (restores some flags too)
?MenuSwitchContext?         := 45E2h                    ;switches to context in A, calls menu hook with A=3, set 5,(iy+16h) for some sort of override to not make switch
?MenuEdKey?                 := 45E5h
?BackUpGraphSettings?       := 45E8h
?notalphnum?                := 45EBh
?SaveSavedFlags?            := 45EEh
?SetMenuFlags?              := 45F1h
?RstrSomeFlags?             := 45F4h
?RstrOScreen?               := 45F7h                    ;restores saveSScreen to the display
?SaveOScreen?               := 45FAh                    ;stores display in saveSScreen
?dispListName?              := 45FDh                    ;_SeeIfErrorCx
?PrevContext?               := 4600h
?CompareContext?            := 4603h
?AdrMRow?                   := 4606h
?AdrMEle?                   := 4609h
?GETMATOP1A?                := 460Ch
?GETM1TOOP1?                := 460Fh
?GETM1TOP1A?                := 4612h
?GetMToOP1?                 := 4615h
?PUTTOM1A?                  := 4618h
?PUTTOMA1?                  := 461Bh
?PutToMat?                  := 461Eh
?MAT_EL_DIV?                := 4621h
?CMATFUN?                   := 4624h
?ROWECH_POLY?               := 4627h
?ROWECHELON?                := 462Ah
?AdrLEle?                   := 462Dh
?GETL1TOOP1?                := 4630h
?GETL1TOP1A?                := 4633h
?GetLToOP1?                 := 4636h
?GETL1TOOP2?                := 4639h
?GETL1TOP2A?                := 463Ch
?GETL2TOP1A?                := 463Fh
?PUTTOLA1?                  := 4642h
?PutToL?                    := 4645h
?MAXMINLST?                 := 4648h
?LLOW?                      := 464Bh
?LHIGH?                     := 464Eh
?LSUM?                      := 4651h
?CUMSUM?                    := 4654h
?ToFrac?                    := 4657h
?SEQSET?                    := 465Ah
?SEQSOLVE?                  := 465Dh
?CMP_NUM_INIT?              := 4660h
?BinOPExec?                 := 4663h
?EXMEAN1?                   := 4666h
?SET2MVLPTRS?               := 4669h
?SETMAT1?                   := 466Ch
?CREATETLIST?               := 466Fh
?UnOPExec?                  := 4672h
?ThreeExec?                 := 4675h
?RESTOREERRNO?              := 4678h
?FourExec?                  := 467Bh
?FiveExec?                  := 467Eh
?CPYTO2ES1?                 := 4681h
?CPYTO6ES1?                 := 4684h
?CPYTO1ES1?                 := 4687h
?CPYTO3ES1?                 := 468Ah
?CPYTO3ES2?                 := 468Dh
?CPYTO2ES2?                 := 4690h
?CPYTO1ES2?                 := 4693h
?CPYTO2ES3?                 := 4696h
?CPYTO1ES3?                 := 4699h
?CPYTO3ES4?                 := 469Ch
?CPYTO6ES3?                 := 469Fh
?CPYTO2ES4?                 := 46A2h
?CPYTO1ES4?                 := 46A5h
?CPYTO2ES5?                 := 46A8h
?CPYTO1ES5?                 := 46ABh
?CPYTO4EST?                 := 46AEh
?CPYTO2EST?                 := 46B1h
?CPYTO1EST?                 := 46B4h
?CPYTO2ES6?                 := 46B7h
?CPYTO1ES6?                 := 46BAh
?CPYTO2ES7?                 := 46BDh
?CPYTO1ES7?                 := 46C0h
?CPYTO2ES8?                 := 46C3h
?CPYTO1ES8?                 := 46C6h
?CPYTO1ES9?                 := 46C9h
?CPYTO2ES9?                 := 46CCh
?CPYTO2ES10?                := 46CFh
?CPYTO1ES10?                := 46D2h
?CPYTO2ES11?                := 46D5h
?CPYTO1ES11?                := 46D8h
?CPYTO2ES12?                := 46DBh
?CPYTO1ES12?                := 46DEh
?CPYTO2ES13?                := 46E1h
?CPYTO1ES13?                := 46E4h
?CPYTO1ES14?                := 46E7h
?CPYTO1ES16?                := 46EAh
?CPYTO1ES17?                := 46EDh
?CPYTO1ES18?                := 46F0h
?CPYTO1ES15?                := 46F3h
?CPYTO2ES15?                := 46F6h
?CPYO1TOEST?                := 46F9h
?CPYO1TOES1?                := 46FCh
?CPYO6TOES1?                := 46FFh
?CPYO6TOES3?                := 4702h
?CPYO1TOES2?                := 4705h
?CPYO2TOES2?                := 4708h
?CPYO1TOES3?                := 470Bh
?CPYO1TOES4?                := 470Eh
?CPYO1TOES5?                := 4711h
?CPYO1TOES6?                := 4714h
?CPYO1TOES7?                := 4717h
?CPYO2TOES4?                := 471Ah
?CPYO2TOES5?                := 471Dh
?CPYO2TOES6?                := 4720h
?CPYO2TOES7?                := 4723h
?CPYO2TOES8?                := 4726h
?CPYO2TOES9?                := 4729h
?CPYO1TOES8?                := 472Ch
?CPYO1TOES9?                := 472Fh
?CPYO1TOES10?               := 4732h
?CPYO1TOES11?               := 4735h
?CPYO1TOES12?               := 4738h
?CPYO1TOES13?               := 473Bh
?CPYO1TOES14?               := 473Eh
?CPYO1TOES15?               := 4741h
?EVALF3A?                   := 4744h
?GetK?                      := 4747h                    ;?
?setTitle?                  := 474Ah
?dispVarVal?                := 474Dh
?RecallEd?                  := 4750h                    ;_setupBuffer
?createNumEditBuf?          := 4753h
?ProcessBufKeys?            := 4756h                    ;may be default key processing like [CLEAR], etc. especially for an edit buffer.
?CallCommon?                := 4759h
?CommonKeys?                := 475Ch
?Leftmore?                  := 475Fh
?fDel?                      := 4762h
?fClear?                    := 4765h
?finsDisp?                  := 4768h                    ;Michael says _FinsDisp02 := 4768h (something's not right)
?FinsDisp02?                := 476Bh                    ;_setIndicator
?closeeditbufnor?           := 476Eh
?releaseBuffer?             := 4771h
?varnameToOP1hl?            := 4774h
?nameToOP1?                 := 4777h
?numPPutAway?               := 477Ah
?numRedisp?                 := 477Dh
?numError02?                := 4780h
?Load_SFont?                := 4783h
?SFont_Len?                 := 4786h
?InitNumVec?                := 4789h                    ;inits window settings/table setup/finance solver context (dialog-like)
?SetXXOP1?                  := 478Ch
?SetXXOP2?                  := 478Fh
?SetXXXXOP2?                := 4792h
?UCLineS?                   := 4795h
?CLine?                     := 4798h
?CLineS?                    := 479Bh
?XRootY?                    := 479Eh
?YToX?                      := 47A1h
?ZmStats?                   := 47A4h
?POINT_STAT_HLP?            := 47A7h
?DRAWSPLOT?                 := 47AAh
?INITNEWTRACEP?             := 47ADh                    ;A is input here, goes to (8E63h)
?SPLOTCOORD?                := 47B0h
?SPLOTRIGHT?                := 47B3h
?SPLOTLEFT?                 := 47B6h
?CMPBOXINFO?                := 47B9h
?NEXTPLOT?                  := 47BCh
?PREVPLOT?                  := 47BFh
?CLRPREVPLOT?               := 47C2h
?PUT_INDEX_LST?             := 47C5h
?GET_INDEX_LST?             := 47C8h
?HEAP_SORT?                 := 47CBh
?StoGDB2?                   := 47CEh
?RclGDB2?                   := 47D1h
?CircCmd?                   := 47D4h
?GrphCirc?                  := 47D7h
?Mov18B?                    := 47DAh
?DarkLine?                  := 47DDh
?ILine?                     := 47E0h
?IPoint?                    := 47E3h
?XYRNDBOTH?                 := 47E6h
?XYRND?                     := 47E9h
?CheckTOP?                  := 47ECh
?CheckXY?                   := 47EFh
?DarkPnt?                   := 47F2h
?CPointS?                   := 47F5h
?WTOV?                      := 47F8h
?VtoWHLDE?                  := 47FBh
?Xitof?                     := 47FEh
?YftoI?                     := 4801h
?XftoI?                     := 4804h
?TraceOff?                  := 4807h
?GrRedisp?                  := 480Ah
?GDISPTOKEN?                := 480Dh
?GRDECODA?                  := 4810h
?LABCOOR?                   := 4813h                    ;draws labels with _GRLABELS and X/Y/whatever coordinates, including stat plot stuff
?COORDISP?                  := 4816h                    ;draws X and Y coordinates (or R and theta if PolarGC)
?TMPEQUNOSRC?               := 4819h
?GRLABELS?                  := 481Ch
?YPIXSET?                   := 481Fh
?XPIXSET?                   := 4822h
?COPYRNG?                   := 4825h
?VALCUR?                    := 4828h                    ;just sets/resets three flags, enables graph cursor
?GRPUTAWAY?                 := 482Bh
?RSTGFLAGS?                 := 482Eh
?GRReset?                   := 4831h
?XYCENT?                    := 4834h
?ZOOMXYCMD?                 := 4837h
?CPTDELY?                   := 483Ah
?CPTDELX?                   := 483Dh
?SetFuncM?                  := 4840h
?SetSeqM?                   := 4843h
?SetPolM?                   := 4846h
?SetParM?                   := 4849h
?ZmInt?                     := 484Ch
?ZmDecml?                   := 484Fh
?ZmPrev?                    := 4852h
?ZmUsr?                     := 4855h
?SETUZM?                    := 4858h
?ZmFit?                     := 485Bh
?ZmSquare?                  := 485Eh
?ZmTrig?                    := 4861h
?SetXMinMax?                := 4864h
?ZooDefault?                := 4867h
?GrBufCpy?                  := 486Ah
?DRAWSPLITLINE?             := 486Dh
?RestoreDisp?               := 4870h
?FNDDB?                     := 4873h
?AllEq?                     := 4876h
?fndallseleq?               := 4879h
?NEXTEQ?                    := 487Ch
?PREVEQ?                    := 487Fh
?BLINKGCUR?                 := 4882h
?NBCURSOR?                  := 4885h
?STATMARK?                  := 4888h
?CHKTEXTCURS?               := 488Bh
?Regraph?                   := 488Eh
?DOREFFLAGS02?              := 4891h                    ;something wrong here
?INITNSEQ?                  := 4894h
?YRES?                      := 4897h                    ;_PLOTPTXY2
?Ceiling?                   := 489Ah                    ;ceil(OP1)
?PutXY?                     := 489Dh                    ;draws X and Y coordinates (regardless of PolarGC)
?PUTEQUNO?                  := 48A0h
?PDspGrph?                  := 48A3h
?HorizCmd?                  := 48A6h
?VertCmd?                   := 48A9h
?LineCmd?                   := 48ACh
?UnLineCmd?                 := 48AFh
?PointCmd?                  := 48B2h
?PixelTest?                 := 48B5h
?PixelCmd?                  := 48B8h
?TanLnF?                    := 48BBh
?DRAWCMD_INIT?              := 48BEh
?DrawCmd?                   := 48C1h
?SHADECMD?                  := 48C4h
?InvCmd?                    := 48C7h
?STATSHADE?                 := 48CAh
?dspmattable?               := 48CDh
?dsplsts?                   := 48D0h
?closeEditBuf?              := 48D3h
?parseEditBuf?              := 48D6h
?putsm?                     := 48D9h
?DspCurTbl?                 := 48DCh
?DSPGRTBL?                  := 48DFh
?zeroTemplate?              := 48E2h
?settblrefs?                := 48E5h
?dispTblBot?                := 48E8h
?DispTblTop?                := 48EBh
?dispTblbody?               := 48EEh
?VPUTBLANK?                 := 48F1h
?TBLTRACE?                  := 48F4h
?dispListNameY?             := 48F7h
?CurNameLength?             := 48FAh
?NameToBuf?                 := 48FDh
?jpromptcursor?             := 4900h
?BufLeft?                   := 4903h
?BufRight?                  := 4906h
?bufInsert?                 := 4909h
?bufQueueChar?              := 490Ch
?BufReplace?                := 490Fh
?BufDelete?                 := 4912h
?BUFPEEK?                   := 4915h
?BUFPEEK1?                  := 4918h
?BUFPEEK2?                  := 491Bh
?BUFPEEK3?                  := 491Eh
?BufToBtm?                  := 4921h
?setupEditEqu?              := 4924h
?BufToTop?                  := 4927h
?isEditFull?                := 492Ah
?IsEditEmpty?               := 492Dh
?IsAtTop?                   := 4930h
?IsAtBtm?                   := 4933h
?BufClear?                  := 4936h
?JcursorFirst?              := 4939h
?JcursorLast?               := 493Ch
?CursorLeft?                := 493Fh
?cursorRight?               := 4942h
?cursorUp?                  := 4945h
?CursorDown?                := 4948h
?cursorToOffset?            := 494Bh
?InsDisp?                   := 494Eh
?FDISPBOL1?                 := 4951h
?FDISPBOL?                  := 4954h
?DispEOW?                   := 4957h
?DispHead?                  := 495Ah
?DispTail?                  := 495Dh
?PutTokString?              := 4960h
?setupEditCmd?              := 4963h
?setEmptyEditEqu?           := 4966h
?SetEmptyEditPtr?           := 4969h
?CloseEditEqu?              := 496Ch
?GetPrevTok?                := 496Fh
?getkey?                    := 4972h
?canIndic?                  := 4975h
?LCD_DRIVERON?              := 4978h 
?DFMIN2?                    := 497Bh
?formDisp?                  := 497Eh                    ;this is directly what the OS calls on the homescreen to display a result
?formMatrix?                := 4981h
?wscrollLeft?               := 4984h
?wscrollUp?                 := 4987h
?wscrollDown?               := 498Ah
?wscrollRight?              := 498Dh
?FormEReal?                 := 4990h
?formERealTOK?              := 4993h
?FormDCplx?                 := 4996h
?FormReal?                  := 4999h
?formScrollUp?              := 499Ch
?setwinabove?               := 499Fh
?disarmScroll?              := 49A2h
?OP1toEdit?                 := 49A5h
?MinToEdit?                 := 49A8h
?rclVarToEdit?              := 49ABh
?rclVarToEditPtR?           := 49AEh
?RCLENTRYTOEDIT?            := 49B1h
?rclToQueue?                := 49B4h                    ;recalls bytes at OP1 into edit buffer
?FORMTOTOK?                 := 49B7h
?DISP_INTERVAL?             := 49BAh
?DisplstName?               := 49BDh
?dispSLstNameHL?            := 49C0h
?EditEqu?                   := 49C3h
?closeEquField?             := 49C6h
?AutoSelect?                := 49C9h
?DISPYEOS?                  := 49CCh
?dispNumEOS?                := 49CFh
?setupdispeq?               := 49D2h
?DispForward?               := 49D5h
?DispYPrompt2?              := 49D8h
?stringwidth?               := 49DBh
?dispErrorScreen?           := 49DEh                    ;displays top row of error screen (error message)
?POPCX?                     := 49E1h                    ;moves 14 bytes at cxPrev to cxMain, 15th byte goes to replace appflags
?loadnoeentry?              := 49E4h
?SaveScreen?                := 49E7h
?RETSCREEN?                 := 49EAh
?RetScreenErr?              := 49EDh
?CheckSplitFlag?            := 49F0h
?SolveRedisp?               := 49F3h
?SolveDisp?                 := 49F6h
?itemName?                  := 49F9h
?SetNorm_Vals?              := 49FCh
?SetYOffset?                := 49FFh                    ;sets up YOffset and next 4 bytes (possibly specialized for the table editor)
?ConvKeyToTok?              := 4A02h
?ConvFCKeyToTok?            := 4A05h
?ConvFEKeyToTok?            := 4A08h
?TokToKey?                  := 4A0Bh
?SendSkipExitPacket?        := 4A0Eh
?GETVARCMD?                 := 4A11h
?SendVarCmd?                := 4A14h
?SendScreenshot?            := 4A17h
?keyscnlnk?                 := 4A1Ah
?DeselectAllVars?           := 4A1Dh
?DelRes?                    := 4A20h
?ConvLcToLr?                := 4A23h
?RedimMat?                  := 4A26h
?IncLstSize?                := 4A29h
?InsertList?                := 4A2Ch
?dellistel?                 := 4A2Fh
?EditProg?                  := 4A32h
?CloseProg?                 := 4A35h
?ClrGraphRef?               := 4A38h
?FixTempCnt?                := 4A3Bh
?SAVEDATA?                  := 4A3Eh
?RESTOREDATA?               := 4A41h
?FindAlphaUp?               := 4A44h
?FindAlphaDn?               := 4A47h
?CmpSyms?                   := 4A4Ah
?CREATETEMP?                := 4A4Dh
?CleanAll?                  := 4A50h
?MoveToNextSym?             := 4A53h                    ;input: hl=pointer to type byte of VAT entry. output: hl = pointer to next entry's type byte
?ConvLrToLc?                := 4A56h
?TblScreenDn?               := 4A59h                    ;something is not right here
?TblScreenUp?               := 4A5Ch
?SCREENUP?                  := 4A5Fh
?ScreenUpDown?              := 4A62h
?ZifRclHandler?             := 4A65h
?zifrclkapp?                := 4A68h
?rclkeyRtn?                 := 4A6Bh
?RCLKEY?                    := 4A6Bh
?RCLREGEQ_CALL?             := 4A6Eh
?RCLREGEQ?                  := 4A71h
?initNamePrompt?            := 4A74h
?NamePrompt2?               := 4A77h
?CATALOGCHK?                := 4A7Ah
?clrTR?                     := 4A7Dh
?QUAD?                      := 4A80h
?GRAPHQUAD?                 := 4A83h
?BC2NOREAL?                 := 4A86h
?ErrNonReal_FPST_FPS1?      := 4A89h
?ErrNonReal?                := 4A8Ch                    ;ERR:DATA TYPE if top B numers from FPS are non-real
?WRITE_TEXT?                := 4A8Fh
?FORSEQINIT?                := 4A92h
?GRPHPARS?                  := 4A95h
?PLOTPARS?                  := 4A98h
?ParseInp?                  := 4A9Bh
?PARSEOFF?                  := 4A9Eh
?PARSESCAN?                 := 4AA1h
?GETPARSE?                  := 4AA4h
?SAVEPARSE?                 := 4AA7h
?InitPFlgs?                 := 4AAAh
?CKENDLINERR?               := 4AADh
?OP2Set60?                  := 4AB0h
?GETSTATPTR?                := 4AB3h
?CMP_STATPTR?               := 4AB6h
?VARSYSADR?                 := 4AB9h
?StoSysTok?                 := 4ABCh
?StoAns?                    := 4ABFh
?StoTheta?                  := 4AC2h
?StoR?                      := 4AC5h
?StoY?                      := 4AC8h
?StoN?                      := 4ACBh
?StoT?                      := 4ACEh
?StoX?                      := 4AD1h
?StoOther?                  := 4AD4h
?RclAns?                    := 4AD7h
?RclY?                      := 4ADAh
?RclN?                      := 4ADDh
?RclX?                      := 4AE0h
?RclVarSym?                 := 4AE3h
?RclSysTok?                 := 4AE6h
?StMatEl?                   := 4AE9h
?STLSTVECEL?                := 4AECh
?ConvOP1?                   := 4AEFh
?Find_Parse_Formula?        := 4AF2h
?PARSE_FORMULA?             := 4AF5h
?FetchQuotedString?         := 4AF8h
?FetchNumLine?              := 4AFBh
?ParseNameTokens?           := 4AFEh
?ParseInpGraph?             := 4B01h                    ;same as _ParseInp except 3,(iy+1Fh) is graph/split screen override, or something
?ParseInpGraphReset?        := 4B04h                    ;_ParseInpGraph except zeroes out iy+6/7, resets 3,(iy+1Ah) and 0,(iy+1Fh), fmtFlags->fmtOverride, parse within ParseInp?
?ParseInpLastEnt?           := 4B07h                    ;ParseInp on program 05h,23h,00h
?ErrOnCertainTypes?         := 4B0Ah                    ;ERR:DATA TYPE if A is one of a couple of values...subroutine in ParseInp, somehow
?CreatePair?                := 4B0Dh
?PUSHNUM?                   := 4B10h
?INCCURPCERREND?            := 4B13h
?ERREND?                    := 4B16h
?COMMAERRF?                 := 4B19h
?COMMAERR?                  := 4B1Ch
?STEQARG2?                  := 4B1Fh
?STEQARG?                   := 4B22h
?INPARG?                    := 4B25h
?STEQARG3?                  := 4B28h
?NXTFETCH?                  := 4B2Bh
?CKFETCHVAR?                := 4B2Eh
?FETCHVARA?                 := 4B31h
?FETCHVAR?                  := 4B34h
?CKENDLIN?                  := 4B37h                    ;gets parse byte in A and then _CKENDEXP
?CKENDEXP?                  := 4B3Ah                    ;checks A for 3Eh or 3Fh
?CKPARSEND?                 := 4B3Dh
?STOTYPEARG?                := 4B40h
?ConvDim?                   := 4B43h
?ConvDim00?                 := 4B46h
?AHEADEQUAL?                := 4B49h
?PARSAHEADS?                := 4B4Ch
?PARSAHEAD?                 := 4B4Fh
?AnsName?                   := 4B52h
?STOCMPREALS?               := 4B55h
?GETDEPTR?                  := 4B58h
?PUSH2BOPER?                := 4B5Bh                    ;push the value in bc onto the operator stack
?POP2BOPER?                 := 4B5Eh                    ;pop 2 bytes on the operator stack to bc
?PUSHOPER?                  := 4B61h                    ;push the value in a onto the operator stack
?POPOPER?                   := 4B64h                    ;pop 1 byte on the operator stack to a
?FIND_E_UNDEF?              := 4B67h
?STTMPEQ?                   := 4B6Ah
?FINDEOL?                   := 4B6Dh
?BRKINC?                    := 4B70h
?INCFETCH?                  := 4B73h
?CURFETCH?                  := 4B76h
?Random?                    := 4B79h
?StoRand?                   := 4B7Ch
?RandInit?                  := 4B7Fh
?resetStacks?               := 4B82h                    ;(onsp)->(errsp), (fpbase)->(fps), (opbase)->(ops)
?Factorial?                 := 4B85h
?YONOFF?                    := 4B88h
?EQSELUNSEL?                := 4B8Bh
?ITSOLVER?                  := 4B8Eh
?GRITSOLVER?                := 4B91h
?ITSOLVERB?                 := 4B94h
?ITSOLVERNB?                := 4B97h
?ExTest_INT?                := 4B9Ah
?DIST_FUN?                  := 4BADh
?LogGamma?                  := 4BA0h
?OneVar?                    := 4BA3h
?ONEVARS_0?                 := 4BA6h
?ORDSTAT?                   := 4BA9h
?INITSTATANS2?              := 4BACh
?ANOVA_SPEC?                := 4BAFh
?OutputExpr?                := 4BB2h
?CentCursor?                := 4BB5h
?TEXT?                      := 4BB8h
?FINISHSPEC?                := 4BBBh
?TRCYFUNC?                  := 4BBEh
?RCL_SEQ_X?                 := 4BC1h
?RCLSEQ2?                   := 4BC4h
?GRPPutAway?                := 4BC7h
?CKVALDELX?                 := 4BCAh
?CKVALDELTA?                := 4BCDh
?GrBufClr?                  := 4BD0h
?GRBUFCPY_V?                := 4BD3h
?FNDSELEQ?                  := 4BD6h
?CLRGRAPHXY?                := 4BD9h
?NEDXT_Y_STYLE?             := 4BDCh
?PLOTPT?                    := 4BDFh
?NEWINDEP?                  := 4BE2h
?Axes?                      := 4BE5h
?setPenX?                   := 4BE8h
?setPenY?                   := 4BEBh
?setPenT?                   := 4BEEh
?TAN_EQU_DISP?              := 4BF1h
?PutAns?                    := 4BF4h
?DispOP1A?                  := 4BF7h
?MATHTANLN?                 := 4BFAh
?ENDDRAW?                   := 4BFDh
?SetTblGraphDraw?           := 4C00h
?StartDialog?               := 4C03h
?DialogInit?                := 4C06h
?GetDialogNumOP1?           := 4C09h
?SetDialogNumOP1?           := 4C0Ch
?GetDialogNumHL?            := 4C0Fh
?ErrArgumentO123?           := 4C12h                    ;ERR:ARGUMENT if OP2>OP1 or OP1>OP3
?SetDialogKeyOverride?      := 4C15h
?ResDialogKeyOverride?      := 4C18h
?ForceDialogKeypress?       := 4C1Bh
?DialogStartGetKey?         := 4C1Eh
?StartDialog_Override?      := 4C21h
?CallDialogCallback?        := 4C24h
?SetDialogCallback?         := 4C27h
?ResDialogCallback?         := 4C2Ah
?CopyDialogNum?             := 4C2Dh
?MemClear?                  := 4C30h
?MemSet?                    := 4C33h
?ReloadAppEntryVecs?        := 4C36h
?PointOn?                   := 4C39h
?ExecuteNewPrgm?            := 4C3Ch
?StrLength?                 := 4C3Fh
?VPutMapRec?                := 4C42h
?getRomPage?                := 4C45h
?FindAppUp?                 := 4C48h
?FindAppDn?                 := 4C4Bh
?FindApp?                   := 4C4Eh
?ExecuteApp?                := 4C51h
?MonReset?                  := 4C54h
?ClearParseVar?             := 4C57h
?SetParseVarProg?           := 4C5Ah
?isContextKey?              := 4C5Dh
?IBounds?                   := 4C60h
?IOffset?                   := 4C63h
?DrawCirc2?                 := 4C66h
?CanAlphIns?                := 4C69h
?cxRedisp?                  := 4C6Ch
?GetBaseVer?                := 4C6Fh
?OPSet0DE?                  := 4C72h                    ;loads a floating point 0 to location de 
?AppGetCbl?                 := 4C75h
?AppGetCalc?                := 4C78h
?SaveDisp?                  := 4C7Bh
?SetIgnoreKey?              := 4C7Eh                    ;set 1,(iy+28h) / ret
?SetSendThisKeyBack?        := 4C81h                    ;set 2,(iy+28h) / ld (kbdKey),a / ret
?DisableApd?                := 4C84h
?EnableApd?                 := 4C87h                    ;set apdable,(iy+apdflags)
?JForceCmdNoChar2?          := 4C8Ah                    ;2.41 at least
?set2IY34?                  := 4C8Dh                    ;set 2,(iy+34) / ret
?forcecmd?                  := 4C90h
?ApdSetup?                  := 4C93h
?Get_NumKey?                := 4C96h
?AppSetup?                  := 4C99h                    ;or _AppCleanup, or something
?HandleLinkKeyActivity?     := 4C9Ch
?JForceCmdNoChar3?          := 4C9Fh                    ;2.41 at least
?ReleaseSedit?              := 4CA2h
?initsmalleditline?         := 4CA5h
?startsmalledit?            := 4CA8h
;4CABh
?SGetTokString?             := 4CAEh
?LoadPattern?               := 4CB1h
?SStringLength?             := 4CB4h
?RestorePenCol?             := 4CB7h
;4CBAh
?DoNothing?                 := 4CBDh
?ForceSmallEditReturn?      := 4CC0h
;4CC3h                      ;saves context
;4CC6h
;4CC9h
;4CCCh
?VEraseEOL?                 := 4CCFh
;4CD2h
;4CD5h
?GoToErr?                   := 4CD8h
?initsmalleditBox?          := 4CDBh
;4CDEh
?EmptyHook?                 := 4CE1h
?ForceSmallEditReturn2?     := 4CE4h
;4CE7h                      ;same as 4CC3h
;4CEAh
?ClearRow?                  := 4CEDh
;4CF0h
;4CF3h
;4CF6h
;4CF9h
;4CFCh
;4CFFh
;4D02h
;4D05h
;4D08h
;4D0Bh
;4D0Eh
;4D11h
;4D14h
;4D17h
;4D1Ah
;4D1Dh
;4D20h
;4D23h
?AppScreenUpDown?           := 4D26h                    ;shifts screen up/down, A is LCD row, H is number of lines to shift, (OP1)-(OP1+3) are something
?AppScreenUpDown1?          := 4D29h                    ;shifts screen up/down, but really no clue what the inputs are (all registers and (OP1)-(OP1+3))
;4D2Ch
?initsmalleditlinevar?      := 4D2Fh
?initsmalleditlineop1?      := 4D32h
?initsmalleditboxvar?       := 4D35h
?initsmalleditboxop1?       := 4D38h
;4D3Bh
?RestartDialog?             := 4D3Eh
?ErrCustom1?                := 4D41h
?ErrCustom2?                := 4D44h
?AppStartMouse?             := 4D47h
?AppStartMouseNoSetup?      := 4D4Ah
?AppMouseGetKey?            := 4D4Dh
?AppDispMouse?              := 4D50h
?AppEraseMouse?             := 4D53h
?AppSetupMouseMem?          := 4D56h
?GetDispRowOffset?          := 4D59h                    ;HL=A*12 (intended for A to be row and HL becomes offset into plotSScreen)
?ClearRect?                 := 4D5Ch
?InvertRect?                := 4D5Fh
?FillRect?                  := 4D62h
?AppUpdateMouse?            := 4D65h
?AppDispPrevMouse?          := 4D68h                    ;might bring previous keypress's movement to current coordinates with flags to not display
;4D6Bh                      ;restores some cursor flags and stuff
?initcellbox?               := 4D6Eh
?drawcell?                  := 4D71h
;4D74h
?invertcell?                := 4D77h
?setcelloverride?           := 4D7Ah
?DrawRectBorder?            := 4D7Dh
?ClearCell?                 := 4D80h
?covercell?                 := 4D83h
?EraseRectBorder?           := 4D86h
?FillRectPattern?           := 4D89h
?DrawRectBorderClear?       := 4D8Ch
;4D8Fh                      ;mouse subroutine
;4D92h
?VerticalLine?              := 4D95h
?IBoundsFull?               := 4D98h
?DisplayImage?              := 4D9Bh
;4D9Eh                      ;does something dumb with ports 10h/11h
;4DA1h                      ;mouse subroutine
?AppUpdateMouseCoords?      := 4DA4h
?ShiftBitsLeft?             := 4DA7h                    ;mouse subroutine, shifts B bits left from DE sprite to HL one
;4DAAh                      ;mouse subroutine
;4DADh                      ;mouse subroutine
;4DB0h                      ;mouse subroutine
;4DB3h                      ;mouse subroutine
;4DB6h                      ;mouse subroutine
;4DB9h                      ;mouse subroutine
;4DBCh                      ;mouse subroutine
?AppUpdateMouseRow?         := 4DBFh
?AppDrawMouse?              := 4DC2h                    ;set 2,(iy+2Ch) for AppEraseMouse, reset for AppDispMouse
?AppDrawMouseDirect?        := 4DC5h                    ;pretty much _AppDrawMouse, but you pass LCD column in A
?CPoint?                    := 4DC8h
?DeleteApp?                 := 4DCBh
?AppUpdateMouseXY?          := 4DCEh
?setmodecellflag?           := 4DD1h
?resetmodecellflag?         := 4DD4h
?ismodecellset?             := 4DD7h
?getmodecellflag?           := 4DDAh
;4DDDh
?CellBoxManager?            := 4DE0h
?startnewcell?              := 4DE3h
;4DE6h
?CellCursorHandle?          := 4DE9h
;4DECh
;4DEFh
?ClearCurCell?              := 4DF2h
?drawcurcell?               := 4DF5h
?invertcurcell?             := 4DF8h
?covercurcell?              := 4DFBh
?BlinkCell?                 := 4DFEh
?BlinkCellNoLookUp?         := 4E01h
?BlinkCurCell?              := 4E04h
?BlinkCellToOn?             := 4E07h
?BlinkCellToOnNoLookUp?     := 4E0Ah
?BlinkCurCellToOn?          := 4E0Dh
?BlinkCellToOff?            := 4E10h
?BlinkCellToOffNoLookUp?    := 4E13h
?BlinkCurCellToOff?         := 4E16h
?getcurmodecellflag?        := 4E19h
;4E1Ch
?startsmalleditreturn?      := 4E1Fh
;4E22h
;4E25h
?CellkHandle?               := 4E28h
?errchkalphabox?            := 4E2Bh
;4E2Eh
;4E31h
;4E34h
;4E37h
?eraseallcells?             := 4E3Ah
?iscurmodecellset?          := 4E3Dh
;4E40h
?initalphabox?              := 4E43h
;4E46h
;4E49h
?drawblnkcell?              := 4E4Ch
?ClearBlnkCell?             := 4E4Fh
?invertblnkcell?            := 4E52h
?AppMouseForceKey?          := 4E55h
?AppSetupMouseMemCoords?    := 4E58h                    ;this is _AppSetupMouseMem except you pass starting coordinates in HL
?AppMoveMouse?              := 4E5Bh                    ;this is _AppMouseForceKey and then updating coordinates
?GetStringInput?            := 4E5Eh
?GetStringInput2?           := 4E61h
?WaitEnterKeyValue?         := 4E64h
?HorizontalLine?            := 4E67h
?CreateAppVar?              := 4E6Ah
?CreateProtProg?            := 4E6Dh
?CreateVar?                 := 4E70h
?AsmComp?                   := 4E73h
?GetAsmSize?                := 4E76h
?SquishPrgm?                := 4E79h
?ExecutePrgm?               := 4E7Ch
?ChkFindSymAsm?             := 4E7Fh
?ParsePrgmName?             := 4E82h
?CSub?                      := 4E85h
?CAdd?                      := 4E88h
?CSqaure?                   := 4E8Bh
?CMult?                     := 4E8Eh
?CRecip?                    := 4E91h
?CDiv?                      := 4E94h
?CAbs?                      := 4E97h
?AddSquares?                := 4E9Ah
?CSqRoot?                   := 4E9Dh
?CLN?                       := 4EA0h
?CLog?                      := 4EA3h
?CTenX?                     := 4EA6h
?CEtoX?                     := 4EA9h
?CXrootY?                   := 4EACh
;4EAFh
?CYtoX?                     := 4EB2h
?InvertNonReal?             := 4EB5h
?CplxMult?                  := 4EB8h
?CplxDiv?                   := 4EBBh
?CplxTrunc?                 := 4EBEh
?CplxFrac?                  := 4EC1h
?CplxFloor?                 := 4EC4h
?SendHeaderPacket?          := 4EC7h
?CancelTransmission?        := 4ECAh
?SendScreenContents?        := 4ECDh
?SendRAMVarData?            := 4ED0h
?SendRAMCmd?                := 4ED3h
?SendPacket?                := 4ED6h
?ReceiveAck?                := 4ED9h
?Send4BytePacket?           := 4EDCh
?SendDataByte?              := 4EDFh
?Send4Bytes?                := 4EE2h
?SendAByte?                 := 4EE5h
?SendCByte?                 := 4EE8h
?GetSmallPacket?            := 4EEBh
?GetDataPacket?             := 4EEEh
?SendAck?                   := 4EF1h
?Get4Bytes?                 := 4EF4h
?Get3Bytes?                 := 4EF7h
?Rec1stByte?                := 4EFAh
?Rec1stByteNC?              := 4EFDh
?ContinueGetByte?           := 4F00h
?RecAByteIO?                := 4F03h
?ReceiveVar?                := 4F06h
?ReceiveVarDataExists?      := 4F09h
?ReceiveVarData?            := 4F0Ch
?SrchVLstUp?                := 4F0Fh
?SrchVLstDn?                := 4F12h
?SendVariable?              := 4F15h
?Get4BytesCursor?           := 4F18h
?Get4BytesNC?               := 4F1Bh
?Convert85List?             := 4F1Eh
?SendDirectoryContents?     := 4F21h
?SendReadyPacket?           := 4F24h
?Convert85Real?             := 4F27h
?ret_6?                     := 4F2Ah
?SendCertificate?           := 4F2Dh                    ;sends certificate in header/data packets, Flash must be unlocked, used with sending an application in LINK menu
?SendApplication?           := 4F30h
?SendOSHeader?              := 4F33h
?SendOSPage?                := 4F36h
?SendOS?                    := 4F39h
?FlashWriteDisable?         := 4F3Ch
?SendCmd?                   := 4F3Fh
?SendOSValidationData?      := 4F42h
?Disp?                      := 4F45h
?SendGetkeyPress?           := 4F48h
?RejectCommand?             := 4F4Bh
?CheckLinkLines?            := 4F4Eh
?GetHookByte?               := 4F51h
?GetBytePaged?              := 4F54h
?cursorhook?                := 4F57h
?call_library_hook?         := 4F5Ah
?call_rawkey_hook?          := 4F5Dh
?setCursorHook?             := 4F60h                    ;enable cursor hook
?EnableLibraryHook?         := 4F63h
?SetGetKeyHook?             := 4F66h
?ClrCursorHook?             := 4F69h
?DisableLibraryHook?        := 4F6Ch
?ClrRawKeyHook?             := 4F6Fh
?ResetHookBytes?            := 4F72h
?AdjustAllHooks?            := 4F75h
?getkeyhook?                := 4F78h
?SetGetcscHook?             := 4F7Bh
?ClrGetKeyHook?             := 4F7Eh
?call_linkactivity_hook?    := 4F81h
?EnableLinkActivityHook?    := 4F84h
?DisableLinkHook?           := 4F87h
?GetSmallPacket2?           := 4F8Ah
?EnableCatalog2Hook?        := 4F8Dh
?DisableCatalog2Hook?       := 4F90h
?EnableLocalizeHook?        := 4F93h
?DisableLocalizeHook?       := 4F96h
?SetTokenHook?              := 4F99h
?ClearTokenHook?            := 4F9Ch
;4F9Fh ld hl,92c6 / ld a,(92c5) / res 2,a / cp (hl) / ret
;4FA2h hl=11*(92fc)+92c9 / ld a,(hl) / and Fh / cp 2 / ret                          ; I can almost guarantee this is stat plot related
?DispListElementOffLA?      := 4FA5h
?Bit_VertSplit?             := 4FA8h
?SetHomescreenHook?         := 4FABh
?ClrHomeScreenHook?         := 4FAEh
?SetWindowHook?             := 4FB1h
?DisableWindowHook?         := 4FB4h
?SetGraphModeHook?          := 4FB7h
?DisableGraphHook?          := 4FBAh
?ParseAndStoreSysVar?       := 4FBDh
?DisplayEditSysVar?         := 4FC0h
?JForceWindowSettings?      := 4FC3h
?DelVarArc?                 := 4FC6h
?DelVarNoArc?               := 4FC9h
?SetAllPlots?               := 4FCCh
?SetYeditHook?              := 4FCFh
?DisableYEquHook?           := 4FD2h
?JForceYEqu?                := 4FD5h
?Arc_Unarc?                 := 4FD8h                    ;checks for low battery
?ArchiveVar?                := 4FDBh                    ;set 0,(iy+24h) to check for low battery first
?UnarchiveVar?              := 4FDEh
?DialogKeyHook?             := 4FE1h                    ;rawkey hook used by OS for dialog context
?SetFontHook?               := 4FE4h
?ClrFontHook?               := 4FE7h
?SetRegraphHook?            := 4FEAh
?DisableRegraphHook?        := 4FEDh
?RunGraphingHook?           := 4FF0h
?SetTraceHook?              := 4FF3h
?DisableTraceHook?          := 4FF6h
?RunTraceHook?              := 4FF9h
?NDeriv?                    := 4FFCh
?PolarDerivative?           := 4FFFh
?JForceGraphNoKey?          := 5002h
?JForceGraphKey?            := 5005h
?PowerOff?                  := 5008h
?GetKeyRetOff?              := 500Bh                    ;same as getkey, only returns kOff if 2nd+on is pressed 
?FindGroupSym?              := 500Eh
?FillBasePageTable?         := 5011h
?ArcChk?                    := 5014h
?FlashToRam?                := 5017h
?LoadDEIndPaged?            := 501Ah
?LoadCIndPaged?             := 501Dh
?SetupPagedPtr?             := 5020h
?PagedGet?                  := 5023h
?SetParserHook?             := 5026h
?ClearParserHook?           := 5029h
?SetAppChangeHook?          := 502Ch
?ClearAppChangeHook?        := 502Fh
?EnableGraphicsHook?        := 5032h
?DisableGraphicsHook?       := 5035h
?IPointNoGraphicsHook?      := 5038h
?ILineNoHook?               := 503Bh
;503Eh
?DeleteTempPrograms?        := 5041h
?EnableCatalog1Hook?        := 5044h
?DisableCatalog1Hook?       := 5047h
?EnableHelpHook?            := 504Ah
?DisableHelpHook?           := 504Dh
?DispCatalogEnd?            := 5050h
?GetMenuKeypress?           := 5053h
?GetCatalogItem?            := 5056h
?RunCatalog2Hook?           := 5059h
?RunCatalog1Hook?           := 505Ch
;505Fh
;5062h
?dispMenuTitle?             := 5065h
;5068h
?EnablecxRedispHook?        := 506Bh
?DisablecxRedispHook?       := 506Eh
?BufCpy?                    := 5071h
?BufClr?                    := 5074h
?UnOPExec2?                 := 5077h
?BinOPExec2?                := 507Ah
?LoadMenuB?                 := 507Dh                    ;clears screen and loads menu from B, plus a couple flag changes
?DisplayVarInfo?            := 5080h
?SetMenuHook?               := 5083h
?ClearMenuHook?             := 5086h
?getBCOffsetIX?             := 5089h
?GetBCOffsetIX2?            := 508Ch
?ForceFullScreen?           := 508Fh
?GetVariableData?           := 5092h
?FindSwapSector?            := 5095h
?CopyFlashPage?             := 5098h
?FindAppNumPages?           := 509Bh
?HLMinus5?                  := 509Eh
?SendArcPacket?             := 50A1h
?ForceGraphKeypress?        := 50A4h
?DoNothing3?                := 50A7h
?FormBase?                  := 50AAh
;50ADh
?IsFragmented?              := 50B0h
?Chk_Batt_Low?              := 50B3h
?Chk_Batt_Low_2?            := 50B6h
?Arc_Unarc2?                := 50B9h                    ;identical to _Arc_Unarc, except you can choose to res 0,(iy+24h) to skip low battery check
?GetAppBasePage?            := 50BCh                    ;input: a=one of an app's pages. output: a=app's first page
?SetExSpeed?                := 50BFh
?RclExit?                   := 50C2h
?GroupAllVars?              := 50C5h
?UngroupVar?                := 50C8h
?WriteToFlash?              := 50CBh                    ;ReceiveApplication or something like that on OSes below 2.40
?SetSilentLinkHook?         := 50CEh
?DisableSilentLinkHook?     := 50D1h
?TwoVarSet?                 := 50D4h
?ExecClassCToken?           := 50D7h
?ExecClass3Token?           := 50DAh
?GetSysInfo?                := 50DDh
?NZIf83Plus?                := 50E0h
?LinkStatus?                := 50E3h
?DoNothing2?                := 50E6h                    ;originally for TI-Navigator
?KeyboardGetKey?            := 50E9h
?RunAppLib?                 := 50ECh
?FindSpecialAppHeader?      := 50EFh
?SendUSBData?               := 50F2h
?AppGetCBLUSB?              := 50F5h
?AppGetCalcUSB?             := 50F8h
?GetVarCmdUSB?              := 50FBh
;50FEh
?TenX2?                     := 5101h
;5104h
;5107h
?GetVarVersion?             := 510Ah
;510Dh
;5110h
?DeleteTempEditEqu?         := 5113h
?JcursorFirst2?             := 5116h
;5119h
?PromptMoveBackLeft?        := 511Ch
?wputsEOL2?                 := 511Fh                    ;same except res 0,(iy+0Eh) first
?InvertTextInsMode?         := 5122h
;5125h
?ResetDefaults?             := 5128h
?ZeroFinanceVars?           := 512Bh
?DispHeader?                := 512Eh
?JForceGroup?               := 5131h
;5134h
;5137h
?DispCoords?                := 513Ah
;513Dh
;5140h
?chkTmr?                    := 5143h
;5146h
;5149h
;514Ch
?getDate?                   := 514Fh
?GetDateString?             := 5152h
?getDtFmt?                  := 5155h
?getDtStr?                  := 5158h
?getTime?                   := 515Bh
?GetTimeString?             := 515Eh
?getTmFmt?                  := 5161h
?getTmStr?                  := 5164h
?SetZeroOne?                := 5167h
?setDate?                   := 516Ah
?IsOneTwoThree?             := 516Dh
?setTime?                   := 5170h
?IsOP112or24?               := 5173h
?chkTimer0?                 := 5176h
?timeCnv?                   := 5179h
?GetLToOP1Extra?            := 517Ch
?ClrWindowAndFlags?         := 517Fh
?SetMachineID?              := 5182h
?ResetLists?                := 5185h
?DispValue?                 := 5188h
;518Bh
;518Eh
?ExecLib?                   := 5191h
;5194h
?CPOP1OP2Rounded?           := 5197h
?CPOP1OP2Rounded2?          := 519Ah
?OpenLib?                   := 519Dh
;51A0h
;51A3h
?ResetIOPrompt?             := 51A6h
?StrCpyVarData?             := 51A9h
?SetUpEditor?               := 51ACh
?SortA?                     := 51AFh
?SortD?                     := 51B2h
;51B5h
?IsOP1ResID?                := 51B8h
?ListEdNameCxMain?          := 51BBh
?ListEdEnterNewName?        := 51BEh
;51C1h
?ForceModeKeypress?         := 51C4h                    ;forces a keypress (and calls help hook) on any of several mode-setting contexts
?DispAboutScreen?           := 51C7h
?ChkHelpHookVer?            := 51CAh
?Disp32?                    := 51CDh
;51D0h
;51D3h
;51D6h
;51D9h
?DrawTableEditor?           := 51DCh                    ;draws table editor lines
?DisplayListNameEquals?     := 51DFh
?DisplayListHeader?         := 51E2h
?DispMatrixDimensions?      := 51E5h
?HighlightListEdItem?       := 51E8h
;51EBh
;51EEh
?MatrixName?                := 51F1h
;51F4h
;51F7h
;51FAh
;51FDh
;5200h
;5203h
;5206h
;5209h
;520Ch
;520Fh
?SetupEmptyEditTempEqu?     := 5212h
?ExecClass1Token?           := 5215h
?HandleMathTokenParse?      := 5218h
?MaybePushMultiplyOp?       := 521Bh
?RestartParseOP1Result?     := 521Eh
?Chk_Batt_Level?            := 5221h
;5224h
;5227h
;522Ah
?DisplayListEquals?         := 522Dh
?GetCurPlotListOffset?      := 5230h
?GoToLastRow?               := 5233h
?RectBorder?                := 5236h
;5239h
;523Ch
;523Fh
?LoadA5?                    := 5242h
;5245h
?NamedListToOP1?            := 5248h
;524Bh
;524Eh
;5251h
?InitUSBDeviceCallback?     := 5254h
?KillUSBDevice?             := 5257h                    ;this actually recycles the USB connection and re-inits it (I think)
?SetUSBConfiguration?       := 525Ah
?RequestUSBData?            := 525Dh
?StopReceivingUSBData?      := 5260h
?FindAppHeaderByPage?       := 5263h
?FindNextHeaderByPage?      := 5266h
?IsMatchingLaunchApp?       := 5269h
?InitTimer?                 := 526Ch
?KillTimer?                 := 526Fh
?StartTimer?                := 5272h
?RestartTimer?              := 5275h
?StopTimer?                 := 5278h
?WaitTimer?                 := 527Bh
?CheckTimer?                := 527Eh
?CheckTimerRestart?         := 5281h
?SetVertGraphActive?        := 5284h
?ClearVertGraphActive?      := 5287h
?EnableUSBHook?             := 528Ah
?DisableUSBHook?            := 528Dh
?InitUSBDevice?             := 5290h
?KillUSBPeripheral?         := 5293h
?GetCurPlotListOffset2?     := 5296h
;5299h
?GraphLine?                 := 529Ch
;529Fh
;52A2h
;52A5h
;52A8h
;52ABh
;52AEh
?ZifTableEditor?            := 52B1h
;52B4h
?GetCurPlotOffset?          := 52B7h
;52BAh
?FindAppName?               := 52BDh
;52C0h
;52C3h
?UpdateStatPlotLists?       := 52C6h
?GrBufCpyCustom?            := 52C9h
;52CCh
;52CFh
;52D2h
?VDispRealOP1?              := 52D5h
?DispXEqualsNum?            := 52D8h
?ResetGraphSettings?        := 52DBh
?InitializeVariables?       := 52DEh
;52E1h                      ;bit 4,(9C75h) (this is DEFINITELY returning the status of something when acting as a TI-SmartView Input Pad...this bit is bit 1 of the data byte from a PC HID Set Report request)
?DelVarSym?                 := 52E4h
?FindAppUpNoCase?           := 52E7h
?FindAppDnNoCase?           := 52EAh
?DeleteInvalidApps?         := 52EDh
?DeleteApp_Link?            := 52F0h
?CmpSymsNoCase?             := 52F3h
?SetAppRestrictions?        := 52F6h
?RemoveAppRestrictions?     := 52F9h
?QueryAppRestrictions?      := 52FCh
?DispAppRestrictions?       := 52FFh
?SetupHome?                 := 5302h
?GRPUTAWAYFull?             := 5305h                    ;same as _GRPUTAWAY except it assumes no split screen
?SendSmartPadKeypress?      := 5308h                    ;B and A are the inputs
?ToggleUSBSmartPadInput?    := 530Bh                    ;A is input, 0 or 1 to enable/disable
?IsUSBDeviceConnected?      := 530Eh                    ;bit 4,(81h) \ ret, this is just a guess on its purpose but it seems to work
?RecycleUSB?                := 5311h                    ;identical to 5257h
?PolarEquToOP1?             := 5314h
?ParamXEquToOP1?            := 5317h
?ParamYEquToOP1?            := 531Ah
?GetRestrictionsOptions?    := 531Dh
?DispResetComplete?         := 5320h
?PTTReset?                  := 5323h
?FindAppCustom?             := 5326h
?ClearGraphStyles?          := 5329h
;532Ch
;532Fh
;5332h
;5335h
;5338h
;533Bh
;533Eh
;5341h
;5344h
;5347h
;534Ah
;534Dh
;5350h
;5353h
;5356h
;5359h
;535Ch
;535Fh
;5362h
;5365h
;5368h
;536Bh
;536Eh
;5371h
;5374h
;5377h
;537Ah
;537Dh
;5380h
;5383h
;5386h
;5389h
;538Ch
;538Fh
;5392h
;5395h
;5398h
;539Bh
;539Eh
;53A1h
;53A4h
;53A7h
;53AAh
;53ADh
;53B0h
;53B3h
;53B6h
;53B9h
;53BCh
;53BFh
;53C2h
;53C5h
;53C8h
;53CBh
;53CEh
;53D1h
;53D4h
;53D7h
;53DAh
;53DDh
;53E0h
;53E3h
;53E6h
;53E9h
;53ECh
;53EFh
;53F2h
;53F5h
;53F8h
;53FBh
;53FEh
;5401h
;5404h
;5407h
;540Ah
;540Dh
;5410h
;5413h
;5416h
;5419h
;541Ch
;541Fh
;5422h
;5425h
;5428h
;542Bh
;542Eh
;5431h
;5434h
;5437h
;543Ah
;543Dh
;5440h
;5443h
;5446h
;5449h
?xorAret?                   := 5443h
?scfRet?                    := 5446h
?ret?                       := 5449h

;Page 1Fh ROM Calls
;--------------------------------
?bootbtf?                   := 8000h
;400Fh may point to version string ("1.02 ",0)
?MD5Final?                  := 8018h
?RSAValidate?               := 801Bh
?cmpStr?                    := 801Eh                    ;BigNumCompare
?WriteAByte?                := 8021h
?EraseFlash?                := 8024h
?FindFirstCertField?        := 8027h
?ZeroToCertificate?         := 802Ah
?GetCertificateEnd?         := 802Dh
?FindGroupedField?          := 8030h
?ret_1?                     := 8033h
?ret_2?                     := 8036h
?ret_3?                     := 8039h
?ret_4?                     := 803Ch
?ret_5?                     := 803Fh
?Mult8By8?                  := 8042h
?Mult16By8?                 := 8045h
?Div16By8?                  := 8048h
?Div16By16?                 := 804Bh
;804Eh                      ;scary certificate reading and writing, something about calc ID and fields 0A10/0A20
?LoadAIndPaged?             := 8051h
?FlashToRam2?               := 8054h
?GetCertificateStart?       := 8057h
?GetFieldSize?              := 805Ah
?FindSubField?              := 805Dh
?EraseCertificateSector?    := 8060h
?CheckHeaderKey?            := 8063h
;8066h                      ;just returns Z if specified data in field 0310h, subfield 0610h exists, DE points to data of that field you want to find
;8069h                      ;just returns number of 0810h/0710h fields that exist in certificate or something, in IX
?Load_LFontV2?              := 806Ch
?Load_LFontV?               := 806Fh
?ReceiveOS?                 := 8072h
?FindOSHeaderSubField?      := 8075h
?FindNextCertField?         := 8078h
?GetByteOrBoot?             := 807Bh
?getSerial?                 := 807Eh                    ;GetCalcSerial
?ReceiveCalcID?             := 8081h                    ;receives certificate replacement (including calculator ID, fails if already exists) and writes it, requires Flash unlocked
?EraseFlashPage?            := 8084h
?WriteFlashUnsafe?          := 8087h
?dispBootVer?               := 808Ah
?MD5Init?                   := 808Dh
?MD5Update?                 := 8090h
?MarkOSInvalid?             := 8093h
?FindProgramLicense?        := 8096h                    ;copies 8010h field to appID and other insane stuff that makes zero sense
?MarkOSValid?               := 8099h
?CheckOSValidated?          := 809Ch
?SetupAppPubKey?            := 809Fh
?SigModR?                   := 80A2h
?TransformHash?             := 80A5h
?IsAppFreeware?             := 80A8h
?FindAppHeaderSubField?     := 80ABh
?WriteValidationNumber?     := 80AEh                    ;generates two-byte validation number from calc ID and stores to certificate
?Div32By16?                 := 80B1h
?FindGroup?                 := 80B4h                    ;searches until field of DE-like group is found (DE=0A00h, it stops when it finds 0Ax0h)
?getBootVer?                := 80B7h
?getHardwareVersion?        := 80BAh
?xorA?                      := 80BDh                    ;xor a
?bignumpowermod17?          := 80C0h
?ProdNrPart1?               := 80C3h
?WriteAByteSafe?            := 80C6h
?WriteFlash?                := 80C9h
?SetupDateStampPubKey?      := 80CCh
?SetFlashLowerBound?        := 80CFh
?LowBatteryBoot?            := 80D2h
;TI-84 Plus/Silver Edition Only Entry Points
?AttemptUSBOSReceive?       := 80E4h                    ;Z to wait for USB cable insert and get OS, NZ and A= contents of port 4Dh or 56h, ON to cancel and clear RAM
?DisplayBootMessage?        := 80E7h
?NewLine2?                  := 80EAh
?DisplayBootError10?        := 80EDh
?Chk_Batt_Low_B?            := 80F0h
?Chk_Batt_Low_B2?           := 80F3h
?ReceiveOS_USB?             := 80F6h
?DisplayOSProgress?         := 80F9h
?ResetCalc?                 := 80FCh
?SetupOSPubKey?             := 80FFh
?CheckHeaderKeyHL?          := 8102h                    ;same as _CheckHeaderKey, only you pass the address of header in HL, not at appData
?USBErrorCleanup?           := 8105h                    ;kills some USB stuff (doesn't completely kill periph communication), error handler in boot code
?InitUSB?                   := 8108h                    ;initializes USB hardware as peripheral, sets 5,(iy+1Bh), C set if problems
;810Bh set 1,(81h) and wait (has something to do with USB peripheral kill, but it doesn't actually kill it)
?KillUSB?                   := 810Eh                    ;identical to 8105h, except in the middle of the outputs, it sends zero to port 4Ch
?DisplayBootError1?         := 8111h
?DisplayBootError2?         := 8114h
?DisplayBootError3?         := 8117h
?DisplayBootError4?         := 811Ah
?DisplayBootError5?         := 811Dh
?DisplayBootError6?         := 8120h
?DisplayBootError7?         := 8123h
?DisplayBootError8?         := 8126h
?DisplayBootError9?         := 8129h

;RAM Equates
;--------------------------------
?ramStart?                  := 8000h
?appData?                   := 8000h
?ramCode?                   := 8100h
?SmallEditColumnLeft?       := 8177h
?SmallEditRow?              := 8178h
?SmallEditColumnRight?      := 8179h
;penCol left edge?          equ 817Bh
?bigInteger1?               := 8182h
?SmallEditCancelParse?      := 8194h
?SmallEditRowCount?         := 81B7h
?bigInteger2?               := 81C3h
?SmallEditPromptString?     := 81CCh
?ramCodeEnd?                := 822Fh
?baseAppBrTab?              := 8230h                    ;table of base pages for apps on page < 20h (starts with eight zeroes because they're OS pages)
?clockFlag?                 := 8230h                    ;bit 2 set for 24-hour mode and don't display "AM/PM"
?clockIDs?                  := 8231h                    ;five bytes, numbers 0-4 in memory, that when present, stops displaying clock numbers in time setting context?
?bootTemp?                  := 8251h
?MD5Temp?                   := 8259h
?MD5Length?                 := 8269h
?MD5Hash?                   := 8292h
?appSearchPage?             := 82A3h
?tempSwapArea?              := 82A5h
;something                                              equ 837Bh                   ;18 bytes, probably indicates something about Flash app pages, start out as 0FFh
?appID?                     := 838Dh
?arcPageEnd?                := 8392h
?arcPtrEnd?                 := 8393h
;839Fh something...field size bytes?
?MD5Buffer?                 := 83A5h
?Abackup?                   := 83EBh
?ramReturnData?             := 83EDh
?arcInfo?                   := 83EEh
?savedArcInfo?              := 8406h
?appInfo?                   := 8432h
?appBank_jump?              := 843Ch
?appPage?                   := 843Eh
?kbdScanCode?               := 843Fh
?kbdKey?                    := 8444h
?kbdGetKy?                  := 8445h
?keyExtend?                 := 8446h
?EXTECHO?                   := keyExtend
?contrast?                  := 8447h
?apdSubTimer?               := 8448h
?apdTimer?                  := 8449h
?curTime?                   := 844Ah
?curRow?                    := 844Bh
?curCol?                    := 844Ch
?curOffset?                 := 844Dh
?curUnder?                  := 844Eh
?curY?                      := 844Fh
?curType?                   := 8450h
?curXRow?                   := 8451h
?prevDData?                 := 8452h
?lFont_record?              := 845Ah
?sFont_record?              := 8462h
?tokVarPtr?                 := 846Ah
?tokLen?                    := 846Ch
?indicMem?                  := 846Eh                    ;eight bytes used by _saveTR and _restoreTR to store image in top right corner
?indicCounter?              := 8476h
?indicBusy?                 := 8477h
?OP1?                       := 8478h
?OP1M?                      := 847Ah
?OP2?                       := 8483h
?OP2M?                      := 8485h
?OP2EXT?                    := 848Ch
?OP3?                       := 848Eh
?OP3M?                      := 8490h
?OP4?                       := 8499h
?OP4M?                      := 849Bh
?OP5?                       := 84A4h
?OP5M?                      := 84A6h
?OP6?                       := 84AFh
?OP6M?                      := 84B1h
?OP6EXT?                    := 84B8h
?progToEdit?                := 84BFh
?nameBuff?                  := 84C7h
?equ_edit_save?             := 84D2h
?iMathPtr1?                 := 84D3h
?iMathPtr2?                 := 84D5h
?iMathPtr3?                 := 84D7h
?iMathPtr4?                 := 84D9h
?iMathPtr5?                 := 84DBh
?chkDelPtr1?                := 84DDh
?chkDelPtr2?                := 84DFh
?insDelPtr?                 := 84E1h
?upDownPtr?                 := 84E3h
?fOutDat?                   := 84E5h
?asm_data_ptr1?             := 84EBh
?asm_data_ptr2?             := 84EDh
?asm_sym_ptr1?              := 84EFh
?asm_sym_ptr2?              := 84F1h
?asm_ram?                   := 84F3h
?asm_ind_call?              := 8507h
?textShadow?                := 8508h
?textShadCur?               := 8588h
?textShadTop?               := 858Ah
?textShadAlph?              := 858Bh
?textShadIns?               := 858Ch
?cxMain?                    := 858Dh
?cxPPutAway?                := 858Fh
?cxPutAway?                 := 8591h
?cxErrorEP?                 := 8595h
?cxSizeWind?                := 8597h
?cxPage?                    := 8599h
?cxCurApp?                  := 859Ah
?cxPrev?                    := 859Bh                    ;12 bytes are shadows of cxMain through cxCurApp and appFlags
?monQH?                     := 85AAh
?monQT?                     := 85ABh
?monQueue?                  := 85ACh
?onSP?                      := 85BCh
?promptRow?                 := 85C0h
?promptCol?                 := 85C1h
?promptIns?                 := 85C2h
?promptShift?               := 85C3h
?promptRet?                 := 85C4h
?promptValid?               := 85C6h
?promptTop?                 := 85C8h
?promptCursor?              := 85CAh
?promptTail?                := 85CCh
?promptBtm?                 := 85CEh
?varType?                   := 85D0h
?varCurrent?                := 85D1h
?varClass?                  := 85D9h
?CatalogCurrent?            := 85DAh                    ;word at this location starting with 6007h corresponds to what is highlighted in catalog
?menuActive?                := 85DCh
?menuAppDepth?              := 85DDh
?MenuCurrent?               := 85DEh
;                                                                                   equ 85DFh                   ;holds current submenu index
;                                                                                   equ 85E0h                   ;holds currently selected item in current submenu
;                                                                                   equ 85E1h                   ;holds number of submenus for this menu
;                                                                                   equ 85E2h                   ;holds number of items in this submenu
;                                                                                   equ 85E3h                   ;iy+appFlags backup for menu stuff
;                                                                                   equ 85E4h                   ;iy+0Ch backup for menu stuff
;                                                                                   equ 85E5h                   ;curGStyle backup for menu stuff
;                                                                                   equ 85E6h                   ;iy+graphFlags backup for menu stuff
?ProgCurrent?               := 85E8h
;something, OP1 backup?     equ 85F2h                   ;type and name of topmost variable on menu with names
;something                                              equ 85FDh
?userMenuSA?                := 85FEh
?ioPrompt?                  := 865Fh
?dImageWidth?               := 8660h
?ioFlag?                    := 8670h
?sndRecState?               := 8672h
?ioErrState?                := 8673h
?header?                    := 8674h
?ioData?                    := 867Dh
?ioNewData?                 := 8689h
?bakHeader?                 := 868Bh
;something                                              equ 8697h                   ;app bitmap for selecting stuff from menus
;something                                              equ 86B7h                   ;used in 47h and 74h link packets
?penCol?                    := 86D7h
?penRow?                    := 86D8h
?rclQueue?                  := 86D9h
?rclQueueEnd?               := 86DBh
?errNo?                     := 86DDh
?errSP?                     := 86DEh
?errOffset?                 := 86E0h
?saveSScreen?               := 86ECh
?asm_prgm_size?             := 89ECh
?bstCounter?                := 89EEh
?flags?                     := 89F0h
?appFlagsAddr?              := 89FDh
;something                                              equ 8A36h                   ;stats-related? This gets stored to (varCurrent) for some reason
?statVars?                  := 8A3Ah
?anovaf_vars?               := 8C17h
?infVars?                   := 8C4Dh
?infVar1?                   := 8C56h
?infVar2?                   := 8C5Fh
?infVar3?                   := 8C68h
?infVar4?                   := 8C71h
?infVar5?                   := 8C7Ah
?infVar6?                   := 8C83h
?infVar7?                   := 8C8Ch
?infVar8?                   := 8C95h
?infVar9?                   := 8C9Eh
?infVar10?                  := 8CA7h
?infVar11?                  := 8CB0h
?infVar12?                  := 8CB9h
?infVar13?                  := 8CC2h
?infVar14?                  := 8CCBh
?infVar15?                  := 8CD4h
?infVar16?                  := 8CDDh
?infVar17?                  := 8CE6h
?infVar18?                  := 8CEFh
?infVar19?                  := 8CF8h
?infVar20?                  := 8D01h
;something                                              equ 8D0Bh
;list-related stat vars     equ 8D0Dh
?curGStyle?                 := 8D17h
?curGY?                     := 8D18h
?curGX?                     := 8D19h
?curGY2?                    := 8D1Ah
?curGX2?                    := 8D1Bh                    ;currently selected equation while graphing
?freeSaveY?                 := 8D1Ch
?freeSaveX?                 := 8D1Dh
;100 bytes                                              equ 8D2Ah
?XOffset?                   := 8DA1h
?YOffset?                   := 8DA2h
?lcdTallP?                  := 8DA3h
?pixWideP?                  := 8DA4h
?pixWide_m_1?               := 8DA5h
?pixWide_m_2?               := 8DA6h
?lastEntryPTR?              := 8DA7h                    ;pointer to the next available byte in the entry stack
?lastEntryStk?              := 8DA9h                    ;the start of entry stack (note last entry is not in the stack, it is in the program '#'.)  This is a stack of strings.  first 2 bytes are length, followed by string. 2nd from last entry is first in this stack.
?numLastEntries?            := 8E29h                    ;number of entries you can back-track through minus one
?currLastEntry?             := 8E2Ah                    ;counter used by OS to keep track of which entry was just displayed by pressing 2nd+enter
?curPlotNumber?             := 8E63h                    ;current plot being graphed (1-3), this gets reset back to 0
;something                                              equ 8E65h
;something                                              equ 8E66h
?curInc?                    := 8E67h
?uXmin?                     := 8E7Eh
?uXmax?                     := 8E87h
?uXscl?                     := 8E90h
?uYmin?                     := 8E99h
?uYmax?                     := 8EA2h
?uYscl?                     := 8EABh
?uThetMin?                  := 8EB4h
?uThetMax?                  := 8EBDh
?uThetStep?                 := 8EC6h
?uTmin?                     := 8ECFh
?uTmax?                     := 8ED8h
?uTStep?                    := 8EE1h
?uPlotStart?                := 8EEAh
?unMax?                     := 8EF3h
?uu0?                       := 8EFCh
?uv0?                       := 8F05h
?unMin?                     := 8F0Eh
?uu02?                      := 8F17h
?uv02?                      := 8F20h
?uw0?                       := 8F29h
?uPlotStep?                 := 8F32h
?uXres?                     := 8F3Bh
?uw02?                      := 8F44h
?Xmin?                      := 8F50h
?Xmax?                      := 8F59h
?Xscl?                      := 8F62h
?Ymin?                      := 8F6Bh
?Ymax?                      := 8F74h
?Yscl?                      := 8F7Dh
?ThetaMin?                  := 8F86h
?ThetaMax?                  := 8F8Fh
?ThetaStep?                 := 8F98h
?TminPar?                   := 8FA1h
?TmaxPar?                   := 8FAAh
?Tstep?                     := 8FB3h
?PlotStart?                 := 8FBCh
?nMax?                      := 8FC5h
?u0?                        := 8FCEh
?v0?                        := 8FD7h
?nMin?                      := 8FE0h
?u02?                       := 8FE9h
?v02?                       := 8FF2h
?w0?                        := 8FFBh
?PlotStep?                  := 9004h
?XresO?                     := 900Dh
?w02?                       := 9016h
?un1?                       := 901Fh
?un2?                       := 9028h
?vn1?                       := 9031h
?vn2?                       := 903Ah
?wn1?                       := 9043h
?wn2?                       := 904Ch
?fin_N?                     := 9055h
?fin_I?                     := 905Eh
?fin_PV?                    := 9067h
?fin_PMT?                   := 9070h
?fin_FV?                    := 9079h
?fin_PY?                    := 9082h
?fin_CY?                    := 908Bh
?cal_N?                     := 9094h
?cal_I?                     := 909Dh
?cal_PV?                    := 90A6h
?cal_PMT?                   := 90AFh
?cal_FV?                    := 90B8h
?cal_PY?                    := 90C1h
?smallEditRAM?              := 90D3h
?XFact?                     := 913Fh
?YFact?                     := 9148h
?Xres_int?                  := 9151h
?deltaX?                    := 9152h
?deltaY?                    := 915Bh
?shortX?                    := 9164h
?shortY?                    := 916Dh
?lower?                     := 9176h
?upper?                     := 917Fh
?XOutSym?                   := 918Ch
?XOutDat?                   := 918Eh
?YOutSym?                   := 9190h
?YOutDat?                   := 9192h
?inputSym?                  := 9194h
?inputDat?                  := 9196h
?prevData?                  := 9198h
;something                                              equ 91D9h
;something                                              equ 91DAh
?CurTableRow?               := 91DCh
?CurTableCol?               := 91DDh
?TblMin?                    := 92B3h
?TblStep?                   := 92BCh
;something                                              equ 92C5h
;something                                              equ 92C6h
;somePlotThing1                                         equ 92D9h
;somePlotThing2                                         equ 92EAh
;somePlotThing3                                         equ 92FBh
?ES?                        := 9302h                    ;bottom of the es
?EST?                       := 9305h                    ;current height of the es
;something                                              equ 9311h                   ;this is the pointer to a table of stuff for a BASIC menu
?plotSScreen?               := 9340h
?seed1?                     := 9640h
?seed2?                     := 9649h
?basic_prog?                := 9652h
?basic_start?               := 965Bh
?nextParseByte?             := 965Dh                    ;basic_pc
?basic_end?                 := 965Fh
?numArguments?              := 9661h
;something                                              equ 9665h                   ;parser-related word
;something                                              equ 966Ch
;something                                              equ 966Dh
?cmdShadow?                 := 966Eh
?cmdShadCur?                := 96EEh
?cmdShadAlph?               := 96F0h
?cmdShadIns?                := 96F1h
?cmdCursor?                 := 96F2h
?editTop?                   := 96F4h
?editCursor?                := 96F6h
?editTail?                  := 96F8h
?editBtm?                   := 96FAh
;something                                              equ 96FEh                   ;word, this is offset into list for currently-highlighted element in list editor
;something                                              equ 9700h                   ;table entry pointer used in dialog/menu/edit buffer routines
?matrixDimensions?          := 9702h                    ;dimensions of matrix being edited in matrix editor
?editSym?                   := 9706h                    ;pointer to symbol table entry of variable being edited
?editDat?                   := 9708h                    ;pointer to data of variable being edited
;something                                              equ 970Eh                   ;stats/list editor related, usually 1
;something                                              equ 970Fh                   ;stats/list editor related, usually 0 (this is 0-based offset from listName1), pretty sure this is a page offset
;something                                              equ 9710h                   ;stats/list editor related, usually 0 (this is 0-based currently-selected list)
?listName1?                 := 9711h
?listName2?                 := 9716h
?listName3?                 := 971Bh
?listName4?                 := 9720h
?listName5?                 := 9725h
?listName6?                 := 972Ah
?listName7?                 := 972Fh
?listName8?                 := 9734h
?listName9?                 := 9739h
?listName10?                := 973Eh
?listName11?                := 9743h
?listName12?                := 9748h
?listName13?                := 974Dh
?listName14?                := 9752h
?listName15?                := 9757h
?listName16?                := 975Ch
?listName17?                := 9761h
?listName18?                := 9766h
?listName19?                := 976Bh
?listName20?                := 9770h
;something                                              equ 9775h
?y1LineType?                := 9776h                    ;these bytes define the line type for functions which are graphed
?y2LineType?                := 9777h
?y3LineType?                := 9778h
?y4LineType?                := 9779h
?y5LineType?                := 977Ah
?y6LineType?                := 977Bh
?y7LineType?                := 977Ch
?y8LineType?                := 977Dh
?y9LineType?                := 977Eh
?y0LineType?                := 977Fh
?para1LineType?             := 9780h
?para2LineType?             := 9781h
?para3LineType?             := 9782h
?para4LineType?             := 9783h
?para5LineType?             := 9784h
?para6LineType?             := 9785h
?polar1LineType?            := 9786h
?polar2LineType?            := 9787h
?polar3LineType?            := 9788h
?polar4LineType?            := 9789h
?polar5LineType?            := 978Ah
?polar6LineType?            := 978Bh
?secULineType?              := 978Ch
?secVLineType?              := 978Dh
?secWLineType?              := 978Eh
;something                                              equ 979Fh
;something                                              equ 97A1h
?winTop?                    := 97A5h
?winBtm?                    := 97A6h
?winLeftEdge?               := 97A7h
?winLeft?                   := 97A8h
?winAbove?                  := 97AAh
?winRow?                    := 97ACh
?winCol?                    := 97AEh
?fmtDigits?                 := 97B0h
?fmtString?                 := 97B1h
?fmtConv?                   := 97F2h
?fmtLeft?                   := 9804h
?fmtIndex?                  := 9806h
?fmtMatSym?                 := 9808h
?fmtMatMem?                 := 980Ah
?EQS?                       := 980Ch
;something                                              equ 980Eh
;something                                              equ 9810h
?freeRAM?                   := 9815h                    ;pretty sure this is the amount of RAM free, valid in Mem Mgmt/Del anyway
;something                                              equ 9817h
?tSymPtr1?                  := 9818h
?tSymPtr2?                  := 981Ah
?chkDelPtr3?                := 981Ch
?chkDelPtr4?                := 981Eh
?tempMem?                   := 9820h
?fpBase?                    := 9822h
?FPS?                       := 9824h
?OPBase?                    := 9826h
?OPS?                       := 9828h
?pTempCnt?                  := 982Ah
?cleanTmp?                  := 982Ch
?pTemp?                     := 982Eh                    ;end of symbol table
?progPtr?                   := 9830h
?newDataPtr?                := 9832h
?pagedCount?                := 9834h
?pagedPN?                   := 9835h
?pagedGetPtr?               := 9836h
?pagedPutPtr?               := 9838h
?pagedBuf?                  := 983Ah
;something                                              equ 984Ah                   ;this is the top LCD row for a menu (usually 1)
?appErr1?                   := 984Dh
?appErr2?                   := 985Ah
?flashByte1?                := 9867h
?flashByte2?                := 9868h
?freeArcBlock?              := 9869h
?arcPage?                   := 986Bh
?arcPtr?                    := 986Ch
?appRawKeyHandle?           := 9870h
?appBackUpScreen?           := 9872h
?customHeight?              := 9B72h
?localLanguage?             := 9B73h
?hookExecTemp?              := 9B75h
?linkActivityHook?          := 9B78h
?cursorHookPtr?             := 9B7Ch
?libraryHookPtr?            := 9B80h
?rawKeyHookPtr?             := 9B84h
?getKeyHookPtr?             := 9B88h
?homescreenHookPtr?         := 9B8Ch
?windowHookPtr?             := 9B90h
?graphHookPtr?              := 9B94h
?yEqualsHookPtr?            := 9B98h
?fontHookPtr?               := 9B9Ch
?regraphHookPtr?            := 9BA0h
?graphicsHook?              := 9BA4h
?traceHookPtr?              := 9BA8h
?parserHookPtr?             := 9BACh
?appChangeHookPtr?          := 9BB0h
?catalog1HookPtr?           := 9BB4h
?helpHookPtr?               := 9BB8h
?cxRedispHookPtr?           := 9BBCh
?menuHookPtr?               := 9BC0h
?catalog2HookPtr?           := 9BC4h
?tokenHookPtr?              := 9BC8h
?localizeHookPtr?           := 9BCCh
?silentLinkHookPtr?         := 9BD0h                    ;restartClr?
?USBActivityHookPtr?        := 9BD4h
?baseAppBrTab2?             := 9C06h                    ;table of base pages for apps on page >= 20h; first 20h bytes are zeroes.
?USBcallbackPage?           := 9C13h
?USBcallbackPtr?            := 9C14h
?vendorID?                  := 9C16h
?productID?                 := 9C18h
?devReleaseNumber?          := 9C1Ah
?oldSESpeed?                := 9C21h
?calcPeripheralState?       := 9C26h
?usb_dataWaitingCount?      := 9C27h
?basePageTable2End?         := 9C6Fh                    ;this is the last page
?port91hTemp?               := 9C79h
?usb_dataExpectCount?       := 9C80h
?offPageCallPage?           := 9C83h                    ;temporarily stores off-page page and address
?offPageCallAddress?        := 9C84h
;something                                              equ 9C86h                   ;used with SE link activity, values of 00h, 0FAh, 0FFh probably mean something
;something                                              equ 9C87h                   ;zero this to force the APPS menu to recache itself (this is always either 0, 1, or last app page, for some reason)
;something                                              equ 9C88h                   ;don't know, but it's 14 bytes and has to do with selecting stuff (if 9C87h is non-zero, this is zeroed out)
;something                                              equ 9C9Eh                   ;funky, this actually gets written to the certificate on non-83+ (11 bytes)
?SEspeed?                   := 9CAEh
;something, table index     equ 9CAFh
;something                                              equ 9CB0h
;something                                              equ 9CB1h                   ;table
;something                                              equ 9CCDh
?localTokStr?               := 9D65h
?keyForStr?                 := 9D76h
?keyToStrRam?               := 9D77h
?sedMonSp?                  := 9D88h                    ;small edit monitor SP
?bpSave?                    := 9D8Ah
?userMem?                   := 9D95h
?symTable?                  := 0FE66h

;System Flags
;----------------------------------------------------------------------
?ioDelFlag?                 := 0h
?inDelete?                  := 0                        ;1 = DELETE SCREEN 

?trigFlags?                 := 0h                       ;Trigonometry mode settings
?trigDeg?                   := 2                        ;1=degrees, 0=radians

?kbdFlags?                  := 0h                       ;Keyboard scan
?kbdSCR?                    := 3                        ;1=scan code ready
?kbdKeyPress?               := 4                        ;1=key has been pressed

?doneFlags?                 := 0h                       ;display "Done"
?donePrgm?                  := 5                        ;1=display "Done" after prgm
;----------------------------------------------------------------------
?editFlags?                 := 1h
?editOpen?                  := 2                        ;1=edit buffer is open

?ansFlags?                  := 1
?AnsScroll?                 := 3                        ;1=answer can scroll, seems must be reset in order to move about edit buffer

?monFlags?                  := 1h                       ;monitor flags
?monAbandon?                := 4                        ;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
?plotFlags?                 := 2h                       ;plot generation flags
?plotLoc?                   := 1                        ;0=bkup and display, 1=display only
?plotDisp?                  := 2                        ;1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not

?grfModeFlags?              := 2h                       ;graph mode settings
?grfFuncM?                  := 4                        ;1=function graph
?grfPolarM?                 := 5                        ;1=polar graph
?grfParamM?                 := 6                        ;1=parametric graph
?grfRecurM?                 := 7                        ;1=RECURSION graph
;----------------------------------------------------------------------
?graphFlags?                := 3h
?graphDraw?                 := 0                        ;0=graph is valid, 1=redraw graph(dirty)
?graphCursor?               := 2
;----------------------------------------------------------------------
?grfDBFlags?                := 4h
?grfDot?                    := 0                        ;0=line, 1=dot
?grfSimul?                  := 1                        ;0=sequential, 1=simultaneous
?grfGrid?                   := 2                        ;0=no grid, 1=grid
?grfPolar?                  := 3                        ;0=rectangular, 1=polar coordinates
?grfNoCoord?                := 4                        ;0=display coordinates, 1=off
?grfNoAxis?                 := 5                        ;0=axis, 1=no axis
?grfLabel?                  := 6                        ;0=off, 1=axis label
;----------------------------------------------------------------------
?textFlags?                 := 5h                       ;Text output flags
?textEraseBelow?            := 1                        ;1=erase line below small char
?textScrolled?              := 2                        ;1=screen scrolled
?textInverse?               := 3                        ;1=display inverse bit-map
?textInsMode?               := 4                        ;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
?ParsFlag?                  := 6h                       ;PARSER flags
;----------------------------------------------------------------------
?ParsFlag2?                 := 7h                       ;PARSER flags
?numOP1?                    := 0                        ;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
?newDispF?                  := 8h                       ;Derivative mode flags
?preClrForMode?             := 0                        ;1=HELP BLINK ON MODE SCREEN
?allowProgTokens?           := 1                        ;1=allow programming tokens to be parsed in BASIC programs

?apdFlags?                  := 8h                       ;Automatic power-down
?apdAble?                   := 2                        ;1=APD enabled
?apdRunning?                := 3                        ;1=APD clock running
?apdWarmStart?              := 4                        ;1=calculator is turning on from APD or power loss
;----------------------------------------------------------------------
?web_err_mask?              := 60h
;----------------------------------------------------------------------
?onFlags?                   := 9h                       ;on key flags
?parseInput?                := 1                        ;1=parse input when done
?onRunning?                 := 3                        ;1=calculator is running
?onInterrupt?               := 4                        ;1=on key interrupt request

?statFlags?                 := 9h                       ;statistics flags
;unknown                                                equ 5                       ;unknown
?statsValid?                := 6                        ;1=stats are valid
;----------------------------------------------------------------------
?fmtFlags?                  := 0Ah                      ;numeric format flags
?fmtExponent?               := 0                        ;1=show exponent, 0=no exponent
?fmtEng?                    := 1                        ;1=engineering notion, 0=scientific
?fmtHex?                    := 2                        ;1=hexadecimal
?fmtOct?                    := 3                        ;1=octal
?fmtBin?                    := 4                        ;1=binary

?numMode?                   := 0Ah
?fmtReal?                   := 5
?fmtRect?                   := 6
?fmtPolar?                  := 7

?realMode?                  := 5
?rectMode?                  := 6
?polarMode?                 := 7
;                           ;if Hex and Oct both = 1
;                           ; then Bin=0 means >Frac
;                           ; Bin=1 means >DMS
?fmtBaseMask?               := 00011100b                ; mask to base flags
?fmtBaseShift?              := 2                        ; offset to base flags
;
;       CHECK IF THESE ARE USED BY NUMFORM,
;
;                           equ  6
;                           equ  7
;----------------------------------------------------------------------
?fmtOverride?               := 0Bh                      ;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
?fmtEditFlags?              := 0Ch                      ;numeric editing flags
?fmtEdit?                   := 0                        ;1=format number for editing

?curFlags?                  := 0Ch                      ;Cursor
?curAble?                   := 2                        ;1=cursor flash is enabled
?curOn?                     := 3                        ;1=cursor is showing
?curLock?                   := 4                        ;1=cursor is locked off

?cmdFlags?                  := 0Ch                      ;command editor flags
?cmdVirgin?                 := 5                        ;1=nothing has been typed in cmd bfr
;----------------------------------------------------------------------
?appFlags?                  := 0Dh                      ;application flags
?appWantIntrpt?             := 0                        ;1=want ON key interrupts
?appTextSave?               := 1                        ;1=save characters in textShadow
?appAutoScroll?             := 2                        ;1=auto-scroll text on last line
?appMenus?                  := 3                        ;1=process keys that bring up menus, 0=check Lock menu flag
?appLockMenus?              := 4                        ;1=ignore menu keys, 0=switch to home screen and bring up menu
?appCurGraphic?             := 5                        ;1=graphic cursor
?appCurWord?                := 6                        ;1=text cursor covers entire word
?appExit?                   := 7                        ;1=application handles [EXIT] key itself

?appWantIntrptF?            := 1 shl appWantIntrpt
?appTextSaveF?              := 1 shl appTextSave
?appAutoScrollF?            := 1 shl appAutoScroll
?appMenusF?                 := 1 shl appMenus
?appLockMenusF?             := 1 shl appLockMenus
?appCurGraphicF?            := 1 shl appCurGraphic
?appCurWordF?               := 1 shl appCurWord
?appExitF?                  := 1 shl appExit
;----------------------------------------------------------------------
?rclFlag?                   := 0Eh                      ;OS recall queue flags
?enableQueue?               := 7                        ;1 = enable recall queue
;----------------------------------------------------------------------
?seqFlags?                  := 0Fh                      ;Sequential Graph flags
?webMode?                   := 0                        ;0 = NORMAL SEQ MODE, 1 = WEB MODE
?webVert?                   := 1
?sequv?                     := 2                        ;U vs V
?seqvw?                     := 3                        ;V vs W
?sequw?                     := 4                        ;U vs W
;----------------------------------------------------------------------
?promptFlags?               := 11h                      ;prompt line flags
?promptEdit?                := 0                        ;1=editing in prompt buffer
;----------------------------------------------------------------------
?indicFlags?                := 12h                      ;Indicator flags
?indicRun?                  := 0                        ;1=run indicator ON
?indicInUse?                := 1                        ;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey
?indicOnly?                 := 2                        ;interrupt handler only checks run indicator

?shiftFlags?                := 12h                      ;[2nd] and [ALPHA] flags
?shift2nd?                  := 3                        ;1=[2nd] has been pressed
?shiftAlpha?                := 4                        ;1=[ALPHA] has been pressed
?shiftLwrAlph?              := 5                        ;1=lower case, 0=upper case
?shiftALock?                := 6                        ;1=alpha lock has been pressed
?shiftKeepAlph?             := 7                        ;1=cannot cancel alpha shift
;----------------------------------------------------------------------
?tblFlags?                  := 13h                      ;table flags.
?autoFill?                  := 4                        ;1=prompt, 0=fillAuto
?autoCalc?                  := 5                        ;1=prompt, 0=CalcAuto
?reTable?                   := 6                        ;0=table is okay, 1=must recompute table.
;----------------------------------------------------------------------
?sGrFlags?                  := 14h
?grfSplit?                  := 0                        ;1=Split Graph, 0=Normal
?vertSplit?                 := 1                        ;1=Vertical (left-right) Split
?grfSChanged?               := 2                        ;1=Graph just changed Split <-> normal
?grfSplitOverride?          := 3                        ;1 = ignore graph split flag if set
?write_on_graph?            := 4                        ;1 = TEXT OR EQU WRITING TO GRAPH SCREEN
?g_style_active?            := 5                        ;1 = GRAPH STYLES ARE ENABLED, USE THEM
?cmp_mod_box?               := 6                        ;1 = DOING MOD BOX PLOT COMPUTATION
?textWrite?                 := 7
;----------------------------------------------------------------------
?newIndicFlags?             := 15h
?extraIndic?                := 0
?saIndic?                   := 1
;3 has something to do with stat/list editor
;----------------------------------------------------------------------
?interruptFlags?            := 16h
?secondTimerEnabled?        := 0                        ;1 = second hardware timer enabled
?batteryFlags?              := 16h
?batteriesGood?             := 2                        ;1 = batteries good, I think this being reset will force the calc to shut off, used in USB error handler
;----------------------------------------------------------------------
?smartFlags?                := 17h
?smarter_mask?              := 3
?smarter_test?              := 1
?smartGraph?                := 0
?smartGraph_inv?            := 1
;----------------------------------------------------------------------
?traceFlags?                := 18h
?grfExpr?                   := 0                        ;set to hide expression while tracing
;----------------------------------------------------------------------
;There is a flag 19h.
;----------------------------------------------------------------------
?statFlags2?                := 1Ah
?statDiagnosticsOn?         := 0                        ;1 = stat diagnostics on
;----------------------------------------------------------------------
?linkFlags?                 := 1Bh
?IDis95h?                   := 1                        ;1 = link routines use machine ID 95h (CBL)
?IDis82h?                   := 2                        ;1 = link routines use machine ID 82h (TI-82)
?IDis83h?                   := 3                        ;1 = link routines use machine ID 83h (TI-83)
?IDis03h?                   := 4                        ;1 = link routines use machine ID 03h (PC to TI-83)
?USBenabled?                := 5                        ;1 = use USB port first, or at least try to
;----------------------------------------------------------------------
;There is a flag 1Ch (stats-related).
;----------------------------------------------------------------------
;There is a flag 1Dh.
;----------------------------------------------------------------------
;There is a flag 1Eh.
;----------------------------------------------------------------------
?varTypeMask?               := 1Fh                      ;is this a flag byte? yes
?varGraphRef?               := 6
;----------------------------------------------------------------------
?graphFlags2?               := 1Fh
?splitOverride?             := 3                        ;0 = force full screen with ParseInp, or something
;----------------------------------------------------------------------
?asm_Flag1?                 := 21h                      ;ASM CODING
?asm_Flag2?                 := 22h                      ;ASM CODING
?asm_Flag3?                 := 23h                      ;ASM CODING
;----------------------------------------------------------------------
?arcFlag?                   := 24h
?checkBatteryLevelFirst?    := 0                        ;1 = check battery levels in Arc_Unarc first and throw error if low

?getSendFlg?                := 24h
?comFailed?                 := 1                        ;1 = Get/Send Communication Failed

?selfTestFlag?              := 24h
?resetOnPowerOn?            := 2                        ;1 = Force RAM reset when APD disabled on next power on

?appLwrCaseFlag?            := 24h
?lwrCaseActive?             := 3
;----------------------------------------------------------------------
?contextFlags?              := 25h
?nocxPutAway?               := 5                        ;1 = do not call cxPutAway routine
;----------------------------------------------------------------------
?groupFlags?                := 26h                      ;used temporarily in Arc_Unarc
?inGroup?                   := 1                        ;1 = IN GROUP CONTEXT
?noCompletionByte?          := 2                        ;1 = do not write 0FCh when calling Arc_Unarc, leave as 0FEh
?noDataWrite?               := 3                        ;1 = do not write data when calling Arc_Unarc, nor size bytes
?writeSizeBytesOnly?        := 5                        ;1 = only write size bytes when calling Arc_Unarc
;----------------------------------------------------------------------
;There is a flag 27h.
;----------------------------------------------------------------------
?APIFlg?                    := 28h
?appAllowContext?           := 0                        ;App wants context changes to happen
;1 set to ignore a key after returning from rawkeyhook
;2 set to send this key back?
;3
?appRunning?                := 4                        ;app is currently running
;5
;6
?appRetKeyOff?              := 7                        ;1 = GetKey returns kOff when [2nd]+[ON] pressed
;----------------------------------------------------------------------
?apiFlg2?                   := 29h
;----------------------------------------------------------------------
?apiFlg3?                   := 2Ah
;1 set means using small font?
;----------------------------------------------------------------------
?apiFlg4?                   := 2Bh
?cellOverride?              := 1                        ;use cell override
?fullScrnDraw?              := 2                        ;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
?mouseFlag1?                := 2Ch
;----------------------------------------------------------------------
?mouseFlag2?                := 2Dh                      ;might want to keep this always reset
;----------------------------------------------------------------------
?xapFlag0?                  := 2Eh                      ;external app flags, do not use 0,(iy+2Eh) (used by mouse routines)
?xapFlag1?                  := 2Fh
?xapFlag2?                  := 30h
?xapFlag3?                  := 31h
;----------------------------------------------------------------------
?fontFlags?                 := 32h
?fracDrawLFont?             := 2
?fracTallLFont?             := 3
?customFont?                := 7
;----------------------------------------------------------------------
?hookflags1?                := 33h                      ;also scriptFlag, rclFlag2, backGroundLink
?alt_On?                    := 0                        ;run ONSCRPT at startup
?alt_Off?                   := 1                        ;run OFFSCRPT at shutdown
?useRclQueueEnd?            := 2                        ;1 = external mode
?ignoreBPLink?              := 3                        ;1 = override flag for link activity hook
?bPLinkOn?                  := 4                        ;1 = link activity hook active
?enableKeyEcho?             := 5                        ;1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI)
?noTempDelete?              := 6                        ;1 = do not delete temporary programs at homescreen
;----------------------------------------------------------------------
?hookflags2?                := 34h                      ;also sysHookFlg
?getCSCHookActive?          := 0                        ;1 = GetCSC hook active
?libraryHookActive?         := 1                        ;1 = library hook active
;2 This is set in the OS, but never referenced and the code is never executed
?homescreenHookActive?      := 4                        ;1 = homescreen hook active
?rawKeyHookActive?          := 5                        ;1 = raw key hook active
?catalog2HookActive?        := 6                        ;1 = catalog 2 hook active
?cursorHookActive?          := 7                        ;1 = cursor hook active
;----------------------------------------------------------------------
?hookflags3?                := 35h                      ;also sysHookFlg1
?tokenHookActive?           := 0                        ;1 = token hook active
?localizeHookActive?        := 1                        ;1 = localize hook active
?windowHookActive?          := 2                        ;1 = window hook active
?graphHookActive?           := 3                        ;1 = graph hook active
?yEquHookActive?            := 4                        ;1 = Y= hook active
?fontHookActive?            := 5                        ;1 = font hook active
?regraphHookActive?         := 6                        ;1 = regraph hook active
?drawingHookActive?         := 7                        ;1 = drawing hook active
;----------------------------------------------------------------------
?hookflags4?                := 36h                      ;also sysHookFlag2
?traceHookActive?           := 0                        ;1 = trace hook active
?parserHookActive?          := 1                        ;1 = parser hook active
?appChangeHookActive?       := 2                        ;1 = app change hook active
?catalog1HookActive?        := 3                        ;1 = catalog 1 hook active
?helpHookActive?            := 4                        ;1 = help hook active
?cxRedispHookActive?        := 5                        ;1 = cxRedisp hook active
?menuHookActive?            := 6                        ;1 = menu hook active
?silentLinkHookActive?      := 7                        ;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override         equ 37h                     ;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override         equ 38h                     ;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override         equ 39h                     ;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
;hookflags5                                             equ 3Ah
?usbActivityHookActive?     := 0                        ;1 = USB activity hook active
;----------------------------------------------------------------------
?plotFlag3?                 := 3Ch  
?bufferOnly?                := 0
?useFastCirc?               := 4
;----------------------------------------------------------------------
?dBKeyFlags?                := 3Dh
?keyDefaultsF?              := 6                        ;1 = GetKey returns extended keycodes with TI-Keyboard
;----------------------------------------------------------------------
?silentLinkFlags?           := 3Eh
?silentLinkActive?          := 0                        ;1 = SE/84+ silent link is active

?extraHookFlags?            := 3Eh
?checkCatalog2HookVer?      := 3                        ;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
?openLibActive?             := 4                        ;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)
;5
;----------------------------------------------------------------------
?clockFlags?                := 3Fh
?notMDYMode?                := 0                        ;0 = M/D/Y format
?isYMDMode?                 := 1                        ;1 = Y/M/D format
?is24Hour?                  := 2                        ;1 = clock in 24 hour mode
?inAfternoon?               := 3                        ;1 = current time is in afternoon (PM) (I think)
?useTokensInString?         := 4                        ;1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset)
?displayClock?              := 5                        ;1 = display clock (this is set every second, reset otherwise)
?clockOn?                   := 6                        ;1 = clock on
;----------------------------------------------------------------------
?USBFlag1?                  := 40h
;1 Reset in I/O receiving code, doesn't seem to be used anywhere else
?usbReceiveZone1?           := 2                        ;1 = receive to RAM pages 3/2 ("zone 1")
;----------------------------------------------------------------------
?USBFlag2?                  := 41h
;0
;2
?noUSBHostInit?             := 3                        ;1 = _InitSpecificUSBDevice must fail
?usbDataWaiting?            := 5
;6
;7
;----------------------------------------------------------------------
?USBFlag3?                  := 42h
;----------------------------------------------------------------------
?USBFlag4?                  := 43h
?usbTimeoutError?           := 0                        ;1 = USB timeout error (crystal timer expired)
;----------------------------------------------------------------------

;Character Font Equates  
;-------------------------------
?LrecurN?                   := 001h
?LrecurU?                   := 002h
?LrecurV?                   := 003h
?LrecurW?                   := 004h
?Lconvert?                  := 005h
?LsqUp?                     := 006h
?LsqDown?                   := 007h
?Lintegral?                 := 008h
?Lcross?                    := 009h
?LboxIcon?                  := 00Ah
?LcrossIcon?                := 00Bh
?LdotIcon?                  := 00Ch
?LsubT?                     := 00Dh                     ;small capital T for parametric mode.
?LcubeR?                    := 00Eh                     ;slightly different 3 for cubed root.
?LhexF?                     := 00Fh
?Lroot?                     := 010h
?Linverse?                  := 011h
?Lsquare?                   := 012h
?Langle?                    := 013h
?Ldegree?                   := 014h
?Lradian?                   := 015h
?Ltranspose?                := 016h
?LLE?                       := 017h
?LNE?                       := 018h
?LGE?                       := 019h
?Lneg?                      := 01Ah
?Lexponent?                 := 01Bh
?Lstore?                    := 01Ch
?Lten?                      := 01Dh
?LupArrow?                  := 01Eh
?LdownArrow?                := 01Fh
?Lspace?                    := 020h
?Lexclam?                   := 021h
?Lquote?                    := 022h
?Lpound?                    := 023h
?Lfourth?                   := 024h
?Lpercent?                  := 025h
?Lampersand?                := 026h
?Lapostrophe?               := 027h
?LlParen?                   := 028h
?LrParen?                   := 029h
?Lasterisk?                 := 02Ah
?LplusSign?                 := 02Bh
?Lcomma?                    := 02Ch
?Ldash?                     := 02Dh
?Lperiod?                   := 02Eh
?Lslash?                    := 02Fh
?L0?                        := 030h
?L1?                        := 031h
?L2?                        := 032h
?L3?                        := 033h
?L4?                        := 034h
?L5?                        := 035h
?L6?                        := 036h
?L7?                        := 037h
?L8?                        := 038h
?L9?                        := 039h
?Lcolon?                    := 03Ah
?Lsemicolon?                := 03Bh
?LLT?                       := 03Ch
?LEQ?                       := 03Dh
?LGT?                       := 03Eh
?Lquestion?                 := 03Fh
?LatSign?                   := 040h
?LcapA?                     := 041h
?LcapB?                     := 042h
?LcapC?                     := 043h
?LcapD?                     := 044h
?LcapE?                     := 045h
?LcapF?                     := 046h
?LcapG?                     := 047h
?LcapH?                     := 048h
?LcapI?                     := 049h
?LcapJ?                     := 04Ah
?LcapK?                     := 04Bh
?LcapL?                     := 04Ch
?LcapM?                     := 04Dh
?LcapN?                     := 04Eh
?LcapO?                     := 04Fh
?LcapP?                     := 050h
?LcapQ?                     := 051h
?LcapR?                     := 052h
?LcapS?                     := 053h
?LcapT?                     := 054h
?LcapU?                     := 055h
?LcapV?                     := 056h
?LcapW?                     := 057h
?LcapX?                     := 058h
?LcapY?                     := 059h
?LcapZ?                     := 05Ah
?Ltheta?                    := 05Bh
?Lbackslash?                := 05Ch
?LrBrack?                   := 05Dh
?Lcaret?                    := 05Eh
?Lunderscore?               := 05Fh
?Lbackquote?                := 060h
?La?                        := 061h
?Lb?                        := 062h
?Lc?                        := 063h
?Ld?                        := 064h
?Le?                        := 065h
?Lf?                        := 066h
?Lg?                        := 067h
?Lh?                        := 068h
?Li?                        := 069h
?Lj?                        := 06Ah
?Lk?                        := 06Bh
?Ll?                        := 06Ch
?Lm?                        := 06Dh
?Ln?                        := 06Eh
?Lo?                        := 06Fh
?Lp?                        := 070h
?Lq?                        := 071h
?Lr?                        := 072h
?Ls?                        := 073h
?Lt?                        := 074h
?Lu?                        := 075h
?Lv?                        := 076h
?Lw?                        := 077h
?Lx?                        := 078h
?Ly?                        := 079h
?Lz?                        := 07Ah
?LlBrace?                   := 07Bh
?Lbar?                      := 07Ch
?LrBrace?                   := 07Dh
?Ltilde?                    := 07Eh
?LinvEQ?                    := 07Fh
?Lsub0?                     := 080h
?Lsub1?                     := 081h
?Lsub2?                     := 082h
?Lsub3?                     := 083h
?Lsub4?                     := 084h
?Lsub5?                     := 085h
?Lsub6?                     := 086h
?Lsub7?                     := 087h
?Lsub8?                     := 088h
?Lsub9?                     := 089h
?LcapAAcute?                := 08Ah
?LcapAGrave?                := 08Bh
?LcapACaret?                := 08Ch
?LcapADier?                 := 08Dh
?LaAcute?                   := 08Eh
?LaGrave?                   := 08Fh
?LaCaret?                   := 090h
?LaDier?                    := 091h
?LcapEAcute?                := 092h
?LcapEGrave?                := 093h
?LcapECaret?                := 094h
?LcapEDier?                 := 095h
?LeAcute?                   := 096h
?LeGrave?                   := 097h
?LeCaret?                   := 098h
?LeDier?                    := 099h
?LcapIAcute?                := 09Ah
?LcapIGrave?                := 09Bh
?LcapICaret?                := 09Ch
?LcapIDier?                 := 09Dh
?LiAcute?                   := 09Eh
?LiGrave?                   := 09Fh
?LiCaret?                   := 0A0h
?LiDier?                    := 0A1h
?LcapOAcute?                := 0A2h
?LcapOGrave?                := 0A3h
?LcapOCaret?                := 0A4h
?LcapODier?                 := 0A5h
?LoAcute?                   := 0A6h
?LoGrave?                   := 0A7h
?LoCaret?                   := 0A8h
?LoDier?                    := 0A9h
?LcapUAcute?                := 0AAh
?LcapUGrave?                := 0ABh
?LcapUCaret?                := 0ACh
?LcapUDier?                 := 0ADh
?LuAcute?                   := 0AEh
?LuGrave?                   := 0AFh
?LuCaret?                   := 0B0h
?LuDier?                    := 0B1h
?LcapCCed?                  := 0B2h
?LcCed?                     := 0B3h
?LcapNTilde?                := 0B4h
?LnTilde?                   := 0B5h
?Laccent?                   := 0B6h
?Lgrave?                    := 0B7h
?Ldieresis?                 := 0B8h
?LquesDown?                 := 0B9h
?LexclamDown?               := 0BAh
?Lalpha?                    := 0BBh
?Lbeta?                     := 0BCh
?Lgamma?                    := 0BDh
?LcapDelta?                 := 0BEh
?Ldelta?                    := 0BFh
?Lepsilon?                  := 0C0h
?LlBrack?                   := 0C1h
?Llambda?                   := 0C2h
?Lmu?                       := 0C3h
?Lpi?                       := 0C4h
?Lrho?                      := 0C5h
?LcapSigma?                 := 0C6h
?Lsigma?                    := 0C7h
?Ltau?                      := 0C8h
?Lphi?                      := 0C9h
?LcapOmega?                 := 0CAh
?LxMean?                    := 0CBh
?LyMean?                    := 0CCh
?LsupX?                     := 0CDh
?Lellipsis?                 := 0CEh
?Lleft?                     := 0CFh
?Lblock?                    := 0D0h
?Lper?                      := 0D1h
?Lhyphen?                   := 0D2h
?Larea?                     := 0D3h
?Ltemp?                     := 0D4h
?Lcube?                     := 0D5h
?Lenter?                    := 0D6h
?LimagI?                    := 0D7h
?Lphat?                     := 0D8h
?Lchi?                      := 0D9h
?LstatF?                    := 0DAh
?Llne?                      := 0DBh
?LlistL?                    := 0DCh
?LfinanN?                   := 0DDh
?L2_r_paren?                := 0DEh
?LblockArrow?               := 0DFh
?LcurO?                     := 0E0h
?LcurO2?                    := 0E1h
?LcurOcapA?                 := 0E2h
?LcurOa?                    := 0E3h
?LcurI?                     := 0E4h
?LcurI2?                    := 0E5h
?LcurIcapA?                 := 0E6h
?LcurIa?                    := 0E7h
?LGline?                    := 0E8h                     ; = 0
?LGthick?                   := 0E9h                     ; = 1
?LGabove?                   := 0EAh                     ; = 2
?LGbelow?                   := 0EBh                     ; = 3
?LGpath?                    := 0ECh                     ; = 4
?LGanimate?                 := 0EDh                     ; = 5
?LGdot?                     := 0EEh                     ; = 6
?LUpBlk?                    := 0EFh                     ;Up arrow and Block in solver
?LDnBlk?                    := 0F0h                     ;Down arrow and Block in solver
?LcurFull?                  := 0F1h                     ;note: must be last char (PutMap checks)

;(MenuCurrent) Values
;--------------------------
?mConfirmation?             := 01h
?mApps?                     := 02h
?mProgramHome?              := 03h
?mPrgm_Run?                 := 00h
?mPrgm_Edit?                := 01h
?mPrgm_New?                 := 02h
?mZoom?                     := 04h
?mZoom_Zoom?                := 00h
?mZoom_Memory?              := 01h
?mDraw?                     := 05h
?mDraw_Draw?                := 00h
?mDraw_Points?              := 01h
?mDraw_Store?               := 02h
?mStatPlots?                := 06h
?mStat?                     := 07h
?mStat_Edit?                := 00h
?mStat_Calc?                := 01h
?mStat_Tests?               := 02h
?mMath?                     := 08h
?mMath_Math?                := 00h
?mMath_Number?              := 01h
?mMath_Complex?             := 02h
?mMath_Prob?                := 03h
?mTest?                     := 09h
?mTest_Test?                := 00h
?mTest_Logic?               := 01h
?mVars?                     := 0Ah
?mVars_Vars?                := 00h
?mVars_YVars?               := 01h
?mMemory?                   := 0Ch
?mMatrix?                   := 0Dh
?mMatrix_Name?              := 00h
?mMatrix_Math?              := 01h
?mMatrix_Edit?              := 02h
?mDistr?                    := 0Eh
?mDistr_Distr?              := 00h
?mDistr_Draw?               := 01h
?mAngle?                    := 0Fh
?mList?                     := 10h
?mList_Names?               := 00h
?mList_Ops?                 := 01h
?mList_Math?                := 02h
?mCalculate?                := 11h
?mVarsWin?                  := 14h
?mVarsWin_XY?               := 00h
?mVarsWin_TTh?              := 01h
?mVarsWin_UVW?              := 02h
?mVarsZoom?                 := 15h
?mVarsZoom_ZXY?             := 00h
?mVarsZoom_ZT?              := 01h
?mVarsZoom_UVW?             := 02h
?mVarsGDB?                  := 16h
?mVarsPics?                 := 17h
?mVarsStrings?              := 18h
?mVarsStat?                 := 19h
?mVarsStat_XY?              := 00h
?mVarsStat_Sigma?           := 01h
?mVarsStat_EQ?              := 02h
?mVarsStat_Test?            := 03h
?mVarsStat_Pts?             := 04h
?mVarsTable?                := 1Ah
?mVarsYEqu?                 := 1Bh
?mVarsParametric?           := 1Ch
?mVarsPolar?                := 1Dh
?mVarsFnOnOff?              := 1Eh
?mMemReset?                 := 1Fh
?mMemReset_RAM?             := 00h
?mMemReset_ROM?             := 01h
?mMemReset_All?             := 02h
?mMemMgmtDel?               := 20h
?mMemResetDefaults?         := 21h
?mMemResetRAMAll?           := 23h
?mMemResetROMVars?          := 24h
?mMemResetROMApps?          := 25h
?mMemResetROMAll?           := 26h
?mMemResetAll?              := 27h
?mGroup?                    := 28h
?mGroup_New?                := 00h
?mGroup_Ungroup?            := 01h
?mGroupVars?                := 29h
?mProgramEdit?              := 2Ah
?mPrgmEd_Ctrl?              := 00h
?mPrgmEd_IO?                := 01h
?mPrgmEd_Exec?              := 02h
?mPrgmZoom?                 := 2Bh
?mPrgmZoom_Zoom?            := 00h
?mPrgmZoom_Mem?             := 01h
?mPrgmDraw?                 := 2Ch
?mPrgmDraw_Draw?            := 00h
?mPrgmDraw_Pt?              := 01h
?mPrgmDraw_Store?           := 02h
?mPrgmStatPlot?             := 2Dh
?mPrgmSP_Plots?             := 00h
?mPrgmSP_Type?              := 01h
?mPrgmSP_Mark?              := 02h
?mPrgmStat?                 := 2Eh
?mPrgmStat_Edit?            := 00h
?mPrgmStat_Calc?            := 01h
?mPrgmStat_Tests?           := 02h
?mPrgmMath?                 := 2Fh
?mPrgmMath_Math?            := 00h
?mPrgmMath_Num?             := 01h
?mPrgmMath_Cplx?            := 02h
?mPrgmMath_Prob?            := 03h
?mLink?                     := 30h
?mLink_Send?                := 00h
?mLink_Recieve?             := 01h
?mLinkTrasmit?              := 31h
?mLinkXmit_Xmit?            := 01h
?mGarbageCollect?           := 3Fh
?mSelectGroupVars?          := 40h
?mSelGrpVars_Sel?           := 00h
?mSelGrpVars_Grp?           := 01h
?mDuplicateName?            := 42h
?mCatalog?                  := 45h
?mFinance?                  := 22h
?mFinance_Calc?             := 00h
?mFinance_Vars?             := 01h

;Keypress Equates
;-------------------------------
?kRight?                    := 001h
?kLeft?                     := 002h
?kUp?                       := 003h
?kDown?                     := 004h
?kEnter?                    := 005h
?kAlphaEnter?               := 006h
?kAlphaUp?                  := 007h
?kAlphaDown?                := 008h
?kClear?                    := 009h
?kDel?                      := 00Ah
?kIns?                      := 00Bh
?kRecall?                   := 00Ch
?kLastEnt?                  := 00Dh
?kBOL?                      := 00Eh
?kEOL?                      := 00Fh

?kSelAll?                   := 010h
?kUnselAll?                 := 011h
?kLtoTI82?                  := 012h
?kBackup?                   := 013h
?kRecieve?                  := 014h
?kLnkQuit?                  := 015h
?kTrans?                    := 016h
?kRename?                   := 017h
?kOverw?                    := 018h
?kOmit?                     := 019h
?kCont?                     := 01Ah
?kSendID?                   := 01Bh
?kSendSW?                   := 01Ch
?kYes?                      := 01Dh
?kNoWay?                    := 01Eh
?kvSendType?                := 01Fh
?kOverWAll?                 := 020h
?kNo?                       := 025h
?kKReset?                   := 026h
?kApp?                      := 027h
?kDoug?                     := 028h
?kListflag?                 := 029h
?menuStart?                 := 02Bh
?kAreYouSure?               := 02Bh
?kAppsMenu?                 := 02Ch
?kPrgm?                     := 02Dh
?kZoom?                     := 02Eh
?kDraw?                     := 02Fh
?kSPlot?                    := 030h
?kStat?                     := 031h
?kMath?                     := 032h
?kTest?                     := 033h
?kChar?                     := 034h
?kVars?                     := 035h
?kMem?                      := 036h
?kMatrix?                   := 037h
?kDist?                     := 038h
?kAngle?                    := 039h
?kList?                     := 03Ah
?kCalc?                     := 03Bh
?kFin?                      := 03Ch
?menuEnd?                   := kFin
?kCatalog?                  := 03Eh
?kInputDone?                := 03Fh
?kOff?                      := kInputDone
?kQuit?                     := 040h
?appStart?                  := kQuit
?kLinkIO?                   := 041h
?kMatrixEd?                 := 042h
?kStatEd?                   := 043h
?kGraph?                    := 044h
?kMode?                     := 045h
?kPrgmEd?                   := 046h                     ;PROGRAM EDIT
?kPrgmCr?                   := 047h                     ;PROGRAM CREATE
?kWindow?                   := 048h                     ;RANGE EDITOR
?kYequ?                     := 049h                     ;EQUATION EDITOR
?kTable?                    := 04Ah                     ;TABLE EDITOR
?kTblSet?                   := 04Bh                     ;TABLE SET
?kChkRAM?                   := 04Ch                     ;CHECK RAM (About screen)
?kDelMem?                   := 04Dh                     ;DELETE MEM
?kResetMem?                 := 04Eh                     ;RESET MEM
?kResetDef?                 := 04Fh                     ;RESET DEFAULT
?kPrgmInput?                := 050h                     ;PROGRAM INPUT
?kZFactEd?                  := 051h                     ;ZOOM FACTOR EDITOR
?kError?                    := 052h                     ;ERROR
?kSolveTVM?                 := 053h                     ;TVM SOLVER
?kSolveRoot?                := 054h                     ;SOLVE EDITOR
?kStatP?                    := 055h                     ;stat plot
?kInfStat?                  := 056h                     ;Inferential Statistic
?kFormat?                   := 057h                     ;FORMAT
?kExtApps?                  := 058h                     ;External Applications.     NEW
?kNewApps?                  := 059h                     ;New Apps for Cerberus.
?append?                    := kNewApps
?echoStart1?                := 05Ah
?kTrace?                    := 05Ah
?kZFit?                     := 05Bh
?kZIn?                      := 05Ch
?kZOut?                     := 05Dh
?kZPrev?                    := 05Eh
?kBox?                      := 05Fh
?kDecml?                    := 060h
?kSetZm?                    := 061h
?kSquar?                    := 062h
?kStd?                      := 063h
?kTrig?                     := 064h
?kUsrZm?                    := 065h
?kZSto?                     := 066h
?kZInt?                     := 067h
?kZStat?                    := 068h
?echoStart2?                := 069h
?kSelect?                   := 069h
?kCircl?                    := 06Ah
?kClDrw?                    := 06Bh
?kLine?                     := 06Ch
?kPen?                      := 06Dh
?kPtChg?                    := 06Eh
?kPtOff?                    := 06Fh
?kPtOn?                     := 070h
?kVert?                     := 071h
?kHoriz?                    := 072h
?kText?                     := 073h
?kTanLn?                    := 074h
?kEval?                     := 075h
?kInters?                   := 076h
?kDYDX?                     := 077h
?kFnIntg?                   := 078h
?kRootG?                    := 079h
?kDYDT?                     := 07Ah
?kDXDT?                     := 07Bh
?kDRDo?                     := 07Ch
?KGFMin?                    := 07Dh
?KGFMax?                    := 07Eh
?EchoStart?                 := 07Fh
?kListName?                 := 07Fh
?kAdd?                      := 080h
?kSub?                      := 081h
?kMul?                      := 082h
?kDiv?                      := 083h
?kExpon?                    := 084h
?kLParen?                   := 085h
?kRParen?                   := 086h
?kLBrack?                   := 087h
?kRBrack?                   := 088h
?kShade?                    := 089h
?kStore?                    := 08Ah
?kComma?                    := 08Bh
?kChs?                      := 08Ch
?kDecPnt?                   := 08Dh
?k0?                        := 08Eh
?k1?                        := 08Fh
?k2?                        := 090h
?k3?                        := 091h
?k4?                        := 092h
?k5?                        := 093h
?k6?                        := 094h
?k7?                        := 095h
?k8?                        := 096h
?k9?                        := 097h
?kEE?                       := 098h
?kSpace?                    := 099h
?kCapA?                     := 09Ah
?kCapB?                     := 09Bh
?kCapC?                     := 09Ch
?kCapD?                     := 09Dh
?kCapE?                     := 09Eh
?kCapF?                     := 09Fh
?kCapG?                     := 0A0h
?kCapH?                     := 0A1h
?kCapI?                     := 0A2h
?kCapJ?                     := 0A3h
?kCapK?                     := 0A4h
?kCapL?                     := 0A5h
?kCapM?                     := 0A6h
?kCapN?                     := 0A7h
?kCapO?                     := 0A8h
?kCapP?                     := 0A9h
?kCapQ?                     := 0AAh
?kCapR?                     := 0ABh
?kCapS?                     := 0ACh
?kCapT?                     := 0ADh
?kCapU?                     := 0AEh
?kCapV?                     := 0AFh
?kCapW?                     := 0B0h
?kCapX?                     := 0B1h
?kCapY?                     := 0B2h
?kCapZ?                     := 0B3h
?kVarx?                     := 0B4h
?kPi?                       := 0B5h
?kInv?                      := 0B6h
?kSin?                      := 0B7h
?kASin?                     := 0B8h
?kCos?                      := 0B9h
?kACos?                     := 0BAh
?kTan?                      := 0BBh
?kATan?                     := 0BCh
?kSquare?                   := 0BDh
?kSqrt?                     := 0BEh
?kLn?                       := 0BFh
?kExp?                      := 0C0h
?kLog?                      := 0C1h
?kALog?                     := 0C2h
?kToABC?                    := 0C3h
?kClrTbl?                   := 0C4h
?kAns?                      := 0C5h
?kColon?                    := 0C6h
?kNDeriv?                   := 0C7h
?kFnInt?                    := 0C8h
?kRoot?                     := 0C9h
?kQuest?                    := 0CAh
?kQuote?                    := 0CBh
?kTheta?                    := 0CCh
?kIf?                       := 0CDh
?kThen?                     := 0CEh
?kElse?                     := 0CFh
?kFor?                      := 0D0h
?kWhile?                    := 0D1h
?kRepeat?                   := 0D2h
?kEnd?                      := 0D3h
?kPause?                    := 0D4h
?kLbl?                      := 0D5h
?kGoto?                     := 0D6h
?kISG?                      := 0D7h
?kDSL?                      := 0D8h
?kMenu?                     := 0D9h
?kExec?                     := 0DAh
?kReturn?                   := 0DBh
?kStop?                     := 0DCh
?kInput?                    := 0DDh
?kPrompt?                   := 0DEh
?kDisp?                     := 0DFh
?kDispG?                    := 0E0h
?kDispT?                    := 0E1h
?kOutput?                   := 0E2h
?kGetKey?                   := 0E3h
?kClrHome?                  := 0E4h
?kPrtScr?                   := 0E5h
?kSinH?                     := 0E6h
?kCosH?                     := 0E7h
?kTanH?                     := 0E8h
?kASinH?                    := 0E9h
?kACosH?                    := 0EAh
?kATanH?                    := 0EBh
?kLBrace?                   := 0ECh
?kRBrace?                   := 0EDh
?kI?                        := 0EEh
?kCONSTeA?                  := 0EFh
?kPlot3?                    := 0F0h
?kFMin?                     := 0F1h
?kFMax?                     := 0F2h
?kL1A?                      := 0F3h
?kL2A?                      := 0F4h
?kL3A?                      := 0F5h
?kL4A?                      := 0F6h
?kL5A?                      := 0F7h
?kL6A?                      := 0F8h
?kunA?                      := 0F9h
?kvnA?                      := 0FAh
?kwnA?                      := 0FBh

;THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
;THERE ARE 2 OF THESE KEYS; BE CAREFUL WITH USAGE
;------------------------------------------------
?kExtendEcho2?              := 0FCh

;THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
;INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
;(EXTECHO) FOR THE KEY VALUE 
;------------------------------------------------------
?kExtendEcho?               := 0FEh

?kE1BT?                     := 0
?kDrawInv?                  := kE1BT
?kDrawF?                    := kE1BT+1
?kPixelOn?                  := kE1BT+2
?kPixelOff?                 := kE1BT+3
?kPxlTest?                  := kE1BT+4
?kRCGDB?                    := kE1BT+5
?kRCPic?                    := kE1BT+6
?kSTGDB?                    := kE1BT+7
?kSTPic?                    := kE1BT+8
?kAbs?                      := kE1BT+9
?kTEqu?                     := kE1BT+10                 ;==
?kTNoteQ?                   := kE1BT+11                 ;<>
?kTGT?                      := kE1BT+12                 ;>
?kTGTE?                     := kE1BT+13                 ;>=
?kTLT?                      := kE1BT+14                 ;<
?kTLTE?                     := kE1BT+15                 ;<=
?kAnd?                      := kE1BT+16
?kOr?                       := kE1BT+17
?kXor?                      := kE1BT+18
?kNot?                      := kE1BT+19
?kLR1?                      := kE1BT+20
?kXRoot?                    := kE1BT+21
?kCube?                     := kE1BT+22
?kCbRt?                     := kE1BT+23                 ;Cube ROOT
?kToDec?                    := kE1BT+24
?kCubicR?                   := kE1BT+25
?kQuartR?                   := kE1BT+26
?kPlot1?                    := kE1BT+27
?kPlot2?                    := kE1BT+28
?kRound?                    := kE1BT+29
?kIPart?                    := kE1BT+30
?kFPart?                    := kE1BT+31
?kInt?                      := kE1BT+32
?kRand?                     := kE1BT+33
?kNPR?                      := kE1BT+34
?kNCR?                      := kE1BT+35
?kXFactorial?               := kE1BT+36
?kRad?                      := kE1BT+37
?kDegr?                     := kE1BT+38                 ;DEGREES CONV
?kAPost?                    := kE1BT+39
?kToDMS?                    := kE1BT+40
?kRToPo?                    := kE1BT+41                 ;R
?kRToPr?                    := kE1BT+42
?kPToRx?                    := kE1BT+43
?kPToRy?                    := kE1BT+44
?kRowSwap?                  := kE1BT+45
?kRowPlus?                  := kE1BT+46
?kTimRow?                   := kE1BT+47
?kTRowP?                    := kE1BT+48
?kSortA?                    := kE1BT+49
?kSortD?                    := kE1BT+50
?kSeq?                      := kE1BT+51
?kMin?                      := kE1BT+52
?kMax?                      := kE1BT+53
?kMean?                     := kE1BT+54
?kMedian?                   := kE1BT+55
?kSum?                      := kE1BT+56
?kProd?                     := kE1BT+57
?kDet?                      := kE1BT+58
?kTransp?                   := kE1BT+59
?kDim?                      := kE1BT+60
?kFill?                     := kE1BT+61
?kIdent?                    := kE1BT+62
?kRandm?                    := kE1BT+63
?kAug?                      := kE1BT+64
?kOneVar?                   := kE1BT+65
?kTwoVar?                   := kE1BT+66
?kLR?                       := kE1BT+67
?kLRExp?                    := kE1BT+68
?kLRLn?                     := kE1BT+69
?kLRPwr?                    := kE1BT+70
?kMedMed?                   := kE1BT+71
?kQuad?                     := kE1BT+72
?kClrLst?                   := kE1BT+73
?kHist?                     := kE1BT+74
?kxyLine?                   := kE1BT+75
?kScatter?                  := kE1BT+76
?kmRad?                     := kE1BT+77
?kmDeg?                     := kE1BT+78
?kmNormF?                   := kE1BT+79
?kmSci?                     := kE1BT+80
?kmEng?                     := kE1BT+81
?kmFloat?                   := kE1BT+82
?kFix?                      := kE1BT+83
?kSplitOn?                  := kE1BT+84
?kFullScreen?               := kE1BT+85
?kStndrd?                   := kE1BT+86
?kParam?                    := kE1BT+87
?kPolar?                    := kE1BT+88
?kSeqG?                     := kE1BT+89
?kAFillOn?                  := kE1BT+90
?kAFillOff?                 := kE1BT+91
?kACalcOn?                  := kE1BT+92
?kACalcOff?                 := kE1BT+93
?kFNOn?                     := kE1BT+94
?kFNOff?                    := kE1BT+95
?kPlotsOn?                  := kE1BT+96
?kPlotsOff?                 := kE1BT+97
?kPixelChg?                 := kE1BT+98
?kSendMBL?                  := kE1BT+99
?kRecvMBL?                  := kE1BT+100
?kBoxPlot?                  := kE1BT+101
?kBoxIcon?                  := kE1BT+102
?kCrossIcon?                := kE1BT+103
?kDotIcon?                  := kE1BT+104
?kE2BT?                     := kE1BT+105
?kSeqential?                := kE2BT
?kSimulG?                   := kE2BT+1
?kPolarG?                   := kE2BT+2
?kRectG?                    := kE2BT+3
?kCoordOn?                  := kE2BT+4
?kCoordOff?                 := kE2BT+5
?kDrawLine?                 := kE2BT+6
?kDrawDot?                  := kE2BT+7
?kAxisOn?                   := kE2BT+8
?kAxisOff?                  := kE2BT+9
?kGridOn?                   := kE2BT+10
?kGridOff?                  := kE2BT+11
?kLblOn?                    := kE2BT+12
?kLblOff?                   := kE2BT+13
?kL1?                       := kE2BT+14
?kL2?                       := kE2BT+15
?kL3?                       := kE2BT+16
?kL4?                       := kE2BT+17
?kL5?                       := kE2BT+18
?kL6?                       := kE2BT+19

;These keys are laid on top of existing keys to
;enable localization in the inferential stats editor.
;----------------------------------------------------
?kinfData?                  := kL1
?kinfStats?                 := kL1+1
?kinfYes?                   := kL1+2
?kinfNo?                    := kL1+3
?kinfCalc?                  := kL1+4
?kinfDraw?                  := kL1+5
?kinfAlt1ne?                := kL1+6
?kinfAlt1lt?                := kL1+7
?kinfAlt1gt?                := kL1+8
?kinfAlt2ne?                := kL1+9
?kinfAlt2lt?                := kL1+10
?kinfAlt2gt?                := kL1+11
?kinfAlt3ne?                := kL1+12
?kinfAlt3lt?                := kL1+13
?kinfAlt3gt?                := kL1+14
?kinfAlt4ne?                := kL1+15
?kinfAlt4lt?                := kL1+16
?kinfAlt4gt?                := kL1+17
?kinfAlt5ne?                := kL1+18
?kinfAlt5lt?                := kL1+19
?kinfAlt5gt?                := kL1+20
?kinfAlt6ne?                := kL1+21
?kinfAlt6lt?                := kL1+22
?kinfAlt6gt?                := kL1+23
?kMatA?                     := kE2BT+20
?kMatB?                     := kE2BT+21
?kMatC?                     := kE2BT+22
?kMatD?                     := kE2BT+23
?kMatE?                     := kE2BT+24
?kXmin?                     := kE2BT+25
?kXmax?                     := kE2BT+26
?kXscl?                     := kE2BT+27
?kYmin?                     := kE2BT+28
?kYmax?                     := kE2BT+29
?kYscl?                     := kE2BT+30
?kTmin?                     := kE2BT+31
?kTmax?                     := kE2BT+32
?kTStep?                    := kE2BT+33
?kOmin?                     := kE2BT+34
?kOmax?                     := kE2BT+35
?kOStep?                    := kE2BT+36
?ku0?                       := kE2BT+37
?kv0?                       := kE2BT+38
?knMin?                     := kE2BT+39
?knMax?                     := kE2BT+40
?kDeltaY?                   := kE2BT+41
?kDeltaX?                   := kE2BT+42
?kZXmin?                    := kE2BT+43
?kZXmax?                    := kE2BT+44
?kZXscl?                    := kE2BT+45
?kZYmin?                    := kE2BT+46
?kZYmax?                    := kE2BT+47
?kZYscl?                    := kE2BT+48
?kZTmin?                    := kE2BT+49
?kZTmax?                    := kE2BT+50
?kZTStep?                   := kE2BT+51
?kZOmin?                    := kE2BT+52
?kZOmax?                    := kE2BT+53
?kZOStep?                   := kE2BT+54
?kZu0?                      := kE2BT+55
?kZv0?                      := kE2BT+56
?kZnMin?                    := kE2BT+57
?kZnMax?                    := kE2BT+58
?kDelLast?                  := kE2BT+59
?kSinReg?                   := kE2BT+60
?kConstE?                   := kE2BT+61
?kPic1?                     := kE2BT+62
?kPic2?                     := kE2BT+63
?kPic3?                     := kE2BT+64
?kDelVar?                   := kE2BT+65
?kGetCalc?                  := kE2BT+66
?kRealM?                    := kE2BT+67
?kPolarM?                   := kE2BT+68
?kRectM?                    := kE2BT+69
?kuv?                       := kE2BT+70                 ;U vs V
?kvw?                       := kE2BT+71                 ;V vs W
?kuw?                       := kE2BT+72                 ;U vs W
?kFinPMTend?                := kE2BT+73
?kFinPMTbeg?                := kE2BT+74
?kGraphStyle?               := kE2BT+75
?kExprOn?                   := kE2BT+76
?kExprOff?                  := kE2BT+77
?kStatA?                    := kE2BT+78
?kStatB?                    := kE2BT+79
?kStatC?                    := kE2BT+80
?kCorr?                     := kE2BT+81
?kStatD?                    := kE2BT+82
?kStatE?                    := kE2BT+83
?kRegEq?                    := kE2BT+84
?kMinX?                     := kE2BT+85
?kQ1?                       := kE2BT+86
?kMD?                       := kE2BT+87
?kQ3?                       := kE2BT+88
?kMaxX?                     := kE2BT+89
?kStatX1?                   := kE2BT+90
?kStatY1?                   := kE2BT+91
?kStatX2?                   := kE2BT+92
?kStatY2?                   := kE2BT+93
?kStatX3?                   := kE2BT+94
?kStatY3?                   := kE2BT+95
?kTblMin?                   := kE2BT+96
?kTblStep?                  := kE2BT+97
?kSetupLst?                 := kE2BT+98
?kClrAllLst?                := kE2BT+99
?kLogistic?                 := kE2BT+100
?kZTest?                    := kE2BT+101
?kTTest?                    := kE2BT+102
?k2SampZTest?               := kE2BT+103
?k2SampTTest?               := kE2BT+104
?k1PropZTest?               := kE2BT+105
?k2PropZTest?               := kE2BT+106
?kChiTest?                  := kE2BT+107
?k2SampFTest?               := kE2BT+108
?kZIntVal?                  := kE2BT+109
?kTIntVal?                  := kE2BT+110
?k2SampTInt?                := kE2BT+111
?k2SampZInt?                := kE2BT+112
?k1PropZInt?                := kE2BT+113
?k2PropZInt?                := kE2BT+114
?kDNormal?                  := kE2BT+115
?kInvNorm?                  := kE2BT+116
?kDT?                       := kE2BT+117
?kChi?                      := kE2BT+118
?kDF?                       := kE2BT+119
?kBinPDF?                   := kE2BT+120
?kBinCDF?                   := kE2BT+121
?kPoiPDF?                   := kE2BT+122
?kPoiCDF?                   := kE2BT+123
?kun?                       := kE2BT+124
?kvn?                       := kE2BT+125
?kwn?                       := kE2BT+126
?kRecn?                     := kE2BT+127
?kPlotStart?                := kE2BT+128
?kZPlotStart?               := kE2BT+129                ;recursion n
?kXFact?                    := kE2BT+130                ;PlotStart
?kYFact?                    := kE2BT+131                ;ZPlotStart
?kANOVA?                    := kE2BT+132                ;XFact
?kMaxY?                     := kE2BT+133                ;YFact
?kWebOn?                    := kE2BT+134                ;MinY
?kWebOff?                   := kE2BT+135                ;MaxY
?kTblInput?                 := kE2BT+136                ;WEB ON
?kGeoPDF?                   := kE2BT+137                ;WEB OFF
?kGeoCDF?                   := kE2BT+138                ;WEB OFF
?kShadeNorm?                := kE2BT+139
?kShadeT?                   := kE2BT+140
?kShadeChi?                 := kE2BT+141
?kShadeF?                   := kE2BT+142
?kPlotStep?                 := kE2BT+143
?kZPlotStep?                := kE2BT+144
?kLinRegtTest?              := kE2BT+145
?KMGT?                      := kE2BT+146                ;VERT SPLIT
?kSelectA?                  := kE2BT+147
?kZFitA?                    := kE2BT+148
?kE2BT_End?                 := kZFitA

;More 2 Byte Keys 
;------------------------------------
?kE2BT2?                    := 0
?kGDB1?                     := kE2BT2
?kGDB2?                     := kE2BT2+1
?kGDB3?                     := kE2BT2+2
?kY1?                       := kE2BT2+3
?kY2?                       := kE2BT2+4
?kY3?                       := kE2BT2+5
?kY4?                       := kE2BT2+6
?kY5?                       := kE2BT2+7
?kY6?                       := kE2BT2+8
?kY7?                       := kE2BT2+9
?kY8?                       := kE2BT2+10
?kY9?                       := kE2BT2+11
?kY0?                       := kE2BT2+12
?kX1T?                      := kE2BT2+13
?kY1T?                      := kE2BT2+14
?kX2T?                      := kE2BT2+15
?kY2T?                      := kE2BT2+16
?kX3T?                      := kE2BT2+17
?kY3T?                      := kE2BT2+18
?kX4T?                      := kE2BT2+19
?kY4T?                      := kE2BT2+20
?kX5T?                      := kE2BT2+21
?kY5T?                      := kE2BT2+22
?kX6T?                      := kE2BT2+23
?kY6T?                      := kE2BT2+24
?kR1?                       := kE2BT2+25
?kR2?                       := kE2BT2+26
?kR3?                       := kE2BT2+27
?kR4?                       := kE2BT2+28
?kR5?                       := kE2BT2+29
?kR6?                       := kE2BT2+30
?kGDB4?                     := kE2BT2+31
?kGDB5?                     := kE2BT2+32
?kGDB6?                     := kE2BT2+33
?kPic4?                     := kE2BT2+34
?kPic5?                     := kE2BT2+35
?kPic6?                     := kE2BT2+36
?kGDB7?                     := kE2BT2+37
?kGDB8?                     := kE2BT2+38
?kGDB9?                     := kE2BT2+39
?kGDB0?                     := kE2BT2+40
?kPic7?                     := kE2BT2+41
?kPic8?                     := kE2BT2+42
?kPic9?                     := kE2BT2+43
?kPic0?                     := kE2BT2+44
?kStatN?                    := kE2BT2+45
?kXMean?                    := kE2BT2+46
?kConj?                     := kE2BT2+47
?kReal?                     := kE2BT2+48
?kFAngle?                   := kE2BT2+49
?kLCM?                      := kE2BT2+50
?kGCD?                      := kE2BT2+51
?kRandInt?                  := kE2BT2+52
?kRandNorm?                 := kE2BT2+53
?kToPolar?                  := kE2BT2+54
?kToRect?                   := kE2BT2+55
?kYMean?                    := kE2BT2+56
?kStdX?                     := kE2BT2+57
?kStdX1?                    := kE2BT2+58
?kw0?                       := kE2BT2+59
?kMatF?                     := kE2BT2+60
?kMatG?                     := kE2BT2+61
?kMatRH?                    := kE2BT2+62
?kMatI?                     := kE2BT2+63
?kMatJ?                     := kE2BT2+64
?kYMean1?                   := kE2BT2+65
?kStdY?                     := kE2BT2+66
?kStdY1?                    := kE2BT2+67
?kMatToLst?                 := kE2BT2+68
?kLstToMat?                 := kE2BT2+69
?kCumSum?                   := kE2BT2+70
?kDeltaLst?                 := kE2BT2+71
?kStdDev?                   := kE2BT2+72
?kVariance?                 := kE2BT2+73
?kLength?                   := kE2BT2+74
?kEquToStrng?               := kE2BT2+75
?kStrngToEqu?               := kE2BT2+76
?kExpr?                     := kE2BT2+77
?kSubStrng?                 := kE2BT2+78
?kInStrng?                  := kE2BT2+79
?kStr1?                     := kE2BT2+80
?kStr2?                     := kE2BT2+81
?kStr3?                     := kE2BT2+82
?kStr4?                     := kE2BT2+83
?kStr5?                     := kE2BT2+84
?kStr6?                     := kE2BT2+85
?kStr7?                     := kE2BT2+86
?kStr8?                     := kE2BT2+87
?kStr9?                     := kE2BT2+88
?kStr0?                     := kE2BT2+89
?kFinN?                     := kE2BT2+90
?kFinI?                     := kE2BT2+91
?kFinPV?                    := kE2BT2+92
?kFinPMT?                   := kE2BT2+93
?kFinFV?                    := kE2BT2+94
?kFinPY?                    := kE2BT2+95
?kFinCY?                    := kE2BT2+96
?kFinFPMT?                  := kE2BT2+97
?kFinFI?                    := kE2BT2+98
?kFinFPV?                   := kE2BT2+99
?kFinFN?                    := kE2BT2+100
?kFinFFV?                   := kE2BT2+101
?kFinNPV?                   := kE2BT2+102
?kFinIRR?                   := kE2BT2+103
?kFinBAL?                   := kE2BT2+104
?kFinPRN?                   := kE2BT2+105
?kFinINT?                   := kE2BT2+106
?kSumX?                     := kE2BT2+107
?kSumX2?                    := kE2BT2+108
?kFinToNom?                 := kE2BT2+109
?kFinToEff?                 := kE2BT2+110
?kFinDBD?                   := kE2BT2+111
?kStatVP?                   := kE2BT2+112
?kStatZ?                    := kE2BT2+113
?kStatT?                    := kE2BT2+114
?kStatChi?                  := kE2BT2+115
?kStatF?                    := kE2BT2+116
?kStatDF?                   := kE2BT2+117
?kStatPhat?                 := kE2BT2+118
?kStatPhat1?                := kE2BT2+119
?kStatPhat2?                := kE2BT2+120
?kStatMeanX1?               := kE2BT2+121
?kStatMeanX2?               := kE2BT2+122
?kStatStdX1?                := kE2BT2+123
?kStatStdX2?                := kE2BT2+124
?kStatStdXP?                := kE2BT2+125
?kStatN1?                   := kE2BT2+126
?kStatN2?                   := kE2BT2+127
?kStatLower?                := kE2BT2+128
?kStatUpper?                := kE2BT2+129
?kuw0?                      := kE2BT2+130
?kImag?                     := kE2BT2+131
?kSumY?                     := kE2BT2+132
?kXres?                     := kE2BT2+133
?kStat_s?                   := kE2BT2+134
?kSumY2?                    := kE2BT2+135
?kSumXY?                    := kE2BT2+136
?kuXres?                    := kE2BT2+137
?kModBox?                   := kE2BT2+138
?kNormProb?                 := kE2BT2+139
?kNormalPDF?                := kE2BT2+140
?kTPDF?                     := kE2BT2+141
?kChiPDF?                   := kE2BT2+142
?kFPDF?                     := kE2BT2+143
?kMinY?                     := kE2BT2+144               ;MinY
?kRandBin?                  := kE2BT2+145
?kRef?                      := kE2BT2+146
?kRRef?                     := kE2BT2+147
?kLRSqr?                    := kE2BT2+148
?kBRSqr?                    := kE2BT2+149
?kDiagOn?                   := kE2BT2+150
?kDiagOff?                  := kE2BT2+151
?kun1?                      := kE2BT2+152               ;FOR RCL USE WHEN GOTTEN FROM 82
?kvn1?                      := kE2BT2+153               ;FOR RCL USE WHEN GOTTEN FROM 82
?k83_00End?                 := kvn1                     ;end of original keys...
?kArchive?                  := k83_00End + 1
?kUnarchive?                := k83_00End + 2
?kAsm?                      := k83_00End + 3            ;Asm(
?kAsmPrgm?                  := k83_00End + 4            ;AsmPrgm
?kAsmComp?                  := k83_00End + 5            ;AsmComp(
?kcapAAcute?                := k83_00End + 6
?kcapAGrave?                := k83_00End + 7
?kcapACaret?                := k83_00End + 8
?kcapADier?                 := k83_00End + 9
?kaAcute?                   := k83_00End + 10
?kaGrave?                   := k83_00End + 11
?kaCaret?                   := k83_00End + 12
?kaDier?                    := k83_00End + 13
?kcapEAcute?                := k83_00End + 14
?kcapEGrave?                := k83_00End + 15
?kcapECaret?                := k83_00End + 16
?kcapEDier?                 := k83_00End + 17
?keAcute?                   := k83_00End + 18
?keGrave?                   := k83_00End + 19
?keCaret?                   := k83_00End + 20
?keDier?                    := k83_00End + 21
?kcapIAcute?                := k83_00End + 22
?kcapIGrave?                := k83_00End + 23
?kcapICaret?                := k83_00End + 24
?kcapIDier?                 := k83_00End + 25
?kiAcute?                   := k83_00End + 26
?kiGrave?                   := k83_00End + 27
?kiCaret?                   := k83_00End + 28
?kiDier?                    := k83_00End + 29
?kcapOAcute?                := k83_00End + 30
?kcapOGrave?                := k83_00End + 31
?kcapOCaret?                := k83_00End + 32
?kcapODier?                 := k83_00End + 33
?koAcute?                   := k83_00End + 34
?koGrave?                   := k83_00End + 35
?koCaret?                   := k83_00End + 36
?koDier?                    := k83_00End + 37
?kcapUAcute?                := k83_00End + 38
?kcapUGrave?                := k83_00End + 39
?kcapUCaret?                := k83_00End + 40
?kcapUDier?                 := k83_00End + 41
?kuAcute?                   := k83_00End + 42
?kuGrave?                   := k83_00End + 43
?kuCaret?                   := k83_00End + 44
?kuDier?                    := k83_00End + 45
?kcapCCed?                  := k83_00End + 46
?kcCed?                     := k83_00End + 47
?kcapNTilde?                := k83_00End + 48
?knTilde?                   := k83_00End + 49
?kaccent?                   := k83_00End + 50
?kgrave?                    := k83_00End + 51
?kdieresis?                 := k83_00End + 52
?kquesDown?                 := k83_00End + 53
?kexclamDown?               := k83_00End + 54
?kalpha?                    := k83_00End + 55
?kbeta?                     := k83_00End + 56
?kgamma?                    := k83_00End + 57
?kcapDelta?                 := k83_00End + 58
?kdelta?                    := k83_00End + 59
?kepsilon?                  := k83_00End + 60
?klambda?                   := k83_00End + 61
?kmu?                       := k83_00End + 62
?kpi2?                      := k83_00End + 63
?krho?                      := k83_00End + 64
?kcapSigma?                 := k83_00End + 65
?ksigma?                    := k83_00End + 66
?ktau?                      := k83_00End + 67
?kphi?                      := k83_00End + 68
?kcapOmega?                 := k83_00End + 69
?kphat?                     := k83_00End + 70
?kchi2?                     := k83_00End + 71
?kstatF2?                   := k83_00End + 72
?kLa?                       := k83_00End + 73
?kLb?                       := k83_00End + 74
?kLc?                       := k83_00End + 75
?kLd?                       := k83_00End + 76
?kLe?                       := k83_00End + 77
?kLf?                       := k83_00End + 78
?kLg?                       := k83_00End + 79
?kLh?                       := k83_00End + 80
?kLi?                       := k83_00End + 81
?kLj?                       := k83_00End + 82
?kLk?                       := k83_00End + 83
?kLl?                       := k83_00End + 84
?kLm?                       := k83_00End + 85
?kLsmalln?                  := k83_00End + 86
?kLo?                       := k83_00End + 87
?kLp?                       := k83_00End + 88
?kLq?                       := k83_00End + 89
?kLsmallr?                  := k83_00End + 90
?kLs?                       := k83_00End + 91
?kLt?                       := k83_00End + 92
?kLu?                       := k83_00End + 93
?kLv?                       := k83_00End + 94
?kLw?                       := k83_00End + 95
?kLx?                       := k83_00End + 96
?kLy?                       := k83_00End + 97
?kLz?                       := k83_00End + 98
?kGarbageC?                 := k83_00End + 99           ;GarbageCollect
?kE2BT2_End?                := kGarbageC

;TI-83 Plus Context Equates
;---------------------------------------------
?cxCmd?                     := kQuit                    ;home screen
?cxMatEdit?                 := kMatrixEd                ;matrix editor
?cxPrgmEdit?                := kPrgmEd                  ;program editor
?cxEquEdit?                 := kYequ                    ;equation editor
?cxGrRange?                 := kWindow                  ;graph range editor
?cxGrZfact?                 := kZFactEd                 ;graph zoom factors editor
?cxGraph?                   := kGraph                   ;graph mode
?cxStatEdit?                := kStatEd                  ;statistics list editor
?cxPrgmInput?               := kPrgmInput               ;programmed input
?cxError?                   := kError                   ;error handler
?cxLinkIO?                  := kLinkIO                  ;LINK I/O interface
?cxMem?                     := kResetMem                ;reset memory
?cxDefMem?                  := kResetDef                ;reset default
?cxRAMApp?                  := kChkRAM                  ;RAM usage screen
?cxMode?                    := kMode                    ;mode settings screen
?cxErase?                   := kDelMem                  ;memory erase
?cxPrgmCreate?              := kPrgmCr                  ;PROGRAM CREATE
?cxTableEditor?             := kTable                   ;TABLE EDITOR
?cxTableSet?                := kTblSet                  ;TABLE SET UP
?cxStatPlot?                := kStatP                   ;STAT PLOTS
?cxInfStat?                 := kInfStat                 ;Inferential Statistic
?cxFormat?                  := kFormat                  ;FORMAT CONTEXT
?cxSolveTVM?                := kSolveTVM                ;Solve TVM
?cxSolveRoot?               := kSolveRoot               ;Solve Root
?lastOldApp?                := kExtApps                 ;external applications
?cxextapps?                 := kExtApps
?cxNewApps?                 := kNewApps                 ;new cerberus applications
?cxGroup?                   := cxNewApps+0              ;1st new app.
?cxUnGroup?                 := cxNewApps+1              ;2nd new app.
?lastNewApp?                := cxUnGroup                ;last new app for this ver

;Scan Code Equates
;-------------------------------
?skDown?                    := 01h
?skLeft?                    := 02h
?skRight?                   := 03h
?skUp?                      := 04h
?skEnter?                   := 09h
?skAdd?                     := 0Ah
?skSub?                     := 0Bh
?skMul?                     := 0Ch
?skDiv?                     := 0Dh
?skPower?                   := 0Eh
?skClear?                   := 0Fh
?skChs?                     := 11h
?sk3?                       := 12h
?sk6?                       := 13h
?sk9?                       := 14h
?skRParen?                  := 15h
?skTan?                     := 16h
?skVars?                    := 17h
?skDecPnt?                  := 19h
?sk2?                       := 1Ah
?sk5?                       := 1Bh
?sk8?                       := 1Ch
?skLParen?                  := 1Dh
?skCos?                     := 1Eh
?skPrgm?                    := 1Fh
?skStat?                    := 20h
?sk0?                       := 21h
?sk1?                       := 22h
?sk4?                       := 23h
?sk7?                       := 24h
?skComma?                   := 25h
?skSin?                     := 26h
?skMatrix?                  := 27h
?skGraphvar?                := 28h
?skStore?                   := 2Ah
?skLn?                      := 2Bh
?skLog?                     := 2Ch
?skSquare?                  := 2Dh
?skRecip?                   := 2Eh
?skMath?                    := 2Fh
?skAlpha?                   := 30h
?skGraph?                   := 31h
?skTrace?                   := 32h
?skZoom?                    := 33h
?skWindow?                  := 34h
?skYEqu?                    := 35h
?sk2nd?                     := 36h
?skMode?                    := 37h
?skDel?                     := 38h

;Tokens
;----------------------------------------------------
?EOSSTART?                  := 0

;DISPLAY CONVERSIONS COME IMMEDIATELY BEFORE 'TSTORE'
;
?DCONV?                     := 01h
;
?tToDMS?                    := DCONV                    ;01h
?tToDEC?                    := DCONV+1                  ;02h
?tToAbc?                    := DCONV+2                  ;03h > A b/c
;
?tStore?                    := DCONV+3                  ;04h Lstore 01
;
?tBoxPlot?                  := 05h
;
?BRACKS?                    := 06h
;
?tLBrack?                   := BRACKS                   ;06h '['
?tRBrack?                   := BRACKS+1                 ;07h ']'
?tLBrace?                   := BRACKS+2                 ;08h '{'
?tRBrace?                   := BRACKS+3                 ;09h '}'
;
?tPOST1?                    := BRACKS+4
;
?tFromRad?                  := tPOST1                   ;0Ah Lradian
?tFromDeg?                  := tPOST1+1                 ;0Bh Ldegree
?tRecip?                    := tPOST1+2                 ;0Ch Linverse
?tSqr?                      := tPOST1+3                 ;0Dh Lsquare
?tTrnspos?                  := tPOST1+4                 ;0Eh Ltranspose
?tCube?                     := tPOST1+5                 ;0Fh ' xor 3'
;
?tLParen?                   := 10h                      ;10h '('
?tRParen?                   := 11h                      ;11h ')'
;
?IMUN?                      := 12h
;
?tRound?                    := IMUN                     ;12h 'round'
?tPxTst?                    := IMUN+1                   ;13h 'PXL-TEST'
?tAug?                      := IMUN+2                   ;14h 'aug'
?tRowSwap?                  := IMUN+3                   ;15h 'rSwap'
?tRowPlus?                  := IMUN+4                   ;16h 'rAdd'
?tmRow?                     := IMUN+5                   ;17h 'multR'
?tmRowPlus?                 := IMUN+6                   ;18h 'mRAdd'
?tMax?                      := IMUN+7                   ;19h 'max'
?tMin?                      := IMUN+8                   ;1Ah 'min'
?tRToPr?                    := IMUN+9                   ;1Bh 'R>Pr
?tRToPo?                    := IMUN+10                  ;1Ch 'R>Po
?tPToRx?                    := IMUN+11                  ;1Dh 'P>Rx
?tPToRy?                    := IMUN+12                  ;1Eh 'P>Ry
?tMedian?                   := IMUN+13                  ;1Fh 'MEDIAN
?tRandM?                    := IMUN+14                  ;20h 'randM'
?tMean?                     := IMUN+15                  ;21h
?tRoot?                     := IMUN+16                  ;22h 'ROOT'
?tSeries?                   := IMUN+17                  ;23h 'seq'
?tFnInt?                    := IMUN+18                  ;24h 'fnInt'
?tNDeriv?                   := IMUN+19                  ;25h 'fnIr'
?tEvalF?                    := IMUN+20                  ;26h
?tFmin?                     := IMUN+21                  ;27h
?tFmax?                     := IMUN+22                  ;28h
;
?tEOSEL?                    := IMUN+23
;
?tSpace?                    := tEOSEL                   ;29h ' '
?tString?                   := tEOSEL+1                 ;2Ah '"'
?tComma?                    := tEOSEL+2                 ;2Bh ','
;
?tii?                       := 2Ch                      ;i

;Postfix Functions
;-----------------------------------------
?tPost?                     := 2Dh
;
?tFact?                     := tPost                    ;2Dh '!'
;
?tCubicR?                   := 2Eh
?tQuartR?                   := 2Fh

;Number Tokens 
;---------------------------------------
?NUMS?                      := 30h
;
?t0?                        := NUMS                     ;30h
?t1?                        := NUMS+1                   ;31h
?t2?                        := NUMS+2                   ;32h
?t3?                        := NUMS+3                   ;33h
?t4?                        := NUMS+4                   ;34h
?t5?                        := NUMS+5                   ;35h
?t6?                        := NUMS+6                   ;36h
?t7?                        := NUMS+7                   ;37h
?t8?                        := NUMS+8                   ;38h
?t9?                        := NUMS+9                   ;39h
?tDecPt?                    := NUMS+10                  ;3Ah
?tee?                       := NUMS+11                  ;3Bh

;Binary OP
;-------------------------------------------
?tOr?                       := 3Ch                      ;3Ch '_or_'
?tXor?                      := 3Dh                      ;3Dh
;
?tColon?                    := 3Eh                      ;3Eh ':'
?tEnter?                    := 3Fh                      ;3Fh Lenter
;
?tAnd?                      := 40h                      ;40h '_and_'

;Letter Tokens
;--------------------------------------
?LET?                       := 41h
?tA?                        := LET                      ;41h
?tB?                        := LET+1                    ;42h
?tC?                        := LET+2                    ;43h
?tD?                        := LET+3                    ;44h
?tE?                        := LET+4                    ;45h
?tF?                        := LET+5                    ;46h
?tG?                        := LET+6                    ;47h
?tH?                        := LET+7                    ;48h
?tI?                        := LET+8                    ;49h
?tJ?                        := LET+9                    ;4Ah
?tK?                        := LET+10                   ;4Bh
?tL?                        := LET+11                   ;4Ch
?tM?                        := LET+12                   ;4Dh
?tN?                        := LET+13                   ;4Eh
?tO?                        := LET+14                   ;4Fh
?tP?                        := LET+15                   ;50h
?tQ?                        := LET+16                   ;51h
?tR?                        := LET+17                   ;52h
?tS?                        := LET+18                   ;53h
?tT?                        := LET+19                   ;54h
?tU?                        := LET+20                   ;55h
?tV?                        := LET+21                   ;56h
?tW?                        := LET+22                   ;57h
?tX?                        := LET+23                   ;58h
?tY?                        := LET+24                   ;59h
?tZ?                        := LET+25                   ;5Ah
?tTheta?                    := LET+26                   ;5Bh

;These Var Tokens Are 1st Of A Double Token
;------------------------------------------

?vToks?                     := LET+27

;User Matrix Token, 2nd Token Needed For Name
;
?tVarMat?                   := vToks                    ;5Ch
;
;User List Token, 2nd Token Needed For Name
;
?tVarLst?                   := vToks+1                  ;5Dh
;
;User Equation Token, 2nd Token Needed For Name
;
?tVarEqu?                   := vToks+2                  ;5Eh
?tProg?                     := vToks+3                  ;5Fh
;
;User Pict Token, 2nd Token Needed For Name
;
?tVarPict?                  := vToks+4                  ;60h
;
;User GDB Token, 2nd Token Needed For Name
;
?tVarGDB?                   := vToks+5                  ;61h
?tVarOut?                   := vToks+6                  ;62h
?tVarSys?                   := vToks+7                  ;63h

;Mode Setting Commands
;-------------------------------------------------
?MODESA?                    := vToks+8                  ;64h
?tRad?                      := MODESA                   ;64h 'Radian'
?tDeg?                      := MODESA+1                 ;65h 'Degree'
?tNormF?                    := MODESA+2                 ;66h 'Normal'
?tSci?                      := MODESA+3                 ;67h 'Sci'
?tEng?                      := MODESA+4                 ;68h 'Eng'
?tFloat?                    := MODESA+5                 ;69h 'Float'
?CMPS?                      := 6Ah
?tEQ?                       := CMPS                     ;6Ah '=='
?tLT?                       := CMPS+1                   ;6Bh '<'
?tGT?                       := CMPS+2                   ;6Ch '>'
?tLE?                       := CMPS+3                   ;6Dh LLE
?tGE?                       := CMPS+4                   ;6Eh LGE
?tNE?                       := CMPS+5                   ;6Fh LNE

;Binary OP
;---------------------------------------
?tAdd?                      := 70h                      ;70h '+'
?tSub?                      := 71h                      ;71h '-'
?tAns?                      := 72h                      ;72h

;Mode Setting Commands
;-------------------------------------------------------
?MODES?                     := 73h
?tFix?                      := MODES                    ;73h 'Fix_'
?tSplitOn?                  := MODES+1                  ;74h
?tFullScreen?               := MODES+2                  ;75h
?tStndrd?                   := MODES+3                  ;76h 'Func'
?tParam?                    := MODES+4                  ;77h 'Param'
?tPolar?                    := MODES+5                  ;78h 'Pol'
?tSeqG?                     := MODES+6                  ;79h
?tAFillOn?                  := MODES+7                  ;7Ah 'AUTO FILL ON'
?tAFillOff?                 := MODES+8                  ;7Bh
?tACalcOn?                  := MODES+9                  ;7Ch
?tACalcOff?                 := MODES+10                 ;7Dh 'AutoFill OFF'

;Graph Format Tokens Are 2 Byte Tokens
;----------------------------------------
?tGFormat?                  := MODES+11                 ;7Eh
?tBoxIcon?                  := 7Fh
?tCrossIcon?                := 80h
?tDotIcon?                  := 81h

;(More) Binary OP
;---------------------------------------
?tMul?                      := 82h                      ;82h '*'
?tDiv?                      := 83h                      ;83h '/'

;Some Graph Commands
;------------------------------------------------------
?GRCMDS?                    := 84h
?tTrace?                    := GRCMDS                   ; 84h 'Trace'
?tClDrw?                    := GRCMDS+1                 ; 85h 'ClDrw'
?tZoomStd?                  := GRCMDS+2                 ; 86h 'ZStd'
?tZoomtrg?                  := GRCMDS+3                 ; 87h 'Ztrg'
?tZoomBox?                  := GRCMDS+4                 ; 88h 'ZBOX'
?tZoomIn?                   := GRCMDS+5                 ; 89h 'ZIn'
?tZoomOut?                  := GRCMDS+6                 ; 8Ah 'ZOut'
?tZoomSqr?                  := GRCMDS+7                 ; 8Bh 'ZSqr'
?tZoomInt?                  := GRCMDS+8                 ; 8Ch 'ZInt'
?tZoomPrev?                 := GRCMDS+9                 ; 8Dh 'ZPrev'
?tZoomDec?                  := GRCMDS+10                ; 8Eh 'ZDecm'
?tZoomStat?                 := GRCMDS+11                ; 8Fh 'ZStat
?tUsrZm?                    := GRCMDS+12                ; 90h 'ZRcl'
?tPrtScrn?                  := GRCMDS+13                ; 91h 'PrtScrn'
?tZoomSto?                  := GRCMDS+14                ; 92h  ZOOM STORE
?tText?                     := GRCMDS+15                ; 93h

;Binary OP (Combination and Permutation)
;-------------------------------------------------
?tnPr?                      := GRCMDS+16                ;94h '_nPr_'
?tnCr?                      := GRCMDS+17                ;95h '_nCr_'

;More Graph Commands
;--------------------------------------------------
?tYOn?                      := GRCMDS+18                ;96h 'FnOn_'
?tYOff?                     := GRCMDS+19                ;97h 'FnOff_'
?tStPic?                    := GRCMDS+20                ;98h 'StPic_'
?tRcPic?                    := GRCMDS+21                ;99h 'RcPic_'
?tStoDB?                    := GRCMDS+22                ;9Ah 'StGDB_'
?tRclDB?                    := GRCMDS+23                ;9Bh 'RcGDB_'
?tLine?                     := GRCMDS+24                ;9Ch 'Line'
?tVert?                     := GRCMDS+25                ;9Dh 'Vert_'
?tPtOn?                     := GRCMDS+26                ;9Eh 'PtOn'
?tPtOff?                    := GRCMDS+27                ;9Fh 'PtOff'

;Token A0 Cannot Be An EOS Function Since Low MULT=A0 Already
;------------------------------------------------------------
?tPtChg?                    := GRCMDS+28                ;A0h 'PtChg'
?tPXOn?                     := GRCMDS+29                ;A1h
?tPXOff?                    := GRCMDS+30                ;A2h
?tPXChg?                    := GRCMDS+31                ;A3h
?tShade?                    := GRCMDS+32                ;A4h 'Shade'
?tCircl?                    := GRCMDS+33                ;A5h 'Circl'
?tHorz?                     := GRCMDS+34                ;A6h 'HORIZONTAL'
?tTanLn?                    := GRCMDS+35                ;A7h 'TanLn'
?tDrInv?                    := GRCMDS+36                ;A8h 'DrInv_'
?tDrawF?                    := GRCMDS+37                ;A9h 'DrawF_'
?tVarStrng?                 := 0AAh

;Functions with No Arguments                                    
;--------------------------------------------------
?NOARG?                     := 0ABh
?tRand?                     := NOARG                    ;ABh 'rand'
?tPi?                       := NOARG+1                  ;ACh  Lpi
?tGetKey?                   := NOARG+2                  ;ADh 'getKy'
?tAPost?                    := tGetKey+1                ;APOSTROPHY
?tQuest?                    := tAPost+1                 ;QUESTION MARK
?UNARY?                     := tQuest+1                 ;B0h
?tChs?                      := UNARY                    ;B0h
?tInt?                      := UNARY+1                  ;B1h
?tAbs?                      := UNARY+2                  ;B2h
?tDet?                      := UNARY+3                  ;B3h
?tIdent?                    := UNARY+4                  ;B4h
?tDim?                      := UNARY+5                  ;B5h
?tSum?                      := UNARY+6                  ;B6h
?tProd?                     := UNARY+7                  ;B7h
?tNot?                      := UNARY+8                  ;B8h
?tIPart?                    := UNARY+9                  ;B9h
?tFPart?                    := UNARY+10                 ;BAh

;New 2 Byte Tokens
;------------------------------------------
?t2ByteTok?                 := 0BBh
?UNARYLR?                   := UNARY+12
?tSqrt?                     := UNARYLR                  ;BCh
?tCubRt?                    := UNARYLR+1                ;BDh
?tLn?                       := UNARYLR+2                ;BEh
?tExp?                      := UNARYLR+3                ;BFh
?tLog?                      := UNARYLR+4                ;C0h
?tALog?                     := UNARYLR+5                ;C1h
?tSin?                      := UNARYLR+6                ;C2h
?tASin?                     := UNARYLR+7                ;C3h
?tCos?                      := UNARYLR+8                ;C4h
?tACos?                     := UNARYLR+9                ;C5h
?tTan?                      := UNARYLR+10               ;C6h
?tATan?                     := UNARYLR+11               ;C7h
?tSinH?                     := UNARYLR+12               ;C8h
?tASinH?                    := UNARYLR+13               ;C9h
?tCoshH?                    := UNARYLR+14               ;CAh
?tACosH?                    := UNARYLR+15               ;CBh
?tTanH?                     := UNARYLR+16               ;CCh
?tATanH?                    := UNARYLR+17               ;CDh

;Some Programming Commands
;------------------------------------------------------
?PROGTOK?                   := UNARYLR+18
?tIf?                       := PROGTOK                  ;CEh
?tThen?                     := PROGTOK+1                ;CFh
?tElse?                     := PROGTOK+2                ;D0h
?tWhile?                    := PROGTOK+3                ;D1h
?tRepeat?                   := PROGTOK+4                ;D2h
?tFor?                      := PROGTOK+5                ;D3h
?tEnd?                      := PROGTOK+6                ;D4h
?tReturn?                   := PROGTOK+7                ;D5h
?tLbl?                      := PROGTOK+8                ;D6h 'Lbl_'
?tGoto?                     := PROGTOK+9                ;D7h 'Goto_'
?tPause?                    := PROGTOK+10               ;D8h 'Pause_'
?tStop?                     := PROGTOK+11               ;D9h 'Stop'
?tISG?                      := PROGTOK+12               ;DAh 'IS>'
?tDSL?                      := PROGTOK+13               ;DBh 'DS<'
?tInput?                    := PROGTOK+14               ;DCh 'Input_'
?tPrompt?                   := PROGTOK+15               ;DDh 'Prompt_'
?tDisp?                     := PROGTOK+16               ;DEh 'Disp_'
?tDispG?                    := PROGTOK+17               ;DFh 'DispG'
?tOutput?                   := PROGTOK+18               ;E0h 'Outpt'
?tClLCD?                    := PROGTOK+19               ;E1h 'ClLCD'
?tConst?                    := PROGTOK+20               ;E2h 'Fill'
?tSortA?                    := PROGTOK+21               ;E3h 'sortA_'
?tSortD?                    := PROGTOK+22               ;E4h 'sortD_'
?tDispTab?                  := PROGTOK+23               ;E5h 'Disp Table
?tMenu?                     := PROGTOK+24               ;E6h 'Menu'
?tSendMBL?                  := PROGTOK+25               ;E7h 'SEND'
?tGetMBL?                   := PROGTOK+26               ;E8h 'GET'

;Stat Plot Commands
;------------------------------------------------------
?statPCmd?                  := PROGTOK+27
?tPlotOn?                   := statPCmd                 ;E9h ' PLOTSON'
?tPlotOff?                  := statPCmd+1               ;EAh ' PLOTSOFF
?tListName?                 := 0EBh                     ;LIST DESIGNATOR
?tPlot1?                    := 0ECh
?tPlot2?                    := 0EDh
?tPlot3?                    := 0EEh
?tUnused01?                 := 0EFh                     ;available?
?tPower?                    := 0F0h                     ;' xor '
?tXRoot?                    := 0F1h                     ;LsupX,Lroot
?STATCMD?                   := 0F2h
?tOneVar?                   := STATCMD                  ;F2h 'OneVar_'
?tTwoVar?                   := STATCMD+1                ;F3h
?tLR?                       := STATCMD+2                ;F4h 'LinR(A+BX
?tLRExp?                    := STATCMD+3                ;F5h 'ExpR_'
?tLRLn?                     := STATCMD+4                ;F6h 'LnR_'
?tLRPwr?                    := STATCMD+5                ;F7h 'PwrR_'
?tMedMed?                   := STATCMD+6                ;F8h
?tQuad?                     := STATCMD+7                ;F9h
?tClrLst?                   := STATCMD+8                ;FAh 'CLEAR LIST
?tClrTbl?                   := STATCMD+9                ;FBh CLEAR TABLE
?tHist?                     := STATCMD+10               ;FCh 'Hist_'
?txyLine?                   := STATCMD+11               ;FDh 'xyline_'
?tScatter?                  := STATCMD+12               ;FEh 'Scatter_'
?tLR1?                      := STATCMD+13               ;FFh 'LINR(AX+B

;2nd Half Of Graph Format Tokens
;----------------------------------------------
;           Format settings commands
;
?GFMT?                      := 0
?tSeq?                      := GFMT                     ; 'SeqG'
?tSimulG?                   := GFMT+1                   ; 'SimulG'
?tPolarG?                   := GFMT+2                   ; 'PolarGC'
?tRectG?                    := GFMT+3                   ; 'RectGC'
?tCoordOn?                  := GFMT+4                   ; 'CoordOn'
?tCoordOff?                 := GFMT+5                   ; 'CoordOff'
?tDrawLine?                 := GFMT+6                   ; 'DrawLine'
?tDrawDot?                  := GFMT+7                   ; 'DrawDot'
?tAxisOn?                   := GFMT+8                   ; 'AxesOn'
?tAxisOff?                  := GFMT+9                   ; 'AxesOff'
?tGridOn?                   := GFMT+10                  ; 'GridOn'
?tGridOff?                  := GFMT+11                  ; 'GridOff'
?tLblOn?                    := GFMT+12                  ; 'LabelOn'
?tLblOff?                   := GFMT+13                  ; 'LabelOff'
?tWebOn?                    := GFMT+14                  ; 'WebOn'
?tWebOff?                   := GFMT+15                  ; 'WebOFF'
?tuv?                       := GFMT+16                  ; U vs V
?tvw?                       := GFMT+17                  ; V vs W
?tuw?                       := GFMT+18                  ; U vs W

;2nd Half Of User Matrix Tokens
;-------------------------------------
?tMatA?                     := 00h                      ;MAT A
?tMatB?                     := 01h                      ;MAT B
?tMatC?                     := 02h                      ;MAT C
?tMatD?                     := 03h                      ;MAT D
?tMatE?                     := 04h                      ;MAT E
?tMatF?                     := 05h                      ;MAT F
?tMatG?                     := 06h                      ;MAT G
?tMatH?                     := 07h                      ;MAT H
?tMatI?                     := 08h                      ;MAT I
?tMatJ?                     := 09h                      ;MAT J

;2nd Half Of User List Tokens
;--------------------------------------
?tL1?                       := 00h                      ;LIST 1
?tL2?                       := 01h                      ;LIST 2
?tL3?                       := 02h                      ;LIST 3
?tL4?                       := 03h                      ;LIST 4
?tL5?                       := 04h                      ;LIST 5
?tL6?                       := 05h                      ;LIST 6

;2nd Half Of User Equation Tokens
;----------------------------------
;  "Y" EQUATIONS HAVE BIT 4 SET
;
?tY1?                       := 10h                      ;Y1
?tY2?                       := 11h                      ;Y2
?tY3?                       := 12h                      ;Y3
?tY4?                       := 13h                      ;Y4
?tY5?                       := 14h                      ;Y5
?tY6?                       := 15h                      ;Y6
?tY7?                       := 16h                      ;Y7
?tY8?                       := 17h                      ;Y8
?tY9?                       := 18h                      ;Y9
?tY0?                       := 19h                      ;Y0

;Param Equations Have Bit 5 Set
;-----------------------------------
?tX1T?                      := 20h                      ;X1t
?tY1T?                      := 21h                      ;Y1t
?tX2T?                      := 22h                      ;X2t
?tY2T?                      := 23h                      ;Y2t
?tX3T?                      := 24h                      ;X3t
?tY3T?                      := 25h                      ;Y3t
?tX4T?                      := 26h                      ;X4t
?tY4T?                      := 27h                      ;Y4t
?tX5T?                      := 28h                      ;X5t
?tY5T?                      := 29h                      ;Y5t
?tX6T?                      := 2Ah                      ;X6t
?tY6T?                      := 2Bh                      ;Y6t

;Polar Equations Have Bit 6 Set
;----------------------------------
?tR1?                       := 40h                      ;R1
?tR2?                       := 41h                      ;R2
?tR3?                       := 42h                      ;R3
?tR4?                       := 43h                      ;R4
?tR5?                       := 44h                      ;R5
?tR6?                       := 45h                      ;R6

;Recursion Equations Have Bit 7 Set
;----------------------------------
?tun?                       := 80h                      ;Un
?tvn?                       := 81h                      ;Vn
?twn?                       := 82h                      ;Wn

;2nd Half Of User Picture Tokens
;------------------------------------
?tPic1?                     := 00h                      ;PIC1
?tPic2?                     := 01h                      ;PIC2
?tPic3?                     := 02h                      ;PIC3
?tPic4?                     := 03h                      ;PIC4
?tPic5?                     := 04h                      ;PIC5
?tPic6?                     := 05h                      ;PIC6
?tPic7?                     := 06h                      ;PIC7
?tPic8?                     := 07h                      ;PIC8
?tPic9?                     := 08h                      ;PIC9
?tPic0?                     := 09h                      ;PIC0

;2nd Half Of User Graph Database Tokens
;--------------------------------------
?tGDB1?                     := 00h                      ;GDB1
?tGDB2?                     := 01h                      ;GDB2
?tGDB3?                     := 02h                      ;GDB3
?tGDB4?                     := 03h                      ;GDB4
?tGDB5?                     := 04h                      ;GDB5
?tGDB6?                     := 05h                      ;GDB6
?tGDB7?                     := 06h                      ;GDB7
?tGDB8?                     := 07h                      ;GDB8
?tGDB9?                     := 08h                      ;GDB9
?tGDB0?                     := 09h                      ;GDB0

;2nd Half Of String Vars
;------------------------------
?tStr1?                     := 00h
?tStr2?                     := 01h
?tStr3?                     := 02h
?tStr4?                     := 03h
?tStr5?                     := 04h
?tStr6?                     := 05h
?tStr7?                     := 06h
?tStr8?                     := 07h
?tStr9?                     := 08h
?tStr0?                     := 09h

;2nd Half Of System Output Only Variables
;-----------------------------------------------------------------
;OPEN                                                                               equ 00h
?tRegEq?                    := 01h                      ;REGRESSION EQUATION
?tStatN?                    := 02h                      ;STATISTICS N
?tXMean?                    := 03h                      ;X MEAN
?tSumX?                     := 04h                      ;SUM(X)
?tSumXSqr?                  := 05h                      ;SUM(X xor 2)
?tStdX?                     := 06h                      ;STANDARD DEV X
?tStdPX?                    := 07h                      ;STANDARD DEV POP X
?tMinX?                     := 08h                      ;Min X VALUE
?tMaxX?                     := 09h                      ;Max X VALUE
?tMinY?                     := 0Ah                      ;Min Y VALUE
?tMaxY?                     := 0Bh                      ;Max Y VALUE
?tYmean?                    := 0Ch                      ;Y MEAN
?tSumY?                     := 0Dh                      ;SUM(Y)
?tSumYSqr?                  := 0Eh                      ;SUM(Y xor 2)
?tStdY?                     := 0Fh                      ;STANDARD DEV Y
?tStdPY?                    := 10h                      ;STANDARD DEV POP Y
?tSumXY?                    := 11h                      ;SUM(XY)
?tCorr?                     := 12h                      ;CORRELATION
?tMedX?                     := 13h                      ;MED(X)
?tQ1?                       := 14h                      ;1ST QUADRANT OF X
?tQ3?                       := 15h                      ;3RD QUADRANT OF X
?tQuadA?                    := 16h                      ;1ST TERM OF QUAD POLY REG/ Y-INT
?tQuadB?                    := 17h                      ;2ND TERM OF QUAD POLY REG/ SLOPE
?tQuadC?                    := 18h                      ;3RD TERM OF QUAD POLY REG
?tCubeD?                    := 19h                      ;4TH TERM OF CUBIC POLY REG
?tQuartE?                   := 1Ah                      ;5TH TERM OF QUART POLY REG
?tMedX1?                    := 1Bh                      ;x1 FOR MED-MED
?tMedX2?                    := 1Ch                      ;x2 FOR MED-MED
?tMedX3?                    := 1Dh                      ;x3 FOR MED-MED
?tMedY1?                    := 1Eh                      ;y1 FOR MED-MED
?tMedY2?                    := 1Fh                      ;y2 FOR MED-MED
?tMedY3?                    := 20h                      ;y3 FOR MED-MED
?tRecurn?                   := 21h                      ;RECURSION N
?tStatP?                    := 22h
?tStatZ?                    := 23h
?tStatT?                    := 24h
?tStatChi?                  := 25h
?tStatF?                    := 26h
?tStatDF?                   := 27h
?tStatPhat?                 := 28h
?tStatPhat1?                := 29h
?tStatPhat2?                := 2Ah
?tStatMeanX1?               := 2Bh
?tStatStdX1?                := 2Ch
?tStatN1?                   := 2Dh
?tStatMeanX2?               := 2Eh
?tStatStdX2?                := 2Fh
?tStatN2?                   := 30h
?tStatStdXP?                := 31h
?tStatLower?                := 32h
?tStatUpper?                := 33h
?tStat_s?                   := 34h
?tLRSqr?                    := 35h                      ;r xor 2
?tBRSqr?                    := 36h                      ;R xor 2

;These next tokens are only used to access the data
;they are display only and the user cannot access them at all
;------------------------------------------------------------
?tF_DF?                     := 37h                      ;ANOFAV FACTOR DF
?tF_SS?                     := 38h                      ;ANOFAV FACTOR SS
?tF_MS?                     := 39h                      ;ANOFAV FACTOR MS
?tE_DF?                     := 3Ah                      ;ANOFAV ERROR DF
?tE_SS?                     := 3Bh                      ;ANOFAV ERROR SS
?tE_MS?                     := 3Ch                      ;ANOFAV ERROR MS

;2nd Half Of System Input/Output Variables
;------------------------------------------------
;      SYSTEM VARIABLE EQUATES
;
?tuXscl?                    := 0
?tuYscl?                    := 1
?tXscl?                     := 2
?tYscl?                     := 3
?tRecuru0?                  := 4                        ;U 1ST INITIAL COND
?tRecurv0?                  := 5                        ;V 1ST INITIAL COND
?tun1?                      := 6                        ;U(N-1); NOT USED
?tvn1?                      := 7                        ;V(N-1); NOT USED
?tuRecuru0?                 := 8                        ;
?tuRecurv0?                 := 9                        ;
?tXmin?                     := 0Ah
?tXmax?                     := 0Bh
?tYmin?                     := 0Ch
?tYmax?                     := 0Dh
?tTmin?                     := 0Eh
?tTmax?                     := 0Fh
?tThetaMin?                 := 10h
?tThetaMax?                 := 11h
?tuXmin?                    := 12h
?tuXmax?                    := 13h
?tuYmin?                    := 14h
?tuYmax?                    := 15h
?tuThetMin?                 := 16h
?tuThetMax?                 := 17h
?tuTmin?                    := 18h
?tuTmax?                    := 19h
?tTblMin?                   := 1Ah
?tPlotStart?                := 1Bh
?tuPlotStart?               := 1Ch
?tnMax?                     := 1Dh
?tunMax?                    := 1Eh
?tnMin?                     := 1Fh
?tunMin?                    := 20h
?tTblStep?                  := 21h
?tTStep?                    := 22h
?tThetaStep?                := 23h
?tuTStep?                   := 24h
?tuThetStep?                := 25h
?tDeltaX?                   := 26h
?tDeltaY?                   := 27h
?tXFact?                    := 28h
?tYFact?                    := 29h
?tTblInput?                 := 2Ah
?tFinN?                     := 2Bh
?tFinI?                     := 2Ch
?tFinPV?                    := 2Dh
?tFinPMT?                   := 2Eh
?tFinFV?                    := 2Fh
?tFinPY?                    := 30h
?tFinCY?                    := 31h
?tRecurw0?                  := 32h                      ;w0(1)
?tuRecurw0?                 := 33h
?tPlotStep?                 := 34h
?tuPlotStep?                := 35h
?tXres?                     := 36h
?tuXres?                    := 37h
?tRecuru02?                 := 38h                      ;u0(2)
?tuRecuru02?                := 39h
?tRecurv02?                 := 3Ch                      ;v0(2)
?tuRecurv02?                := 3Dh
?tRecurw02?                 := 3Eh                      ;w0(2)
?tuRecurw02?                := 3Fh

;2nd Byte Of t2ByteTok Tokens
;------------------------------
?tFinNPV?                   := 00h
?tFinIRR?                   := 01h
?tFinBAL?                   := 02h
?tFinPRN?                   := 03h
?tFinINT?                   := 04h
?tFinToNom?                 := 05h
?tFinToEff?                 := 06h
?tFinDBD?                   := 07h
?tLCM?                      := 08h
?tGCD?                      := 09h
?tRandInt?                  := 0Ah
?tRandBin?                  := 0Bh
?tSubStrng?                 := 0Ch
?tStdDev?                   := 0Dh
?tVariance?                 := 0Eh
?tInStrng?                  := 0Fh
?tDNormal?                  := 10h
?tInvNorm?                  := 11h
?tDT?                       := 12h
?tChI?                      := 13h
?tDF?                       := 14h
?tBINPDF?                   := 15h
?tBINCDF?                   := 16h
?tPOIPDF?                   := 17h
?tPOICDF?                   := 18h
?tGEOPDF?                   := 19h
?tGEOCDF?                   := 1Ah
?tNormalPDF?                := 1Bh
?tTPDF?                     := 1Ch
?tChiPDF?                   := 1Dh
?tFPDF?                     := 1Eh
?tRandNorm?                 := 1Fh
?tFinFPMT?                  := 20h
?tFinFI?                    := 21h
?tFinFPV?                   := 22h
?tFinFN?                    := 23h
?tFinFFV?                   := 24h
?tConj?                     := 25h
?tReal?                     := 26h
?tImag?                     := 27h
?tAngle?                    := 28h
?tCumSum?                   := 29h
?tExpr?                     := 2Ah
?tLength?                   := 2Bh
?tDeltaLst?                 := 2Ch
?tRef?                      := 2Dh
?tRRef?                     := 2Eh
?tToRect?                   := 2Fh
?tToPolar?                  := 30h
?tConste?                   := 31h
?tSinReg?                   := 32h
?tLogistic?                 := 33h
?tLinRegTTest?              := 34h
?tShadeNorm?                := 35h
?tShadeT?                   := 36h
?tShadeChi?                 := 37h
?tShadeF?                   := 38h
?tMatToLst?                 := 39h
?tLstToMat?                 := 3Ah
?tZTest?                    := 3Bh
?tTTest?                    := 3Ch
?t2SampZTest?               := 3Dh
?t1PropZTest?               := 3Eh
?t2PropZTest?               := 3Fh
?tChiTest?                  := 40h
?tZIntVal?                  := 41h
?t2SampZInt?                := 42h
?t1PropZInt?                := 43h
?t2PropZInt?                := 44h
?tGraphStyle?               := 45h
?t2SampTTest?               := 46h
?t2SampFTest?               := 47h
?tTIntVal?                  := 48h
?t2SampTInt?                := 49h
?tSetupLst?                 := 4Ah
?tFinPMTend?                := 4Bh
?tFinPMTbeg?                := 4Ch
?tRealM?                    := 4Dh
?tPolarM?                   := 4Eh
?tRectM?                    := 4Fh
?tExprOn?                   := 50h
?tExprOff?                  := 51h
?tClrAllLst?                := 52h
?tGetCalc?                  := 53h
?tDelVar?                   := 54h
?tEquToStrng?               := 55h
?tStrngToEqu?               := 56h
?tDelLast?                  := 57h
?tSelect?                   := 58h
?tANOVA?                    := 59h
?tModBox?                   := 5Ah
?tNormProb?                 := 5Bh
?tMGT?                      := 64h                      ;VERTICAL SPLIT
?tZFit?                     := 65h                      ;ZOOM FIT
?tDiag_on?                  := 66h                      ;DIANOSTIC DISPLAY ON
?tDiag_off?                 := 67h                      ;DIANOSTIC DISPLAY OFF
?tOkEnd2v0?                 := 67h                      ;end of 2byte tokens for version 0.
?tArchive?                  := 68h                      ;archive
?tUnarchive?                := 69h                      ;unarchive
?tasm?                      := 6Ah
?tasmComp?                  := 6Bh                      ;asm compile
?tasmPrgm?                  := 6Ch                      ;signifies a program is asm
?tasmCmp?                   := 6Dh                      ;asm program is compiled
?tLcapAAcute?               := 6Eh
?tLcapAGrave?               := 6Fh
?tLcapACaret?               := 70h
?tLcapADier?                := 71h
?tLaAcute?                  := 72h
?tLaGrave?                  := 73h
?tLaCaret?                  := 74h
?tLaDier?                   := 75h
?tLcapEAcute?               := 76h
?tLcapEGrave?               := 77h
?tLcapECaret?               := 78h
?tLcapEDier?                := 79h
?tLeAcute?                  := 7Ah
?tLeGrave?                  := 7Bh
?tLeCaret?                  := 7Ch
?tLeDier?                   := 7Dh
?tLcapIGrave?               := 7Fh
?tLcapICaret?               := 80h
?tLcapIDier?                := 81h
?tLiAcute?                  := 82h
?tLiGrave?                  := 83h
?tLiCaret?                  := 84h
?tLiDier?                   := 85h
?tLcapOAcute?               := 86h
?tLcapOGrave?               := 87h
?tLcapOCaret?               := 88h
?tLcapODier?                := 89h
?tLoAcute?                  := 8Ah
?tLoGrave?                  := 8Bh
?tLoCaret?                  := 8Ch
?tLoDier?                   := 8Dh
?tLcapUAcute?               := 8Eh
?tLcapUGrave?               := 8Fh
?tLcapUCaret?               := 90h
?tLcapUDier?                := 91h
?tLuAcute?                  := 92h
?tLuGrave?                  := 93h
?tLuCaret?                  := 94h
?tLuDier?                   := 95h
?tLcapCCed?                 := 96h
?tLcCed?                    := 97h
?tLcapNTilde?               := 98h
?tLnTilde?                  := 99h
?tLaccent?                  := 9Ah
?tLgrave?                   := 9Bh
?tLdieresis?                := 9Ch
?tLquesDown?                := 9Dh
?tLexclamDown?              := 9Eh
?tLalpha?                   := 9Fh
?tLbeta?                    := 0A0h
?tLgamma?                   := 0A1h
?tLcapDelta?                := 0A2h
?tLdelta?                   := 0A3h
?tLepsilon?                 := 0A4h
?tLlambda?                  := 0A5h
?tLmu?                      := 0A6h
?tLpi?                      := 0A7h
?tLrho?                     := 0A8h
?tLcapSigma?                := 0A9h
?tLphi?                     := 0ABh
?tLcapOmega?                := 0ACh
?tLphat?                    := 0ADh
?tLchi?                     := 0AEh
?tLstatF?                   := 0AFh
?tLa?                       := 0B0h
?tLb?                       := 0B1h
?tLc?                       := 0B2h
?tLd?                       := 0B3h
?tLsmalle?                  := 0B4h
?tLf?                       := 0B5h
?tLsmallg?                  := 0B6h
?tLh?                       := 0B7h
?tLi?                       := 0B8h
?tLj?                       := 0B9h
?tLk?                       := 0BAh
?tLl?                       := 0BCh
?tLm?                       := 0BDh
?tLsmalln?                  := 0BEh
?tLo?                       := 0BFh
?tLp?                       := 0C0h
?tLq?                       := 0C1h
?tLsmallr?                  := 0C2h
?tLs?                       := 0C3h
?tLsmallt?                  := 0C4h
?tLu?                       := 0C5h
?tLv?                       := 0C6h
?tLw?                       := 0C7h
?tLx?                       := 0C8h
?tLy?                       := 0C9h
?tLz?                       := 0CAh
?tLsigma?                   := 0CBh
?tLtau?                     := 0CCh
?tLcapIAcute?               := 0CDh
?tGarbagec?                 := 0CEh
?LastToken?                 := 0CEh                     ;tLAST TOKEN IN THIS VERSION...

;Data Type Equates                                                    
;---------------------------------------------------------------------
?RealObj?                   := 0
?ListObj?                   := 1
?MatObj?                    := 2
?EquObj?                    := 3
?StrngObj?                  := 4
?ProgObj?                   := 5
?ProtProgObj?               := 6
?PictObj?                   := 7
?GDBObj?                    := 8
?UnknownObj?                := 9
?UnknownEquObj?             := 0Ah
?NewEquObj?                 := 0Bh
?CplxObj?                   := 0Ch
?CListObj?                  := 0Dh
?UndefObj?                  := 0Eh
?WindowObj?                 := 0Fh
?ZStoObj?                   := 10h
?TblRngObj?                 := 11h
?LCDObj?                    := 12h
?BackupObj?                 := 13h
?AppObj?                    := 14h                      ;application, only used in menus/link
?AppVarObj?                 := 15h                      ;application variable
?TempProgObj?               := 16h                      ;program, home deletes when finished
?GroupObj?                  := 17h                      ;group.

;I/O Equates                                                          
;---------------------------------------------------
?D0D1_bits?                 := 03h
?D0LD1L?                    := 03h
?D0LD1H?                    := 01h
?D0HD1L?                    := 02h
?D0HD1H?                    := 00h
?bport?                     := 0                        ;4-bit link port (I/O) 

;Device Codes
;-----------------------------------------------------------------
?TI82DEV?                   := 82h
?PC82DEV?                   := 02h
?MAC82DEV?                  := 12h
?TI83FDEV?                  := 73h
?LINK83FDEV?                := 23h
?TI83DEV?                   := 83h
?PC83DEV?                   := 03h
?MAC83DEV?                  := 13h
?TI85DEV?                   := 95h                      ;different than real 85 so me talk
?PC85DEV?                   := 05h
?MAC85DEV?                  := 15h
?TI73DEV?                   := 74h                      ;device x3 is always an 83
?PC73DEV?                   := 07h
?MAC73DEV?                  := 17h
?LINK73FDEV?                := 23h
?PC83FDEV?                  := 23h

;System Error Codes                                                  
;-----------------------------------------------------------
?E_EDITF?                   := 7                        ;allow re-entering application
?E_EDIT?                    := 1 shl E_EDITF
?E_Mask?                    := 7Fh
?E_Overflow?                := 1+E_EDIT
?E_DivBy0?                  := 2+E_EDIT
?E_SingularMat?             := 3+E_EDIT
?E_Domain?                  := 4+E_EDIT
?E_Increment?               := 5+E_EDIT
?E_Break?                   := 6+E_EDIT
?E_NonReal?                 := 7+E_EDIT
?E_Syntax?                  := 8+E_EDIT
?E_DataType?                := 9+E_EDIT
?E_Argument?                := 10+E_EDIT
?E_DimMismatch?             := 11+E_EDIT
?E_Dimension?               := 12+E_EDIT
?E_Undefined?               := 13+E_EDIT
?E_Memory?                  := 14+E_EDIT
?E_Invalid?                 := 15+E_EDIT
?E_IllegalNest?             := 16+E_EDIT
?E_Bound?                   := 17+E_EDIT
?E_GraphRange?              := 18+E_EDIT
?E_Zoom?                    := 19+E_EDIT
?E_Label?                   := 20
?E_Stat?                    := 21
?E_Solver?                  := 22+E_EDIT
?E_Singularity?             := 23+E_EDIT
?E_SignChange?              := 24+E_EDIT
?E_Iterations?              := 25+E_EDIT
?E_BadGuess?                := 26+E_EDIT
?E_StatPlo?                 := 27
?E_TolTooSmall?             := 28+E_EDIT
?E_Reserved?                := 29+E_EDIT
?E_Mode?                    := 30+E_EDIT
?E_LnkErr?                  := 31+E_EDIT
?E_LnkMemErr?               := 32+E_EDIT
?E_LnkTransErr?             := 33+E_EDIT
?E_LnkDupErr?               := 34+E_EDIT
?E_LnkMemFull?              := 35+E_EDIT
?E_Unknown?                 := 36+E_EDIT
?E_Scale?                   := 37+E_EDIT
?E_IdNotFound?              := 38
?E_NoMode?                  := 39+E_EDIT
?E_Validation?              := 40
?E_Length?                  := 41+E_EDIT
?E_Application?             := 42+E_EDIT
?E_AppErr1?                 := 43+E_EDIT
?E_AppErr2?                 := 44+E_EDIT
?E_ExpiredApp?              := 45
?E_BadAdd?                  := 46
?E_Archived?                := 47+E_EDIT
?E_Version?                 := 48
?E_ArchFull?                := 49
?E_Variable?                := 50+E_EDIT
?E_Duplicate?               := 51+E_EDIT
?HigErrNum?                 := 51
;Obsolete error numbers 34  ;first LINK error
?E_LinkIOChkSum?            := 34
?E_LinkIOTimeOut?           := 35
?E_LinkIOBusy?              := 36
?E_LinkIOVer?               := 37

;Equates To RAM Locations For Stat Vars
;----------------------------------------------------------------
?FPLEN?                     := 9                        ;Length of a floating-point number.
?StatN?                     := statVars
?XMean?                     := StatN + FPLEN
?SumX?                      := XMean + FPLEN
?SumXSqr?                   := SumX + FPLEN
?StdX?                      := SumXSqr + FPLEN
?StdPX?                     := StdX + FPLEN
?MinX?                      := StdPX + FPLEN
?MaxX?                      := MinX + FPLEN
?MinY?                      := MaxX + FPLEN
?MaxY?                      := MinY + FPLEN
?YMean?                     := MaxY + FPLEN
?SumY?                      := YMean + FPLEN
?SumYSqr?                   := SumY + FPLEN
?StdY?                      := SumYSqr + FPLEN
?StdPY?                     := StdY + FPLEN
?SumXY?                     := StdPY + FPLEN
?Corr?                      := SumXY + FPLEN
?MedX?                      := Corr + FPLEN
?Q1?                        := MedX + FPLEN
?Q3?                        := Q1 + FPLEN
?QuadA?                     := Q3 + FPLEN
?QuadB?                     := QuadA + FPLEN
?QuadC?                     := QuadB + FPLEN
?CubeD?                     := QuadC + FPLEN
?QuartE?                    := CubeD + FPLEN
?MedX1?                     := QuartE + FPLEN
?MedX2?                     := MedX1 + FPLEN
?MedX3?                     := MedX2 + FPLEN
?MedY1?                     := MedX3 + FPLEN
?MedY2?                     := MedY1 + FPLEN
?MedY3?                     := MedY2 + FPLEN
?PStat?                     := MedY3 + 2*FPLEN
?ZStat?                     := PStat + FPLEN
?TStat?                     := ZStat + FPLEN
?ChiStat?                   := TStat + FPLEN
?FStat?                     := ChiStat + FPLEN
?DF?                        := FStat + FPLEN
?Phat?                      := DF + FPLEN
?Phat1?                     := Phat + FPLEN
?Phat2?                     := Phat1 + FPLEN
?MeanX1?                    := Phat2 + FPLEN
?StdX1?                     := MeanX1 + FPLEN
?StatN1?                    := StdX1 + FPLEN
?MeanX2?                    := StatN1 + FPLEN
?StdX2?                     := MeanX2 + FPLEN
?StatN2?                    := StdX2 + FPLEN
?StdXP2?                    := StatN2 + FPLEN
?SLower?                    := StdXP2 + FPLEN
?SUpper?                    := SLower + FPLEN
?SStat?                     := SUpper + FPLEN
?F_DF?                      := anovaf_vars
?F_SS?                      := F_DF + FPLEN
?F_MS?                      := F_SS + FPLEN
?E_DF?                      := F_MS + FPLEN
?E_SS?                      := E_DF + FPLEN
?E_MS?                      := E_SS + FPLEN
end namespace
