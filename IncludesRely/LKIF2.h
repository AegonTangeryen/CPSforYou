#pragma once

#ifdef LKIF2_EXPORTS
#define EXP __declspec(dllexport)
#else
#define EXP __declspec(dllimport)
#endif

#include "Winsock2.h"

// Return Code List
typedef enum {	
	RC_OK = 0x0000,				// The operation is completed successfully.
	///////////////////////////////////////////////
	// Communication error from controller notification
	//
	RC_NAK_COMMAND = 0x1001,	// Command error
	RC_NAK_COMMAND_LENGTH,		// Command length error
	RC_NAK_TIMEOUT,				// Timeout
	RC_NAK_CHECKSUM,			// Check sum error
	RC_NAK_INVALID_STATE,		// Status error
	RC_NAK_OTHER,				// Other error
	RC_NAK_PARAMETER,			// Parameter error
	RC_NAK_OUT_STAGE,			// OUT calculation count limitation error
	RC_NAK_OUT_HEAD_NUM,		// No. of used head/OUT over error
	RC_NAK_OUT_INVALID_CALC,	// OUT which cannot be used for calculation was specified for calculation.
	RC_NAK_OUT_VOID,			// OUT which specified for calculation is not found.
	RC_NAK_INVALID_CYCLE,		// Unavailable sampling cycle
	RC_NAK_CTRL_ERROR,			// Main unit error
	RC_NAK_SRAM_ERROR,			// Setting value error
	///////////////////////////////////////////////
	// Communication DLL error notification
	//
	RC_ERR_OPEN_DEVICE = 0x2000,// Opening the device failed.
	RC_ERR_NO_DEVICE,			// The device is not open.
	RC_ERR_SEND,				// Command sending error
	RC_ERR_RECEIVE,				// Response receiving error
	RC_ERR_TIMEOUT,				// Timeout
	RC_ERR_NODATA,				// No data
	RC_ERR_NOMEMORY,			// No free memory
	
	RC_ERR_DISCONNECT,			// Cable disconnection suspected
	RC_ERR_UNKNOWN,				// Undefined error
} RC;	

// Measurement value structures
typedef enum {	
	LKIF_FLOATRESULT_VALID,			// valid data
	LKIF_FLOATRESULT_RANGEOVER_P,	// over range at positive (+) side
	LKIF_FLOATRESULT_RANGEOVER_N,	// over range at negative (-) side
	LKIF_FLOATRESULT_WAITING,		// Wait for comparator result
	LKIF_FLOATRESULT_ALARM,			// alarm
	LKIF_FLOATRESULT_INVALID,		// Invalid (error, etc.)
} LKIF_FLOATRESULT;	

// Set ABLE
typedef enum {
	LKIF_ABLEMODE_AUTO,				// AUTO
	LKIF_ABLEMODE_MANUAL,			// manual
} LKIF_ABLEMODE;

// Set Measurement Mode
typedef enum {
	LKIF_MEASUREMODE_NORMAL,						// normal
	LKIF_MEASUREMODE_HALF_T,						// translucent object
	LKIF_MEASUREMDOE_TRAN_1,						// transparent object
	LKIF_MEASUREMODE_TRAN_2,						// transparent object 2
	LKIF_MEASUREMODE_MRS,							// multireflective object
	LKIF_MEASUREMODE_OPAQUE =LKIF_MEASUREMODE_MRS,	// Semi opaque object
} LKIF_MEASUREMODE;

// Set Basic Point
typedef enum {
	LKIF_BASICPOINT_NEAR,			// NEAR
	LKIF_BASICPOINT_FAR,			// FAR
} LKIF_BASICPOINT;

// Set Mounting Mode
typedef enum {
	LKIF_REFLECTIONMODE_DIFFUSION,	// diffuse reflection
	LKIF_REFLECTIONMODE_MIRROR,		// specular reflection
} LKIF_REFLECTIONMODE;

// Set Median
typedef enum {
	LKIF_MEDIAN_OFF,				// OFF
	LKIF_MEDIAN_7,					// 7 point
	LKIF_MEDIAN_15,					// 15 point
	LKIF_MEDIAN_31,					// 31 point
} LKIF_MEDIAN;

// Set LASER CTRL group.
typedef enum {
	LKIF_LASER_CTRL_GROUP_1,		// LASER CTRL 1
	LKIF_LASER_CTRL_GROUP_2,		// LASER CTRL 2
} LKIF_LASER_CTRL_GROUP;

// Set a range.
typedef enum {
	LKIF_RANGE_CENTER,				// CENTER
	LKIF_RANGE_FAR,					// FAR
} LKIF_RANGE;

// Set Mutual Interference Prevention Group
typedef enum {
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP_A,	// Group A
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP_B,	// Group B
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP_C,	// Group C
} LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP;

// Set calculation method.
typedef enum {
	LKIF_CALCMETHOD_HEADA,					// head A
	LKIF_CALCMETHOD_HEADB,					// head B
	LKIF_CALCMETHOD_HEAD_HEADA_PLUS_HEADB,	// head A+head B
	LKIF_CALCMETHOD_HEAD_HEADA_MINUS_HEADB,	// head A-head B
	LKIF_CALCMETHOD_HEAD_HEADA_TRANSPARENT,	// head A transparent object
	LKIF_CALCMETHOD_HEAD_HEADB_TRANSPARENT,	// head B transparent object

	LKIF_CALCMETHOD_HEAD = 0,	// head
	LKIF_CALCMETHOD_OUT,		// OUT
	LKIF_CALCMETHOD_ADD,		// ADD
	LKIF_CALCMETHOD_SUB,		// SUB
	LKIF_CALCMETHOD_AVE,		// AVE
	LKIF_CALCMETHOD_PP,			// P-P
	LKIF_CALCMETHOD_MAX,		// MAX
	LKIF_CALCMETHOD_MIN,		// MIN
} LKIF_CALCMETHOD;

