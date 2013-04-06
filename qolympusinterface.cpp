#include "qolympusinterface.h"
//CALLBACK STUFF
int CALLBACK _mochaImageReady(unsigned int icam, unsigned int ulObjHandle, void *pParam)
{
	QOlympusInterface *caminterface = (QOlympusInterface *)pParam;
	((QOlympusCamera *)caminterface->getCamera(icam))->image_ready(ulObjHandle);

	return 0;
}

int CALLBACK _mochaDeviceAdd(unsigned int icam, void *pParam)
{
	return 0;
}

int CALLBACK _mochaDeviceRemove(unsigned int icam, void *pParam)
{
	QOlympusInterface *caminterface = (QOlympusInterface *)pParam;
	caminterface->removeCamera(icam);
	return 0;
}

int CALLBACK _mochaPropertyChanged(unsigned int icam, unsigned int uProp, void *pParam)
{
	QOlympusInterface *caminterface = (QOlympusInterface *)pParam;
	QOlympusCamera *camera = (QOlympusCamera *)caminterface->getCamera(icam);

	switch(uProp)
	{
		case OP_RESOLUTION_MODE:
			camera->notifypropertychanged(QCameraProperties::ResolutionMode, QVariant(GetResolutionMode(icam)));
			break;
		case OP_FNUMBER:
			camera->notifypropertychanged(QCameraProperties::Aperture, QVariant(GetAperture(icam)));
			break;
		case OP_EXPOSURE_INDEX:
			camera->notifypropertychanged(QCameraProperties::Iso, QVariant(GetISO(icam)));
			break;
		case OP_EXPOSURE_TIME_EX:
			camera->notifypropertychanged(QCameraProperties::ExposureTimes, QVariant(GetExposureEx(icam)));
			break;
		case OP_BATTERY_LEVEL:
			camera->notifypropertychanged(QCameraProperties::BatteryLevel, QVariant(camera->batteryLevel()));
	}

	return 0;
}

int CALLBACK _mochaUpdateCapabilities(unsigned int icam, void *pParam)
{
	return 0;
}


QOlympusInterface::QOlympusInterface()
{
}

QOlympusInterface::~QOlympusInterface()
{

}

void QOlympusInterface::initialize()
{
	
	_mochaCallbacks.pfnImageReady = _mochaImageReady;
	_mochaCallbacks.pImageReadyParam = this;
	_mochaCallbacks.pfnAddDevice = _mochaDeviceAdd;
	_mochaCallbacks.pAddDeviceParam = this;
	_mochaCallbacks.pfnRemoveDevice = _mochaDeviceRemove;
	_mochaCallbacks.pRemoveDeviceParam = this;
	_mochaCallbacks.pfnPropChanged = _mochaPropertyChanged;
	_mochaCallbacks.pPropChangedParam = this;
	_mochaCallbacks.pfnUpdateCapabilities = _mochaUpdateCapabilities;
	_mochaCallbacks.pUpdateCapabilitiesParam = this;

	long ret = InitMocha(&_mochaCallbacks);

	if(ret != 0)
	{
		MOCHA_ERROR	err;
		GetLastMochaError(&err);
		qDebug(err.strErrorMessage);
	}
}
void QOlympusInterface::on_camera_selected(QCamera *camera){ 
	_selectedCamera = (QOlympusCamera *)camera; 
	
	_selectedCameras.insert(_selectedCamera->index(), _selectedCamera);

}
void QOlympusInterface::removeCamera(int index)
{
	if(_selectedCameras.contains(index)){
		QOlympusCamera *cam = _selectedCameras.value(index);
		_selectedCameras.remove(index);

		delete cam;
	}
}


void QOlympusInterface::unload()
{
}
QList<QCamera *> QOlympusInterface::getcameras()
{
	QList<QCamera *> cameras; 
	int count = GetCameraCount();
	
	for(int i=0; i < count; i++)
	{
		if(_selectedCameras.contains(i)) continue;
		QOlympusCamera *camera = new QOlympusCamera(i);
		connect(camera, SIGNAL(camera_selected(QCamera *)),this, SLOT(on_camera_selected(QCamera *)));
		cameras.append(camera);
	}
	
	return cameras;
}

//Q_EXPORT_PLUGIN2( olympus, QOlympusInterface )

Q_PLUGIN_METADATA(IID "com.ctphoto.QCameraInterface/0.1");
