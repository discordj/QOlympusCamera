#ifndef QOLYMPUSCOMMON_H
#define QOLYMPUSCOMMON_H

#include <QMap>
#include <QString>
#include "MochaCommon.h"


//ISO values
inline void loadISOsettings(QMap<UINT16, QString > isosettings){
isosettings.insert(PRM_ISO_AUTO,  "Auto");
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

//Resolution Modes
inline void loadResolutionModes(QMap<UINT16, QString > RESOLUTION_MODES)
{
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
#endif //QOLYPMUSCOMMON_H