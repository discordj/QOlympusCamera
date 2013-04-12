#include "olympuscommon.h"

OlympusCommon *OlympusCommon::instance = (OlympusCommon *)0;


OlympusCommon::OlympusCommon()
{
	loadISOsettings();
	loadResolutionModes();
	loadExposureModes();
	loadWhiteBalanceModes();
}

OlympusCommon::~OlympusCommon()
{

}

OlympusCommon *OlympusCommon::Common()
{
	if(instance == 0)
	{
		instance = new OlympusCommon();
	}

	return instance;
}

void OlympusCommon::loadISOsettings(){
isosettings.clear();
isosettings[PRM_ISO_AUTO]= "Auto";
isosettings[PRM_ISO_100]= "100";	// ISO 100
isosettings[PRM_ISO_125]=("125");	// ISO 125
isosettings[PRM_ISO_160]=("160");	// ISO 160
isosettings[PRM_ISO_200]=("200");	// ISO 200
isosettings[PRM_ISO_250]=("250");	// ISO 250
isosettings[PRM_ISO_320]=("320");	// ISO 320
isosettings[PRM_ISO_400]=("400");	// ISO 400
isosettings[PRM_ISO_500]=("500");	// ISO 500
isosettings[PRM_ISO_640]=("640");	// ISO 640
isosettings[PRM_ISO_800]=("800");	// ISO 800
isosettings[PRM_ISO_1000]=("1000");	// ISO 1000
isosettings[PRM_ISO_1250]=("1250");	// ISO 1250
isosettings[PRM_ISO_1600]=("1600");	// ISO 1600
isosettings[PRM_ISO_2000]=("2000");	// ISO 2000
isosettings[PRM_ISO_2500]=("2500");	// ISO 2500
isosettings[PRM_ISO_3200]=("3200");	// ISO 3200
}

void OlympusCommon::loadResolutionModes()
{
	RESOLUTION_MODES.clear();
RESOLUTION_MODES[PRM_RESOLUTION_SQ] = ("Small Jpeg");// SQ
RESOLUTION_MODES[PRM_RESOLUTION_HQ]	= ("Medium Jpeg");	// HQ
RESOLUTION_MODES[PRM_RESOLUTION_SHQ]= ("Large Jpeg");	// SHQ
RESOLUTION_MODES[PRM_RESOLUTION_TIFF]= ("Tiff");	// TIFF
RESOLUTION_MODES[PRM_RESOLUTION_RAW]= ("Raw");	// RAW
RESOLUTION_MODES[PRM_RESOLUTION_RAW_SQ]= ("Raw + Small Jpeg");	// RAW+SQ
RESOLUTION_MODES[PRM_RESOLUTION_RAW_HQ]	= ("Raw + Medium Jpeg");	// RAW+HQ
RESOLUTION_MODES[PRM_RESOLUTION_RAW_SHQ]= ("Raw + Large Jpeg");	// RAW+SHQ
RESOLUTION_MODES[PRM_RESOLUTION_SET1]= ("Large Fine");	// SET1
RESOLUTION_MODES[PRM_RESOLUTION_SET2]= ("Large Normal");	// SET2
RESOLUTION_MODES[PRM_RESOLUTION_SET3]= ("Medium Normal");	// SET3
RESOLUTION_MODES[PRM_RESOLUTION_SET4]= ("Small Normal");	// SET4
RESOLUTION_MODES[PRM_RESOLUTION_SET0_SET1]= ("Raw + Large Fine");	// SET0+SET1
RESOLUTION_MODES[PRM_RESOLUTION_SET0_SET2]= ("Raw + Large Normal");	// SET0+SET2
RESOLUTION_MODES[PRM_RESOLUTION_SET0_SET3]= ("Raw + Medium Normal");	// SET0+SET3
RESOLUTION_MODES[PRM_RESOLUTION_SET0_SET4]= ("Raw + Small Normal");	// SET0+SET4
}

