#ifndef OLYMPUSCOMMON_H
#define OLYMPUSCOMMON_H

#define NOMINMAX

#include <windows.h>
#include "MochaDLL.h"
#include <MochaCommon.h>
#include "qolympuscamera_global.h"

#include <QObject>
#include <QMap>


class OlympusCommon
{
public:
	static OlympusCommon *Common();
	~OlympusCommon();

//ISO values
QMap<UINT16, QString > isosettings;

//Resolution Modes
QMap<UINT16, QString > RESOLUTION_MODES;

QMap<UINT16, QString> EXPOSURE_MODES;

QMap<UINT16,  QString> WHITEBALANCE_MODES;

QMap<UINT16,  QString> CUSTOMWB_MODES;
QMap<UINT16,  QString> MANUALWB_MODES;

QMap<UINT16,  QString> ONETOUCHWB_MODES;

protected:
OlympusCommon();

private:
static OlympusCommon *instance;
void loadResolutionModes();
void loadISOsettings();
void loadExposureModes();
void loadWhiteBalanceModes();

};

#endif // OLYMPUSCOMMON_H
