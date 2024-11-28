#ifndef CONFIG_H
#define CONFIG_H

#define LOAD 0
#define USED 1
#define VUSED 2
#define AVAILABLE 3
#define VAVAILABLE 4

// DO NOT EDIT ALL PREVIOUS DEFINES
/*********************

CPU setion for graph

***********************/
#define CPU_ELEMENT FLOAD // if core have 2 thread, will be showing first thread load
//#define CPU_ELEMENT SLOAD // if core have 2 thread, will be showing second thread load
//#define CPU_ELEMENT AVGLOAD // if core have 2 thread, will be showing average thread load
//#define CPU_ELEMENT TEMP
//#define CPU_ELEMENT FREQ
//#define CPU_ELEMENT VOLT

/*********************

RAM setion for graph

***********************/
#define RAM_FIRST_ELEMENT LOAD
//#define RAM_FIRST_ELEMENT USED
//#define RAM_FIRST_ELEMENT VUSED
//#define RAM_FIRST_ELEMENT AVAILABLE
//#define RAM_FIRST_ELEMENT VAVAILABLE

//#define RAM_SECOND_ELEMENT LOAD
#define RAM_SECOND_ELEMENT USED
//#define RAM_SECOND_ELEMENT VUSED
//#define RAM_SECOND_ELEMENT AVAILABLE
//#define RAM_SECOND_ELEMENT VAVAILABLE

//#define RAM_THIRD_ELEMENT LOAD
//#define RAM_THIRD_ELEMENT USED
//#define RAM_THIRD_ELEMENT VUSED
#define RAM_THIRD_ELEMENT AVAILABLE
//#define RAM_THIRD_ELEMENT VAVAILABLE

/*********************

HOME setion for graph

***********************/
#define HEADER_TITLE "Resource Monitor Project by ID" //change string here for home header text (no more than 34 characters with "space")

#endif