// Set Target Surface
typedef enum {
	LKIF_CALCTARGET_PEAK_1,		// peak 1
	LKIF_CALCTARGET_PEAK_2,		// peak 2
	LKIF_CALCTARGET_PEAK_3,		// peak 3
	LKIF_CALCTARGET_PEAK_4,		// peak 4
	LKIF_CALCTARGET_PEAK_1_2,	// peak 1-peak 2
	LKIF_CALCTARGET_PEAK_1_3,	// peak 1-peak 3
	LKIF_CALCTARGET_PEAK_1_4,	// peak 1-peak 4
	LKIF_CALCTARGET_PEAK_2_3,	// peak 2-peak 3
	LKIF_CALCTARGET_PEAK_2_4,	// peak 2-peak 4
	LKIF_CALCTARGET_PEAK_3_4,	// peak 3-peak 4
} LKIF_CALCTARGET;

// Set Filter Mode
typedef enum {
	LKIF_FILTERMODE_MOVING_AVERAGE,			// moving average
	LKIF_FILTERMODE_LOWPASS,				// low pass filter
	LKIF_FILTERMODE_HIGHPASS,				// high pass filter
} LKIF_FILTERMODE;

// Specify the filter parameter. (The number of averaging for moving average, or the cutoff frequency for LPF/HPF.) 

typedef enum{
	LKIF_FILTERPARA_AVE_1 = 0,		// 1 time
	LKIF_FILTERPARA_AVE_4,			// 4 times
	LKIF_FILTERPARA_AVE_16,			// 16 times
	LKIF_FILTERPARA_AVE_64,			// 64 times
	LKIF_FILTERPARA_AVE_256,		// 256 times
	LKIF_FILTERPARA_AVE_1024,		// 1024 times
	LKIF_FILTERPARA_AVE_4096,		// 4096 times
	LKIF_FILTERPARA_AVE_16384,		// 16384 times
	LKIF_FILTERPARA_AVE_65536,		// 65536 times
	LKIF_FILTERPARA_AVE_262144,		// 262144 times
	
	LKIF_FILTERPARA_COFF_3000 = 0,	// 3000Hz
	LKIF_FILTERPARA_COFF_1000,		// 1000Hz
	LKIF_FILTERPARA_COFF_300,		// 300Hz
	LKIF_FILTERPARA_COFF_100,		// 100Hz
	LKIF_FILTERPARA_COFF_30,		// 30Hz
	LKIF_FILTERPARA_COFF_10,		// 10Hz
	LKIF_FILTERPARA_COFF_3,			// 3Hz
	LKIF_FILTERPARA_COFF_1,			// 1Hz
	LKIF_FILTERPARA_COFF_0_3,		// 0.3Hz
	LKIF_FILTERPARA_COFF_0_1,		// 0.1Hz
}LKIF_FILTERPARA;

// Set Number of Times for Averaging
typedef enum {
	LKIF_AVERAGE_1,				// 1 time
	LKIF_AVERAGE_4,				// 4 times
	LKIF_AVERAGE_16,			// 16 times
	LKIF_AVERAGE_64,			// 64 times
	LKIF_AVERAGE_256,			// 256 times
	LKIF_AVERAGE_1024,			// 1024 times
	LKIF_AVERAGE_4096,			// 4096 times
	LKIF_AVERAGE_16384,			// 16384 times
	LKIF_AVERAGE_65536,			// 65536 times
	LKIF_AVERAGE_262144,		// 262144 times
} LKIF_AVERAGE;

/// Set Cutoff Frequency
typedef enum {
	LKIF_CUTOFFFREQUENCY_3000,	// 3000Hz
	LKIF_CUTOFFFREQUENCY_1000,	// 1000Hz
	LKIF_CUTOFFFREQUENCY_300,	// 300Hz
	LKIF_CUTOFFFREQUENCY_100,	// 100Hz
	LKIF_CUTOFFFREQUENCY_30,	// 30Hz
	LKIF_CUTOFFFREQUENCY_10,	// 10Hz
	LKIF_CUTOFFFREQUENCY_3,		// 3Hz
	LKIF_CUTOFFFREQUENCY_1,		// 1Hz
	LKIF_CUTOFFFREQUENCY_0_3,	// 0.3Hz
	LKIF_CUTOFFFREQUENCY_0_1,	// 0.1Hz
} LKIF_CUTOFFFREQUENCY;

// Set Trigger Mode
typedef enum {
	LKIF_TRIGGERMODE_EXT1,		// external trigger 1
	LKIF_TRIGGERMODE_EXT2,		// external trigger 2
} LKIF_TRIGGERMODE;

// Set the Measurement Mode.
typedef enum {
	LKIF_CALCMODE_NORMAL,			// normal
	LKIF_CALCMODE_PEAKHOLD,			// peak hold
	LKIF_CALCMODE_BOTTOMHOLD,		// bottom hold
	LKIF_CALCMODE_PEAKTOPEAKHOLD,	// peak-to-peak hold
	LKIF_CALCMODE_SAMPLEHOLD,		// sample hold
	LKIF_CALCMODE_AVERAGEHOLD,		// average hold
} LKIF_CALCMODE;

// Set Minimum Display Unit
typedef enum {
	LKIF_DISPLAYUNIT_0000_01MM=0,	// 0.01mm
	LKIF_DISPLAYUNIT_000_001MM,		// 0.001mm
	LKIF_DISPLAYUNIT_00_0001MM,		// 0.0001mm
	LKIF_DISPLAYUNIT_0_00001MM,		// 0.00001mm
	LKIF_DISPLAYUNIT_00000_1UM,		// 0.1um
	LKIF_DISPLAYUNIT_0000_01UM,		// 0.01um
	LKIF_DISPLAYUNIT_000_001UM,		// 0.001um

	LKIF_DISPLAYUNIT_00000_1M_S=0,	// 0.1m/s
	LKIF_DISPLAYUNIT_0000_01M_S,	// 0.01m/s
	LKIF_DISPLAYUNIT_000_001M_S,	// 0.001m/s
	LKIF_DISPLAYUNIT_00000_1MM_S,	// 0.1mm/s
	LKIF_DISPLAYUNIT_0000_01MM_S,	// 0.01mm/s
	LKIF_DISPLAYUNIT_000_001MM_S,	// 0.001mm/s
	LKIF_DISPLAYUNIT_00_0001MM_S,	// 0.0001mm/s

	LKIF_DISPLAYUNIT_00000_1KM_S2=0,// 0.1km/s2
	LKIF_DISPLAYUNIT_0000_01KM_S2,	// 0.01km/s2
	LKIF_DISPLAYUNIT_000_001KM_S2,	// 0.001km/s2
	LKIF_DISPLAYUNIT_00000_1M_S2,	// 0.1m/s2
	LKIF_DISPLAYUNIT_0000_01M_S2,	// 0.01m/s2
	LKIF_DISPLAYUNIT_000_001M_S2,	// 0.001m/s2
	LKIF_DISPLAYUNIT_00_0001M_S2,	// 0.0001m/s2
} LKIF_DISPLAYUNIT;

