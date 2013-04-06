#ifndef QOLYMPUSCAMERA_H
#define QOLYMPUSCAMERA_H
#define NOMINMAX

#include <windows.h>
#include "MochaDLL.h"
#include "olympuscommon.h"
#include "qolympuscamera_global.h"

#include <QFile>
#include <QTimer>
#include <QPixmap>

#include <qcamera.h>

class QOLYMPUSCAMERA_EXPORT QOlympusCamera : public QCamera
{
   Q_OBJECT
public:
	QOlympusCamera();
	~QOlympusCamera();

	int index() { return _index; }
	QString model() { return _model; }

	void capture(int seconds=0);
	QImage getImage();
	void startbulbexposure();
	void stopbulbexposure();
	void setbulbmode(bool bulb);
	void setSelected(){ emit camera_selected(this); };

	int QCConnect();
	int QCDisconnect();
	QString identifier() { return QString("Olympus %1 (%2)").arg(_model).arg(_serialnumber); }

	QCameraProperties *getCameraProperties();
	QCameraProperty *getCameraProperty(QCameraProperties::QCameraPropertyTypes prop);
	void setCameraProperty(QCameraProperties::QCameraPropertyTypes prop, QVariant value);

	void setImageDirectory(QString dir){_imagedestdir = dir;}
	void setImageFilePrefix(QString imagenameprefix){ _nameprefix = imagenameprefix; }

	void toggleLiveView(bool onoff);
	int batteryLevel(){ return BatteryLevel(_index);}


	virtual bool hasBulbMode();
	virtual bool canSetBulbMode();
	virtual bool hasLiveView(){return IsPropertySupported(_index, OP_LIVEVIEW_MODE);}
	virtual bool canStreamLiveView(){ return false;}

	virtual void lockUI();
	virtual void unlockUI();

	void initializeLiveView(){}
	QPixmap *getLiveViewImage(){return new QPixmap();}
	void endLiveView(){}

	friend class QOlympusInterface;
	friend int CALLBACK _mochaImageReady(unsigned int icam, unsigned int ulObjHandle, void *pParam);
	friend int CALLBACK _mochaPropertyChanged(unsigned int icam, unsigned int uProp, void *pParam);
signals:
	//void image_captured(QImage image);
	//void bulbexposuredone();

protected:
	QOlympusCamera(int index);
	void setIndex(int index) { _index = index; }
	void setModel(QString model) { _model = model; }
	void image_ready(unsigned int ulObjHandle);

	void notifypropertychanged(QCameraProperties::QCameraPropertyTypes prop, QVariant value){ emit camera_property_changed(prop, value); }

private:
	int _index;
	QString _model;
	QString _serialnumber;
	bool _inbulbmode;
	QTimer *bulbtimer;
	QString _imagedestdir;
	QString _nameprefix;
	int _imagecount;
	QString _darkframe;
	bool _usedarkframe;
	int _origexposuretime;
	bool _manualbulb;
	QCameraProperties *_properties;

	QCameraProperties *QOlympusCamera::getallproperties();

private slots:
	void on_bulbtimer_timeout();

};

#endif // QOLYMPUSCAMERA_H