void OlympusCommon::loadExposureModes()
{
	EXPOSURE_MODES.clear();
	EXPOSURE_MODES[PRM_EXP_MODE_FULL_AUTO]="Auto";
	EXPOSURE_MODES[PRM_EXP_MODE_MANUAL]	= "Manual";
	EXPOSURE_MODES[PRM_EXP_MODE_PROGRAM]="Program";
	EXPOSURE_MODES[PRM_EXP_MODE_APERTURE_PRIORITY]	= "Aperture Priority";
	EXPOSURE_MODES[PRM_EXP_MODE_SHUTTER_PRIORITY]	= "Shutter Priority";
	EXPOSURE_MODES[PRM_EXP_MODE_BULB]				= "Bulb";
	EXPOSURE_MODES[PRM_EXP_MODE_MYMODE1]		= "My Mode 1";
	EXPOSURE_MODES[PRM_EXP_MODE_MYMODE2]			= "My Mode 2";
	EXPOSURE_MODES[PRM_EXP_MODE_PORTRAIT]			= "Portrait";
	EXPOSURE_MODES[PRM_EXP_MODE_MACRO]				= "Macro";
	EXPOSURE_MODES[PRM_EXP_MODE_LANDSCAPE]			= "Landscape";
	EXPOSURE_MODES[PRM_EXP_MODE_NIGHTSCENE]			= "Night Scene";
	EXPOSURE_MODES[PRM_EXP_MODE_NS_PORTRAIT]		= "Night Scene Portrait";
	EXPOSURE_MODES[PRM_SCENE_SEL_LANDSCAPE]= "Scene - Landscape";
	EXPOSURE_MODES[PRM_SCENE_SEL_SOUVENIR]= "Scene - Souvenir";
	EXPOSURE_MODES[PRM_SCENE_SEL_NIGHTSCENE] = "Scene - NightScene";
	EXPOSURE_MODES[PRM_SCENE_SEL_NS_PORTRAIT]="Scene - NightScene Portrait";
	EXPOSURE_MODES[PRM_SCENE_SEL_FIREWORKS]="Scene - Fireworks";
	EXPOSURE_MODES[PRM_SCENE_SEL_SUNSET]="Scene - Sunset";
	EXPOSURE_MODES[PRM_SCENE_SEL_PORTRAIT] ="Scene - Portrait";
	EXPOSURE_MODES[PRM_SCENE_SEL_HIGHKEY]= "Scene - HighKey";
	EXPOSURE_MODES[PRM_SCENE_SEL_MACRO]="Scene - Macro";
	EXPOSURE_MODES[PRM_SCENE_SEL_DOCUMENT]="Scene - Document";
	EXPOSURE_MODES[PRM_SCENE_SEL_MANNER]="Scene - Manner";
	EXPOSURE_MODES[PRM_SCENE_SEL_CANDLE]="Scene - Candle";
	EXPOSURE_MODES[PRM_SCENE_SEL_LOWKEY]="Scene - LowKey";
	EXPOSURE_MODES[PRM_SCENE_SEL_LS_PORTRAIT]="Scene - LS Portrait";
	EXPOSURE_MODES[PRM_SCENE_SEL_IMG_STABILIZATION]="Scene - Image Stabilization";
	EXPOSURE_MODES[PRM_SCENE_SEL_NATURE_MACRO]="Scene - Nature Macro";
}

void OlympusCommon::loadWhiteBalanceModes(){
	WHITEBALANCE_MODES[PRM_WB_MODE_AUTO] = "AUTO";
	WHITEBALANCE_MODES[PRM_WB_MODE_DIRECT] = "DIRECT";
	WHITEBALANCE_MODES[PRM_WB_MODE_OTWB] = "ONE TOUCH";
	WHITEBALANCE_MODES[PRM_WB_MODE_CUSTOM] = "CUSTOM";

	MANUALWB_MODES[PRM_MANUAL_WB_3000] = 1;
	MANUALWB_MODES[PRM_MANUAL_WB_3300] = 2;
	MANUALWB_MODES[PRM_MANUAL_WB_3600] = 3;
	MANUALWB_MODES[PRM_MANUAL_WB_3900] = 4;
	MANUALWB_MODES[PRM_MANUAL_WB_4000] = 5;
	MANUALWB_MODES[PRM_MANUAL_WB_4300] = 6;
	MANUALWB_MODES[PRM_MANUAL_WB_4500] = 7;
	MANUALWB_MODES[PRM_MANUAL_WB_4800] = 8;
	MANUALWB_MODES[PRM_MANUAL_WB_5500] = 9;
	MANUALWB_MODES[PRM_MANUAL_WB_6500] = 10;
	MANUALWB_MODES[PRM_MANUAL_WB_6600] = 11;
	MANUALWB_MODES[PRM_MANUAL_WB_7500] = 12;

	ONETOUCHWB_MODES[PRM_OTWB1] = 13;
	ONETOUCHWB_MODES[PRM_OTWB2] = 14;
	ONETOUCHWB_MODES[PRM_OTWB3] = 15;
	ONETOUCHWB_MODES[PRM_OTWB4] = 16;

	CUSTOMWB_MODES[PRM_CUSTOM_WB_1] = 17;
	CUSTOMWB_MODES[PRM_CUSTOM_WB_2] = 18;
	CUSTOMWB_MODES[PRM_CUSTOM_WB_3] = 19;
	CUSTOMWB_MODES[PRM_CUSTOM_WB_4] = 20;

	int count = 0;
	WHITEBALANCES[count++] = "AUTO"; //0
//	WHITEBALANCES[count++] = "DIRECT";
//	WHITEBALANCES[count++] = "ONE TOUCH";
//	WHITEBALANCES[count++] = "CUSTOM";

	WHITEBALANCES[count++] = "3000K";//1
	WHITEBALANCES[count++] = "3300K";
	WHITEBALANCES[count++] = "3600K";
	WHITEBALANCES[count++] = "3900K";
	WHITEBALANCES[count++] = "4000K";
	WHITEBALANCES[count++] = "4300K";
	WHITEBALANCES[count++] = "4500K";
	WHITEBALANCES[count++] = "4800K";
	WHITEBALANCES[count++] = "5300K";
	WHITEBALANCES[count++] = "6000k";
	WHITEBALANCES[count++] = "6600K";
	WHITEBALANCES[count++] = "7500K"; //12

	WHITEBALANCES[count++] = "ONE TOUCH #1";//13
	WHITEBALANCES[count++] = "ONE TOUCH #2";
	WHITEBALANCES[count++] = "ONE TOUCH #3";
	WHITEBALANCES[count++] = "ONE TOUCH #4";//16

	WHITEBALANCES[count++] = "CUSTOM 1";//17
	WHITEBALANCES[count++] = "CUSTOM 2";
	WHITEBALANCES[count++] = "CUSTOM 3";
	WHITEBALANCES[count++] = "CUSTOM 4";//20

}