// Set measurement type.
typedef enum {
	LKIF_MEASURETYPE_DISPLACEMENT,	// Displacement
	LKIF_MEASURETYPE_SPEED,			// Speed
	LKIF_MEASURETYPE_ACCELERATION,	// Acceleration
} LKIF_MEASURETYPE;

// Specify OUT
typedef enum {
	LKIF_OUTNO_01 = 0x0001,			// OUT01
	LKIF_OUTNO_02 = 0x0002,			// OUT02
	LKIF_OUTNO_03 = 0x0004,			// OUT03
	LKIF_OUTNO_04 = 0x0008,			// OUT04
	LKIF_OUTNO_05 = 0x0010,			// OUT05
	LKIF_OUTNO_06 = 0x0020,			// OUT06
	LKIF_OUTNO_07 = 0x0040,			// OUT07
	LKIF_OUTNO_08 = 0x0080,			// OUT08
	LKIF_OUTNO_09 = 0x0100,			// OUT09
	LKIF_OUTNO_10 = 0x0200,			// OUT10
	LKIF_OUTNO_11 = 0x0400,			// OUT11
	LKIF_OUTNO_12 = 0x0800,			// OUT12
	LKIF_OUTNO_ALL = 0x0FFF,		// All OUTs
} LKIF_OUTNO;	

// Set Synchronization  *Specify TRUE/FALSE for each OUT to set ON/OFF.
typedef enum {
	LKIF_SYNCHRONIZATION_ASYNCHRONOUS,	// asynchronous
	LKIF_SYNCHRONIZATION_SYNCHRONIZED,	// synchronous
} LKIF_SYNCHRONIZATION;

// Set Storage (Target)  *Specify TRUE/FALSE for each OUT to set ON/OFF.
typedef enum {
	LKIF_TARGETOUT_NONE,			// no target OUT
	LKIF_TARGETOUT_OUT1,			// OUT1
	LKIF_TARGETOUT_OUT2,			// OUT2
	LKIF_TARGETOUT_BOTH,			// OUT 1/2
} LKIF_TARGETOUT;

// Set Storage (Cycle)
typedef enum {
	LKIF_STORAGECYCLE_1,			// sampling rate x 1
	LKIF_STORAGECYCLE_2,			// sampling rate x 2
	LKIF_STORAGECYCLE_5,			// sampling rate x 5
	LKIF_STORAGECYCLE_10,			// sampling rate x 10
	LKIF_STORAGECYCLE_20,			// sampling rate x 20
	LKIF_STORAGECYCLE_50,			// sampling rate x 50
	LKIF_STORAGECYCLE_100,			// sampling rate x 100
	LKIF_STORAGECYCLE_200,			// sampling rate x 200
	LKIF_STORAGECYCLE_500,			// sampling rate x 500
	LKIF_STORAGECYCLE_1000,			// sampling rate x 1000
	LKIF_STORAGECYCLE_TIMING,		// Timing sync
} LKIF_STORAGECYCLE;

// Set Sampling Rate
typedef enum {
	LKIF_SAMPLINGCYCLE_2_55USEC,	// 2.55us
	LKIF_SAMPLINGCYCLE_5USEC,		// 5us
	LKIF_SAMPLINGCYCLE_10USEC,		// 10us
	LKIF_SAMPLINGCYCLE_20USEC,		// 20us
	LKIF_SAMPLINGCYCLE_50USEC,		// 50us
	LKIF_SAMPLINGCYCLE_100USEC,		// 100us
	LKIF_SAMPLINGCYCLE_200USEC,		// 200us
	LKIF_SAMPLINGCYCLE_500USEC,		// 500us
	LKIF_SAMPLINGCYCLE_1MSEC,		// 1ms
} LKIF_SAMPLINGCYCLE;

// Set Mutual interference prevention
typedef enum {
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_OFF,	// OFF
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_AB_ON,	// AB-ON
	LKIF_MUTUAL_INTERFERENCE_PREVENTION_ABC_ON,	// ABC-ON
} LKIF_MUTUAL_INTERFERENCE_PREVENTION;

// Set Comparator Output Format
typedef enum {
	LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT_NORMAL,		// normal
	LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT_HOLD,		// hold
	LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT_OFF_DELAY,	// off-delay
} LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT;

// Set Strobe Time
typedef enum {
	LKIF_STOROBETIME_2MS,		// 2ms
	LKIF_STOROBETIME_5MS,		// 5ms
	LKIF_STOROBETIME_10MS,		// 10ms
	LKIF_STOROBETIME_20MS,		// 20ms
} LKIF_STOROBETIME;

// Set alarm output form.
typedef enum {
	LKIF_ALARM_OUTPUT_FORM_SYSTEM,	// System alarm
	LKIF_ALARM_OUTPUT_FORM_MEASURE,	// Measurement alarm
	LKIF_ALARM_OUTPUT_FORM_BOTH,	// System alarm and measurement alarm
} LKIF_ALARM_OUTPUT_FORM;

// Mode Switch
typedef enum {
	LKIF_MODE_NORMAL,				// normal mode
	LKIF_MODE_COMMUNICATION,		// setting mode
} LKIF_MODE;

// Measurement value
typedef struct {
	int					OutNo;			// OUT No(0-11)
	LKIF_FLOATRESULT	FloatResult;	// valid or invalid data
	float				Value;			// Measurement value
} LKIF_FLOATVALUE_OUT;

