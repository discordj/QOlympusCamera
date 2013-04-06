#ifndef QOLYMPUSINTERFACE_H
#define QOLYMPUSINTERFACE_H

#define NOMINMAX

#include <windows.h>
#include "MochaDLL.h"
#include "olympuscommon.h"
#include "qolympuscamera_global.h"

#include <QtPlugin>

#include <QFile>
#include <QMap>
#include <qcamerainterface.h>
#include "qolympuscamera.h"

class QOlympusInterface : public QCameraInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "com.ctphoto.QCameraInterface/0.1");
	Q_INTERFACES(QCameraInterface)

public:
	QOlympusInterface();
	~QOlympusInterface();

	virtual void initialize();
	virtual void unload();
	virtual QList<QCamera *> getcameras();
	virtual QString name() { return "Olympus Camera Interface"; }
	QCamera * selectedCamera(){ return _selectedCamera; }
	QCamera *getCamera(int index) { return _selectedCameras.value(index); }
	void removeCamera(int index);

private:
	MOCHA_CALLBACKS	_mochaCallbacks;
	QOlympusCamera *_selectedCamera;
	QMap<int, QOlympusCamera *> _selectedCameras;

private slots:
	void on_camera_selected(QCamera *camera);
};

#endif // QOLYMPUSINTERFACE_H
