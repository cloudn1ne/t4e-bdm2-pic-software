#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=usb/src/usb_cdc.c usb/src/usb_hid.c usb/src/usb.c system.c user.c configuration_bits.c interrupts.c main.c usb_descriptors.c mpc_bdm.c gdb_stub.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/usb/src/usb_cdc.p1 ${OBJECTDIR}/usb/src/usb_hid.p1 ${OBJECTDIR}/usb/src/usb.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/usb_descriptors.p1 ${OBJECTDIR}/mpc_bdm.p1 ${OBJECTDIR}/gdb_stub.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/usb/src/usb_cdc.p1.d ${OBJECTDIR}/usb/src/usb_hid.p1.d ${OBJECTDIR}/usb/src/usb.p1.d ${OBJECTDIR}/system.p1.d ${OBJECTDIR}/user.p1.d ${OBJECTDIR}/configuration_bits.p1.d ${OBJECTDIR}/interrupts.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/usb_descriptors.p1.d ${OBJECTDIR}/mpc_bdm.p1.d ${OBJECTDIR}/gdb_stub.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/usb/src/usb_cdc.p1 ${OBJECTDIR}/usb/src/usb_hid.p1 ${OBJECTDIR}/usb/src/usb.p1 ${OBJECTDIR}/system.p1 ${OBJECTDIR}/user.p1 ${OBJECTDIR}/configuration_bits.p1 ${OBJECTDIR}/interrupts.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/usb_descriptors.p1 ${OBJECTDIR}/mpc_bdm.p1 ${OBJECTDIR}/gdb_stub.p1

# Source Files
SOURCEFILES=usb/src/usb_cdc.c usb/src/usb_hid.c usb/src/usb.c system.c user.c configuration_bits.c interrupts.c main.c usb_descriptors.c mpc_bdm.c gdb_stub.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1459
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/usb/src/usb_cdc.p1: usb/src/usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb_cdc.p1  usb/src/usb_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb_cdc.d ${OBJECTDIR}/usb/src/usb_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/src/usb_hid.p1: usb/src/usb_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb_hid.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb_hid.p1  usb/src/usb_hid.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb_hid.d ${OBJECTDIR}/usb/src/usb_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/src/usb.p1: usb/src/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb.p1  usb/src/usb.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb.d ${OBJECTDIR}/usb/src/usb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_descriptors.p1: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb_descriptors.p1  usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb_descriptors.d ${OBJECTDIR}/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mpc_bdm.p1: mpc_bdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mpc_bdm.p1.d 
	@${RM} ${OBJECTDIR}/mpc_bdm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/mpc_bdm.p1  mpc_bdm.c 
	@-${MV} ${OBJECTDIR}/mpc_bdm.d ${OBJECTDIR}/mpc_bdm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mpc_bdm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gdb_stub.p1: gdb_stub.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gdb_stub.p1.d 
	@${RM} ${OBJECTDIR}/gdb_stub.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/gdb_stub.p1  gdb_stub.c 
	@-${MV} ${OBJECTDIR}/gdb_stub.d ${OBJECTDIR}/gdb_stub.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gdb_stub.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/usb/src/usb_cdc.p1: usb/src/usb_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb_cdc.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb_cdc.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb_cdc.p1  usb/src/usb_cdc.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb_cdc.d ${OBJECTDIR}/usb/src/usb_cdc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb_cdc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/src/usb_hid.p1: usb/src/usb_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb_hid.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb_hid.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb_hid.p1  usb/src/usb_hid.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb_hid.d ${OBJECTDIR}/usb/src/usb_hid.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb_hid.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb/src/usb.p1: usb/src/usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/usb/src" 
	@${RM} ${OBJECTDIR}/usb/src/usb.p1.d 
	@${RM} ${OBJECTDIR}/usb/src/usb.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb/src/usb.p1  usb/src/usb.c 
	@-${MV} ${OBJECTDIR}/usb/src/usb.d ${OBJECTDIR}/usb/src/usb.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb/src/usb.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/system.p1: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.p1.d 
	@${RM} ${OBJECTDIR}/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/system.p1  system.c 
	@-${MV} ${OBJECTDIR}/system.d ${OBJECTDIR}/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/user.p1: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.p1.d 
	@${RM} ${OBJECTDIR}/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/user.p1  user.c 
	@-${MV} ${OBJECTDIR}/user.d ${OBJECTDIR}/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/configuration_bits.p1: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/configuration_bits.p1  configuration_bits.c 
	@-${MV} ${OBJECTDIR}/configuration_bits.d ${OBJECTDIR}/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/interrupts.p1: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.p1.d 
	@${RM} ${OBJECTDIR}/interrupts.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupts.p1  interrupts.c 
	@-${MV} ${OBJECTDIR}/interrupts.d ${OBJECTDIR}/interrupts.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupts.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usb_descriptors.p1: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/usb_descriptors.p1  usb_descriptors.c 
	@-${MV} ${OBJECTDIR}/usb_descriptors.d ${OBJECTDIR}/usb_descriptors.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usb_descriptors.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mpc_bdm.p1: mpc_bdm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mpc_bdm.p1.d 
	@${RM} ${OBJECTDIR}/mpc_bdm.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/mpc_bdm.p1  mpc_bdm.c 
	@-${MV} ${OBJECTDIR}/mpc_bdm.d ${OBJECTDIR}/mpc_bdm.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mpc_bdm.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/gdb_stub.p1: gdb_stub.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/gdb_stub.p1.d 
	@${RM} ${OBJECTDIR}/gdb_stub.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/gdb_stub.p1  gdb_stub.c 
	@-${MV} ${OBJECTDIR}/gdb_stub.d ${OBJECTDIR}/gdb_stub.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/gdb_stub.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD)  -odist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.map  --double=24 --float=24 --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=pro -P -N255 --warn=0 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,+psect,+class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD)  -odist/${CND_CONF}/${IMAGE_TYPE}/BDM2USB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