typedef struct {
	LKIF_FLOATRESULT	FloatResult;	// valid or invalid data
	float				Value;			// Measurement value
} LKIF_FLOATVALUE;

// IP address
typedef struct {
	IN_ADDR				IPAddress;
} LKIF_OPENPARAM_ETHERNET;

extern "C"
{
///////////////////////////////////////////////
// Measurement control commands
//
// Measured value output (single)
EXP RC WINAPI LKIF2_GetCalcDataSingle(IN int OutNo,OUT LKIF_FLOATVALUE_OUT * CalcData);
// Measured value output (multiple)
EXP RC WINAPI LKIF2_GetCalcDataMulti(IN LKIF_OUTNO OutNo, OUT LKIF_FLOATVALUE_OUT * CalcData);
// Measured value output (ALL)
EXP RC WINAPI LKIF2_GetCalcDataALL(OUT int * OutNo,OUT LKIF_FLOATVALUE_OUT * CalcData);

// Timing ON/OFF (single)
EXP RC WINAPI LKIF2_SetTimingSingle(IN int OutNo,IN BOOL OnOff);
// Timing ON/OFF (multiple)
EXP RC WINAPI LKIF2_SetTimingMulti(IN LKIF_OUTNO OutNo,IN BOOL OnOff);
// Timing ON/OFF (synchronous)
EXP RC WINAPI LKIF2_SetTimingSync(IN BOOL OnOff);

// Auto-zero ON/OFF (single)
EXP RC WINAPI LKIF2_SetZeroSingle(IN int OutNo,IN BOOL OnOff);
// Auto-zero ON/OFF (multiple)
EXP RC WINAPI LKIF2_SetZeroMulti(IN LKIF_OUTNO OutNo, IN BOOL OnOff);
// Auto-zero ON/OFF (synchronous)
EXP RC WINAPI LKIF2_SetZeroSync(IN BOOL OnOff);

// Measured value reset (single)
EXP RC WINAPI LKIF2_SetResetSingle(IN int OutNo);
// Measured value reset (multiple)
EXP RC WINAPI LKIF2_SetResetMulti(IN LKIF_OUTNO OutNo);
// Measured value reset (synchronous)
EXP RC WINAPI LKIF2_SetResetSync();

// Panel lock
EXP RC WINAPI LKIF2_SetPanelLock(IN BOOL OnOff);

// Program Change
EXP RC WINAPI LKIF2_SetProgramNo(IN int ProgramNo);
// Program Check
EXP RC WINAPI LKIF2_GetProgramNo(OUT int * ProgramNo);

// Starting the Data Storage
EXP RC WINAPI LKIF2_DataStorageStart();
// Stopping the Data Storage
EXP RC WINAPI LKIF2_DataStorageStop();
// Outputting the Data Storage
EXP RC WINAPI LKIF2_DataStorageGetData(IN int OutNo,IN int NumOfBuffer,OUT LKIF_FLOATVALUE * OutBuffer,OUT int *NumReceived);
// Initializing the Data Storage
EXP RC WINAPI LKIF2_DataStorageInit();
// Data Storage Accumulation Status Output
EXP RC WINAPI LKIF2_DataStorageGetStatus(OUT BOOL * lsStorage,OUT int  * NumStorageData);
// Receive Light Waveform
EXP RC WINAPI LKIF2_GetLight(IN int HeadNo,IN int PeakNo,OUT int * MeasurePosition,OUT BYTE * WaveData);

///////////////////////////////////////////////
// Setting change commands
//
// Display Panel Switch
EXP RC WINAPI LKIF2_SetPanel(IN int UpperDisp,IN int LowerDisp);
// Set Tolerance
EXP RC WINAPI LKIF2_SetTolerance(IN int OutNo,IN int UpperLimit,IN int LowerLimit,IN int Hystersys);
// Set ABLE
EXP RC WINAPI LKIF2_SetAbleMode(IN int HeadNo,IN LKIF_ABLEMODE AbleMode);
// Set ABLE Control Range
EXP RC WINAPI LKIF2_SetAbleMinMax(IN int HeadNo,IN int Min,IN int Max);
// Set Detection mode
EXP RC WINAPI LKIF2_SetMeasureMode(IN int HeadNo,IN LKIF_MEASUREMODE MeasureMode);
// Set Base point
EXP RC WINAPI LKIF2_SetBasicPoint(IN int HeadNo,IN LKIF_BASICPOINT BasicPoint);
// Set Number of Times of Alarm Processing
EXP RC WINAPI LKIF2_SetNumAlarm(IN int HeadNo,IN int AlarmNum);
// Set Number of Times of Alarm Recovery
EXP RC WINAPI LKIF2_SetNumRecovery(IN int HeadNo,IN int RecoveryNum);
// Set Alarm Level
EXP RC WINAPI LKIF2_SetAlarmLevel(IN int HeadNo,IN int AlarmLevel);
// Starting the ABLE Calibration
EXP RC WINAPI LKIF2_AbleStart(IN int HeadNo);
// Finishing the ABLE Calibration
EXP RC WINAPI LKIF2_AbleStop();
// Stopping the ABLE Calibration
EXP RC WINAPI LKIF2_AbleCancel();
// Set Mounting Mode
EXP RC WINAPI LKIF2_SetReflectionMode(IN int HeadNo,IN LKIF_REFLECTIONMODE ReflectionMode);
// Set Mask
EXP RC WINAPI LKIF2_SetMask(IN int HeadNo,IN BOOL OnOff,IN int Pos1,IN int Pos2);
// Set Median
EXP RC WINAPI LKIF2_SetMedian(IN int HeadNo,IN LKIF_MEDIAN Median);
// Set LASER CTRL group
EXP RC WINAPI LKIF2_SetLaserCtrlGroup(IN int HeadNo,IN LKIF_LASER_CTRL_GROUP LaserCtrlGroup);
// Set Range
EXP RC WINAPI LKIF2_SetRange(IN int HeadNo,IN LKIF_RANGE Range);
// Set Mutual interference prevention group
EXP RC WINAPI LKIF2_SetMutualInterferencePreventionGroup(IN int HeadNo,IN LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP Group);
// Set Calculation method
EXP RC WINAPI LKIF2_SetCalcMethod(IN int OutNo,IN LKIF_CALCMETHOD CalcMethod,IN int HeadOutNo);
// Set Surface to be measured
EXP RC WINAPI LKIF2_SetCalcTarget(IN int OutNo,IN LKIF_CALCTARGET CalcTarget);
// Set OUT to be calculated (ADD, SUB)
EXP RC WINAPI LKIF2_SetOutAddSub(IN int OutNo,IN int AddSub1,IN int AddSub2);
// Set OUT to be calculated (AVE, MAX, MIN, P-P)
EXP RC WINAPI LKIF2_SetOutOperation(IN int OutNo,IN LKIF_OUTNO IN TargetOut);
// Set Scaling
EXP RC WINAPI LKIF2_SetScaling(IN int OutNo,IN int InputValue1,IN int OutputValue1,IN int InputValue2,IN int OutputValue2);
// Set Filter Mode
EXP RC WINAPI LKIF2_SetFilter(IN int OutNo,IN LKIF_FILTERMODE FilterMode,IN LKIF_FILTERPARA FilterPara);
// Set Trigger Mode
EXP RC WINAPI LKIF2_SetTriggerMode(IN int OutNo,IN LKIF_TRIGGERMODE TriggerMode);
// Set Offset
EXP RC WINAPI LKIF2_SetOffset(IN int OutNo,IN int Offset);
// Set Calculation Mode
EXP RC WINAPI LKIF2_SetCalcMode(IN int OutNo,IN LKIF_CALCMODE CalcMode);
// Set Analog Output Scaling
EXP RC WINAPI LKIF2_SetAnalogScaling(IN int OutNo,IN int InputValue1,IN int OutputVoltage1,IN int InputValue2,IN int OutputVoltage2);
// Set Minimum Display Unit
EXP RC WINAPI LKIF2_SetDisplayUnit(IN int OutNo,IN LKIF_DISPLAYUNIT DisplayUnit);
// Set Measurement type
EXP RC WINAPI LKIF2_SetMeasureType(IN int OutNo,IN LKIF_MEASURETYPE MeasureType);
// Set Synchronization
EXP RC WINAPI LKIF2_SetSynchronization(IN int OutNo,IN BOOL OnOff);
// Set Storage (OUT No. specification)
EXP RC WINAPI LKIF2_SetStorageTarget(IN int OutNo,IN BOOL OnOff);
// Set Sampling Rate
EXP RC WINAPI LKIF2_SetSamplingCycle(IN LKIF_SAMPLINGCYCLE SamplingCycle);
// Set Mutual Interference Prevention
EXP RC WINAPI LKIF2_SetMutualInterferencePrevention(IN LKIF_MUTUAL_INTERFERENCE_PREVENTION OnOff);
// Set Comparator Output Format
EXP RC WINAPI LKIF2_SetToleranceComparatorOutputFormat(IN LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT OutputFormat);
// Set Strobe Time
EXP RC WINAPI LKIF2_SetStrobeTime(IN LKIF_STOROBETIME StrobeTime);
// Set Data Storage
EXP RC WINAPI LKIF2_SetDataStorage(IN int NumStorage,IN LKIF_STORAGECYCLE StorageCycle);
// Set Analog output channel
EXP RC WINAPI LKIF2_SetAnalogChannel(IN int ChNo,IN int OutNo);
// Set Alarm output type
EXP RC WINAPI LKIF2_SetAlarmOutputForm(IN LKIF_ALARM_OUTPUT_FORM AlarmOutputForm);
// Set Active head count
EXP RC WINAPI LKIF2_SetNumOfUsedHeads(IN int NumOfUsedHeads);
// Set Active OUT count
EXP RC WINAPI LKIF2_SetNumOfUsedOut(IN int NumOfUsedOut);
// Set Active analog output channel count
EXP RC WINAPI LKIF2_SetNumOfUsedAnalogCh(IN int NumOfUsedAnalogCh);

///////////////////////////////////////////////
// Setting confirmation commands
//
// Display Panel Check
EXP RC WINAPI LKIF2_GetPanel(OUT int * UpperDisp,OUT int * LowerDisp);
// Get Tolerance
EXP RC WINAPI LKIF2_GetTolerance(IN int OutNo,OUT int * UpperLimit,OUT int * LowerLimit,OUT int * Hysteresis);
// Get ABLE
EXP RC WINAPI LKIF2_GetAbleMode(IN int HeadNo,OUT LKIF_ABLEMODE * AbleMode);
// Get ABLE Control Range
EXP RC WINAPI LKIF2_GetAbleMinMax(IN int HeadNo,OUT int * Min,OUT int * Max);
// Get Detection mode
EXP RC WINAPI LKIF2_GetMeasureMode(IN int HeadNo,OUT LKIF_MEASUREMODE * MeasureMode);
// Get Base point
EXP RC WINAPI LKIF2_GetBasicPoint(IN int HeadNo,OUT LKIF_BASICPOINT * BasicPoint);
// Get Number of Times of Alarm Processing
EXP RC WINAPI LKIF2_GetNumAlarm(IN int HeadNo,OUT int * AlarmNum);
// Get Number of Times of Alarm Recovery
EXP RC WINAPI LKIF2_GetNumRecovery(IN int HeadNo,OUT int * RecoveryNum);
// Get Alarm Level
EXP RC WINAPI LKIF2_GetAlarmLevel(IN int HeadNo,OUT int * AlarmLevel);
// Get Mounting Mode
EXP RC WINAPI LKIF2_GetReflectionMode(IN int HeadNo,OUT LKIF_REFLECTIONMODE * ReflectionMode);
// Get Mask
EXP RC WINAPI LKIF2_GetMask(IN int HeadNo,OUT BOOL * OnOff,OUT int * Pos1,OUT int * Pos2);
// Get Median
EXP RC WINAPI LKIF2_GetMedian(IN int HeadNo,OUT LKIF_MEDIAN * Median);
// Get LASER CTRL group
EXP RC WINAPI LKIF2_GetLaserCtrlGroup(IN int HeadNo,OUT LKIF_LASER_CTRL_GROUP * LaserCtrlGroup);
// Get Range
EXP RC WINAPI LKIF2_GetRange(IN int HeadNo,OUT LKIF_RANGE * Range);
// Get Mutual interference prevention group
EXP RC WINAPI LKIF2_GetMutualInterferencePreventionGroup(IN int HeadNo,OUT LKIF_MUTUAL_INTERFERENCE_PREVENTION_GROUP * Group);
// Get Calculation method
EXP RC WINAPI LKIF2_GetCalcMethod(IN int OutNo,OUT LKIF_CALCMETHOD * CalcMethod,OUT int * HeadOutNo);
// Get Surface to be measured
EXP RC WINAPI LKIF2_GetCalcTarget(IN int OutNo,OUT LKIF_CALCTARGET * CalcTarget);
// Get OUT to be calculated (ADD, SUB)
EXP RC WINAPI LKIF2_GetOutAddSub(IN int OutNo,OUT int * AddSub1,OUT int * AddSub2);
// Get OUT to be calculated (AVE, MAX, MIN, P-P)
EXP RC WINAPI LKIF2_GetOutOperation(IN int OutNo,OUT LKIF_OUTNO * TargetOut);
// Get Scaling
EXP RC WINAPI LKIF2_GetScaling(IN int OutNo,OUT int * InputValue1,OUT int * OutputValue1,OUT int * InputValue2,OUT int * OutputValue2);
// Get Filter Mode
EXP RC WINAPI LKIF2_GetFilter(IN int OutNo,OUT LKIF_FILTERMODE * FilterMode,OUT LKIF_FILTERPARA * FilterPara);
// Get Trigger Mode
EXP RC WINAPI LKIF2_GetTriggerMode(IN int OutNo,OUT LKIF_TRIGGERMODE * TriggerMode);
// Get Offset
EXP RC WINAPI LKIF2_GetOffset(IN int OutNo,OUT int * Offset);
// Get Calculation Mode
EXP RC WINAPI LKIF2_GetCalcMode(IN int OutNo,OUT LKIF_CALCMODE * CalcMode);
// Get Analog Output Scaling
EXP RC WINAPI LKIF2_GetAnalogScaling(IN int OutNo,OUT int * InputValue1,OUT int * OutputVoltage1,OUT int * InputValue2,OUT int * OutputVoltage2);
// Get Minimum Display Unit
EXP RC WINAPI LKIF2_GetDisplayUnit(IN int OutNo,OUT LKIF_DISPLAYUNIT * DisplayUnit);
// Get Measurement type
EXP RC WINAPI LKIF2_GetMeasureType(IN int OutNo,OUT LKIF_MEASURETYPE * MeasureType);
// Get Synchronization
EXP RC WINAPI LKIF2_GetSynchronization(IN int OutNo,OUT BOOL * OnOff);
// Get Storage (OUT No. specification)
EXP RC WINAPI LKIF2_GetStorageTarget(IN int OutNo,OUT BOOL * OnOff);
// Get Sampling Rate
EXP RC WINAPI LKIF2_GetSamplingCycle(OUT LKIF_SAMPLINGCYCLE * SamplingCycle);
// Get Mutual Interference Prevention
EXP RC WINAPI LKIF2_GetMutualInterferencePrevention(OUT LKIF_MUTUAL_INTERFERENCE_PREVENTION * OnOff);
// Get Comparator Output Format
EXP RC WINAPI LKIF2_GetToleranceComparatorOutputFormat(OUT LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT * OutputFormat);
// Get Strobe Time
EXP RC WINAPI LKIF2_GetStrobeTime(OUT LKIF_STOROBETIME * StrobeTime);
// Get Data Storage
EXP RC WINAPI LKIF2_GetDataStorage(OUT int * NumStorage,OUT LKIF_STORAGECYCLE * StorageCycle);
// Get Analog output channel
EXP RC WINAPI LKIF2_GetAnalogChannel(IN int ChNo,OUT int * OutNo);
// Get Alarm output type
EXP RC WINAPI LKIF2_GetAlarmOutputForm(OUT LKIF_ALARM_OUTPUT_FORM * AlarmOutputForm);
// Get Active head count
EXP RC WINAPI LKIF2_GetNumOfUsedHeads(OUT int * NumOfUsedHeads);
// Get Active OUT count
EXP RC WINAPI LKIF2_GetNumOfUsedOut(OUT int * NumOfUsedOut);
// Get Active analog output channel count
EXP RC WINAPI LKIF2_GetNumOfUsedAnalogCh(OUT int * NumOfUsedAnalogCh);

///////////////////////////////////////////////
// Mode change commands
//
// Start Measurement (Mode switch)
EXP RC WINAPI LKIF2_StartMeasure();
// Stop Measurement (Mode switch)
EXP RC WINAPI LKIF2_StopMeasure();

///////////////////////////////////////////////
// Other commands
//
// Opens the USB device.
EXP RC WINAPI LKIF2_OpenDeviceUsb();
// Opens the Ethernet device.
EXP RC WINAPI LKIF2_OpenDeviceETHER(LKIF_OPENPARAM_ETHERNET * OpenParam);
// Closes the currently open device.
EXP RC WINAPI LKIF2_CloseDevice();



///////////////////////////////////////////////
// The following is intended to ensure the compatibility with the LK-G3000 DLL.


///////////////////////////////////////////////
// Measurement Control Command
//
// Measurement Value Output
EXP BOOL		WINAPI	LKIF_GetCalcData(OUT LKIF_FLOATVALUE *CalcData1,OUT LKIF_FLOATVALUE *CalcData2);
// Timing ON/OFF
EXP	BOOL		WINAPI	LKIF_SetTiming(IN int OutNo,IN BOOL IsOn);
// Auto-zero ON/OFF
EXP	BOOL		WINAPI	LKIF_SetZero(IN int OutNo,IN BOOL IsOn);
// Reset
EXP	BOOL		WINAPI	LKIF_SetReset(IN int OutNo);
// Panel Lock
EXP	BOOL		WINAPI	LKIF_SetPanelLock(IN BOOL IsLock);
// Program Change
EXP	BOOL		WINAPI	LKIF_SetProgramNo(IN int ProgramNo);
// Program Check
EXP	BOOL		WINAPI	LKIF_GetProgramNo(OUT int *ProgramNo);
// Statistical Results Output
typedef struct {
	LKIF_FLOATVALUE		ToleUpper;						// tolerance upper limit
	LKIF_FLOATVALUE		ToleLower;						// tolerance lower limit
	LKIF_FLOATVALUE		AverageValue;					// average value
	LKIF_FLOATVALUE		MaxValue;						// maximum value
	LKIF_FLOATVALUE		MinValue;						// minimum value
	LKIF_FLOATVALUE		DifValue;						// maximum value - minimum value
	LKIF_FLOATVALUE		SdValue;						// standard deviation
	LONG				DataCnt;						// number of all data
	LONG				HighDataCnt;					// number of tolerance High data
	LONG				GoDataCnt;						// number of tolerance Go data
	LONG				LowDataCnt;						// number of tolerance Low data
} LKIF_FIGUREDATA;
EXP	BOOL		WINAPI	LKIF_GetFigureData(IN int OutNo,OUT LKIF_FIGUREDATA *FigureData);
// Clearing Statistics
EXP	BOOL		WINAPI	LKIF_ClearFigureData(void);
// Starting the Data Storage
EXP BOOL		WINAPI	LKIF_DataStorageStart(void);
// Stopping the Data Storage
EXP BOOL		WINAPI	LKIF_DataStorageStop(void);
// Initializing the Data Storage
EXP BOOL		WINAPI	LKIF_DataStorageInit(void);
// Outputting the Data Storage
EXP BOOL		WINAPI	LKIF_DataStorageGetData(IN int OutNo,IN int NumOutBuffer,OUT LKIF_FLOATVALUE *OutBuffer,OUT int *NumReceived);
// Data Storage Accumulation Status Output
EXP BOOL		WINAPI	LKIF_DataStorageGetStatus(IN int OutNo,OUT BOOL *IsStorage,OUT int *NumStorageData);
// Receive Light Waveform
EXP BOOL		WINAPI	LKIF_GetLight(IN int HeadNo,IN int PeekNo,OUT int *MeasurePosition,OUT int *NumReaded,OUT BYTE *Value);

///////////////////////////////////////////////
// Change Parameter Command
//
// Display Panel Switch
EXP BOOL		WINAPI	LKIF_SetPanel(IN int OutNo);
// Set Tolerance
EXP	BOOL		WINAPI	LKIF_SetTolerance(IN int OutNo,IN int UpperLimit,IN int LowerLimit,IN int Hysteresis);
// Set ABLE
EXP	BOOL		WINAPI	LKIF_SetAbleMode(IN int HeadNo,IN LKIF_ABLEMODE AbleMode);
// Set ABLE Control Range
EXP	BOOL		WINAPI	LKIF_SetAbleMinMax(IN int HeadNo,IN int Min,IN int Max);
// Set Measurement Mode
EXP BOOL		WINAPI	LKIF_SetMeasureMode(IN int HeadNo,IN LKIF_MEASUREMODE MeasureMode);
// Set Number of Times of Alarm Processing
EXP	BOOL		WINAPI	LKIF_SetNumAlarm(IN int HeadNo,IN int NumAlarm);
// Set Alarm Level
EXP BOOL		WINAPI	LKIF_SetAlarmLevel(IN int HeadNo,IN int AlarmLevel);
// Starting the ABLE Calibration
EXP	BOOL		WINAPI	LKIF_AbleStart(IN int HeadNo);
// Finishing the ABLE Calibration
EXP	BOOL		WINAPI	LKIF_AbleStop(void);
// Stopping the ABLE Calibration
EXP	BOOL		WINAPI	LKIF_AbleCancel(void);
// Set Mounting Mode
EXP BOOL		WINAPI	LKIF_SetReflectionMode(IN int HeadNo,IN LKIF_REFLECTIONMODE ReflectionMode);
// Set Calculation Method
EXP	BOOL		WINAPI	LKIF_SetCalcMethod(IN int OutNo,IN LKIF_CALCMETHOD CalcMethod,LKIF_CALCTARGET CalcTarget);
// Set Scaling
EXP	BOOL		WINAPI	LKIF_SetScaling(IN int OutNo,IN int HeadNo,IN int InputValue1,IN int OutputValue1,IN int InputValue2,IN int OutputValue2);
// Set Filter Mode
EXP	BOOL		WINAPI	LKIF_SetFilterMode(IN int OutNo,IN LKIF_FILTERMODE FilterMode);
// Set Number of Times for Averaging
EXP BOOL		WINAPI	LKIF_SetAverage(IN int OutNo,IN LKIF_AVERAGE Average);
// Set Cutoff Frequency
EXP	BOOL		WINAPI	LKIF_SetCutOffFrequency(IN int OutNo,IN LKIF_CUTOFFFREQUENCY CutOffFrequency);
// Set Trigger Mode
EXP	BOOL		WINAPI	LKIF_SetTriggerMode(IN int OutNo,IN LKIF_TRIGGERMODE TriggerMode);
// Set Offset
EXP BOOL		WINAPI	LKIF_SetOffset(IN int OutNo,IN int Offset);
// Set Analog Output Scaling
EXP	BOOL		WINAPI	LKIF_SetAnalogScaling(IN int OutNo,IN int InputValue1,IN int OutputVoltage1,IN int InputValue2,IN int OutputVoltage2);
// Set Calculation Mode
EXP	BOOL		WINAPI	LKIF_SetCalcMode(IN int OutNo,IN LKIF_CALCMODE CalcMode);
// Set Minimum Display Unit
EXP	BOOL		WINAPI	LKIF_SetDisplayUnit(IN int OutNo,IN LKIF_DISPLAYUNIT DisplayUnit);
// Set Analog-Through
EXP	BOOL		WINAPI	LKIF_SetAnalogThrough(IN int OutNo,IN BOOL IsOn);
// Set Data Storage
EXP	BOOL		WINAPI	LKIF_SetDataStorage(IN LKIF_TARGETOUT TargetOut,IN int NumStorage,IN LKIF_STORAGECYCLE StorageCycle);
// Set Sampling Rate
EXP BOOL		WINAPI	LKIF_SetSamplingCycle(IN LKIF_SAMPLINGCYCLE SamplingCycle);
// Set Mutual Interference Prevention
EXP	BOOL		WINAPI	LKIF_SetMutualInterferencePrevention(IN BOOL IsOn);
// Set Timing Synchronization
EXP	BOOL		WINAPI	LKIF_SetTimingSynchronization(IN LKIF_SYNCHRONIZATION Synchronization);
// Set Comparator Output Format
EXP	BOOL		WINAPI	LKIF_SetToleranceComparatorOutputFormat(IN LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT ToleranceComparatorOutputFormat);
// Set Strobe Time
EXP	BOOL		WINAPI	LKIF_SetStorobeTime(IN LKIF_STOROBETIME StorobeTime);
///////////////////////////////////////////////
// Check Parameter Command
//
// Display Panel Check
EXP BOOL		WINAPI	LKIF_GetPanel(OUT int *OutNo);
// Get Tolerance
EXP	BOOL		WINAPI	LKIF_GetTolerance(IN int OutNo,OUT int *UpperLimit,OUT int *LowerLimit,OUT int *Hysteresis);
// Get ABLE
EXP	BOOL		WINAPI	LKIF_GetAbleMode(IN int HeadNo,OUT LKIF_ABLEMODE *AbleMode);
// ABLE Control Range
EXP	BOOL		WINAPI	LKIF_GetAbleMinMax(IN int HeadNo,OUT int *Min,OUT int *Max);
// Get Measurement Mode
EXP BOOL		WINAPI	LKIF_GetMeasureMode(IN int HeadNo,OUT LKIF_MEASUREMODE *MeasureMode);
// Get Number of Times of Alarm Processing
EXP	BOOL		WINAPI	LKIF_GetNumAlarm(IN int HeadNo,OUT int *NumAlarm);
// Get Alarm Level
EXP	BOOL		WINAPI	LKIF_GetAlarmLevel(IN int HeadNo,OUT int *AlarmLevel);
// Get Mounting Mode
EXP BOOL		WINAPI	LKIF_GetReflectionMode(IN int HeadNo,OUT LKIF_REFLECTIONMODE *ReflectionMode);
// Get Calculation Method
EXP	BOOL		WINAPI	LKIF_GetCalcMethod(IN int OutNo,OUT LKIF_CALCMETHOD *CalcMethod,LKIF_CALCTARGET *CalcTarget);
// Get Scaling
EXP	BOOL		WINAPI	LKIF_GetScaling(IN int OutNo,IN int HeadNo,OUT int *InputValue1,OUT int *OutputValue1,OUT int *InputValue2,OUT int *OutputValue2);
// Get Filter Mode
EXP	BOOL		WINAPI	LKIF_GetFilterMode(IN int OutNo,OUT LKIF_FILTERMODE *FilterMode);
// Get Number of Times for Averaging
EXP	BOOL		WINAPI	LKIF_GetAverage(IN int OutNo,OUT LKIF_AVERAGE *Average);
// Get Cutoff Frequency
EXP	BOOL		WINAPI	LKIF_GetCutOffFrequency(IN int OutNo,OUT LKIF_CUTOFFFREQUENCY *CutOffFrequency);
// Get Trigger Mode
EXP	BOOL		WINAPI	LKIF_GetTriggerMode(IN int OutNo,OUT LKIF_TRIGGERMODE *TriggerMode);
// Get Offset
EXP BOOL		WINAPI	LKIF_GetOffset(IN int OutNo,IN int *Offset);
// Get Analog Output Scaling
EXP	BOOL		WINAPI	LKIF_GetAnalogScaling(IN int OutNo,OUT int *InputValue1,OUT int *OutputVoltage1,OUT int *InputValue2,OUT int *OutputVoltage2);
// Get Calculation Mode
EXP	BOOL		WINAPI	LKIF_GetCalcMode(IN int OutNo,OUT LKIF_CALCMODE *CalcMode);
// Get Minimum Display Unit
EXP	BOOL		WINAPI	LKIF_GetDisplayUnit(IN int OutNo,OUT LKIF_DISPLAYUNIT *DisplayUnit);
// Analog-Through
EXP	BOOL		WINAPI	LKIF_GetAnalogThrough(IN int OutNo,OUT BOOL *IsOn);
// Get Data Storage
EXP	BOOL		WINAPI	LKIF_GetDataStorage(IN LKIF_TARGETOUT *TargetOut,OUT int *NumStorage,OUT LKIF_STORAGECYCLE *StorageCycle);
// Get Sampling Rate
EXP BOOL		WINAPI	LKIF_GetSamplingCycle(OUT LKIF_SAMPLINGCYCLE *SamplingCycle);
// Get Mutual Interference Prevention
EXP	BOOL		WINAPI	LKIF_GetMutualInterferencePrevention(OUT BOOL *IsOn);
// Get Timing Synchronization
EXP	BOOL		WINAPI	LKIF_GetTimingSynchronization(OUT LKIF_SYNCHRONIZATION *Synchronization);
// Get Comparator Output Format
EXP	BOOL		WINAPI	LKIF_GetToleranceComparatorOutputFormat(OUT LKIF_TOLERANCE_COMPARATOR_OUTPUT_FORMAT *ToleranceComparatorOutputFormat);
// Get Strobe Time
EXP	BOOL		WINAPI	LKIF_GetStorobeTime(OUT LKIF_STOROBETIME *StorobeTime);
///////////////////////////////////////////////
// Mode Change Command
//
// Mode Switch
EXP BOOL		WINAPI	LKIF_SetMode(IN LKIF_MODE Mode);

} // extern "C"
