#include "qolympuscamera.h"

#include "dcrimage.h"

QOlympusCamera::QOlympusCamera()
{

}
QOlympusCamera::QOlympusCamera(int index)
{
	_index = index;
	_model = QString(CameraModel(index));
	_serialnumber = QString(SerialNumber(index));
	_inbulbmode = false;
	_imagecount = 0;
	_imagedestdir = QDir::currentPath();
	_properties = 0;
}

QOlympusCamera::~QOlympusCamera()
{
	QCDisconnect();
}

void QOlympusCamera::capture(int seconds)
{

	if(!Connected(_index))
	{
		QCConnect();
	}

	Capture(_index, PRM_PRESS_HOLD);

	if(_inbulbmode)
	{
		bulbtimer = new QTimer();

		connect(bulbtimer,SIGNAL(timeout()),this,SLOT(on_bulbtimer_timeout()));
		bulbtimer->start(seconds * 1000);
	}
	emit camera_busy(true);
	//else
	//{
	//	QCDisconnect();
	//}
}
void QOlympusCamera::on_bulbtimer_timeout()
{
	if(!Connected(_index))
	{
		QCConnect();
	}

	Capture(_index, PRM_RELEASE_OFF);
	delete bulbtimer;

	//QCDisconnect();
	//emit camera_busy(false);
	
}

void QOlympusCamera::startbulbexposure()
{
}

void QOlympusCamera::stopbulbexposure()
{
}
void QOlympusCamera::lockUI()
{
	int ret = SetCameraControlMode(_index,PRM_CAM_CONTROL);
	if(ret != 0)
	{
		MOCHA_ERROR	err;
		GetLastMochaError(&err);
		qDebug(err.strErrorMessage);
	}
	emit camera_busy(false);
}

void QOlympusCamera::unlockUI(){
	int ret = SetCameraControlMode(_index,PRM_CAM_CAPTURE);
	if(ret != 0)
	{
		MOCHA_ERROR	err;
		GetLastMochaError(&err);
		qDebug(err.strErrorMessage);
	}
	emit camera_busy(true);
}

void  QOlympusCamera::setbulbmode(bool bulb)
{
	if(!Connected(_index))
		QCConnect();
	_inbulbmode = bulb;
	if(bulb){

		if(!canSetBulbMode())
		{
			_origexposuretime = GetExposureEx(_index);
		}
		else
		{
			SetBulbMode(_index,0x01E00001);
			SetProgramMode(_index,PRM_EXP_MODE_BULB);
		}
	}
	else
	{
		SetBulbMode(_index,0);
		SetProgramMode(_index, PRM_EXP_MODE_MANUAL);
		SetExposureEx(_index,_origexposuretime);
		emit camera_property_changed(QCameraProperties::ExposureTimes, QVariant(_origexposuretime));
	}
	//QCDisconnect();


}
bool QOlympusCamera::canSetBulbMode()
{
	hasBulbMode();
	return !_manualbulb;
}

void QOlympusCamera::toggleLiveView(bool onoff)
{
	if(!Connected(_index))
		QCConnect();
	if(onoff)
	{
		SetVideoOutDevice(_index, 0x0001);
	}
	else
	{
		SetVideoOutDevice(_index, 0x0000);
	}
	//QCDisconnect();
}

QCameraProperty *QOlympusCamera::getCameraProperty(QCameraProperties::QCameraPropertyTypes prop)
{

	return _properties->getCameraProperty(prop);
}

QCameraProperties *QOlympusCamera::getCameraProperties()
{
	if(_properties)
		delete _properties;
	_properties = getallproperties();

	return _properties;
}

QCameraProperties *QOlympusCamera::getallproperties()
{

	if(!Connected(_index))
		QCConnect();
	OlympusCommon *olycommon = OlympusCommon::Common();

	QCameraProperties *props = new QCameraProperties();
	int count = 0;
	MOCHA_PROPERTY prop;
	GetPropertyInfo(_index, OP_RESOLUTION_MODE, &prop);
	QCameraProperty *camProp = new QCameraProperty("Resolutions");
	
	camProp->setCurrentValue(QVariant((UINT16) prop.CurrentValue.ui16Value));
	const void *values = GetPropertyValues(_index,OP_RESOLUTION_MODE,(PUINT16) &count, false);
	for(int i=0; i < count; i++)
	{
		QString name = OlympusCommon::Common()->RESOLUTION_MODES[(UINT16)(((UINT16*)values)[i])];
		camProp->appendValue(name,QVariant((UINT16)(((UINT16*)values)[i])));
	}

	props->addProperty(QCameraProperties::ResolutionMode, camProp);



	//GetPropertyInfo(_index, OP_NOISE_REDUCTION_PATTERN, &prop);
	//values = GetPropertyValues(_index,OP_NOISE_REDUCTION_PATTERN,(PUINT16) &count, false);

	//GetPropertyInfo(_index, OP_NOISE_REDUCTION_RANDOM, &prop);
	//values = GetPropertyValues(_index,OP_NOISE_REDUCTION_RANDOM,(PUINT16) &count, false);

	camProp = new QCameraProperty("FNumbers");

	GetPropertyInfo(_index, OP_FNUMBER, &prop);
	camProp->setCurrentValue(QVariant((UINT16) prop.CurrentValue.ui16Value));
	values = GetPropertyValues(_index,OP_FNUMBER,(PUINT16) &count, false);
	for(int i=0; i < count; i++)
	{
		QString name = QString("%1").arg((float)((UINT16)(((UINT16*)values)[i]))/100.0);
		camProp->appendValue(name,QVariant((UINT16)(((UINT16*)values)[i])));
	}

	props->addProperty(QCameraProperties::Aperture, camProp);

	camProp = new QCameraProperty("Exposures");

	GetPropertyInfo(_index, OP_EXPOSURE_PROGRAM_MODE, &prop);
	camProp->setCurrentValue(QVariant((UINT16) prop.CurrentValue.ui16Value));
	values = GetPropertyValues(_index,OP_EXPOSURE_PROGRAM_MODE,(PUINT16) &count, false);
	for(int i=0; i < count; i++)
	{
		QString name = OlympusCommon::Common()->EXPOSURE_MODES[(UINT16)(((UINT16*)values)[i])];
		camProp->appendValue(name,QVariant((UINT16)(((UINT16*)values)[i])));
	}

	props->addProperty(QCameraProperties::ExposureMode, camProp);

	GetPropertyInfo(_index, OP_EXPOSURE_INDEX, &prop);
	camProp = new QCameraProperty("ISOs");
	
	camProp->setCurrentValue(QVariant((UINT16) prop.CurrentValue.ui16Value));
	values = GetPropertyValues(_index,OP_EXPOSURE_INDEX,(PUINT16) &count, false);
	for(int i=0; i < count; i++)
	{
		QString name = OlympusCommon::Common()->isosettings[(UINT16)(((UINT16*)values)[i])];
		camProp->appendValue(name,QVariant((UINT16)(((UINT16*)values)[i])));
	}

	props->addProperty(QCameraProperties::Iso, camProp);


	GetPropertyInfo(_index, OP_EXPOSURE_TIME_EX, &prop);
	camProp = new QCameraProperty("ExposureTimes");
	
	camProp->setCurrentValue(QVariant((UINT) prop.CurrentValue.ulValue));
	values = GetPropertyValues(_index,OP_EXPOSURE_TIME_EX,(PUINT16) &count, false);
	for(int i=0; i < count*2; i +=2 )
	{

		UINT16 numerator = ((UINT16 *)values)[i+1];
		UINT16 denominator = ((UINT16 *)values)[i];

		QString name;
		if(numerator == 10)
		{
			name = QString("%1").arg(((float)denominator)/10.0);
		}
		else if(numerator == 1) name = QString("%1").arg(denominator);
		else name = QString("%1\"").arg((float)numerator/(float)denominator);
		//QString name = OlympusCommon::Common()->isosettings[(UINT)(((UINT*)values)[i])];
		camProp->appendValue(name,QVariant((UINT)(((UINT*)values)[i/2])));
	}

	props->addProperty(QCameraProperties::ExposureTimes, camProp);

	//QCDisconnect();

	
	props->addProperty(QCameraProperties::WhiteBalanceMode, getwbproperties());

	return props;
}

QCameraProperty *QOlympusCamera::getwbproperties(){

	OlympusCommon *olycommon = OlympusCommon::Common();

	QCameraProperties *props = new QCameraProperties();
	int count = 0;
	MOCHA_PROPERTY prop;

	QCameraProperty *camProp = new QCameraProperty("WhiteBalance");


	GetPropertyInfo(_index, OP_WB_MODE, &prop);
	
	//camProp->setCurrentValue(QVariant((UINT16) prop.CurrentValue.ui16Value));
	const void *values = GetPropertyValues(_index,OP_WB_MODE,(PUINT16) &count, false);

	for(int i=0; i < OlympusCommon::Common()->WHITEBALANCES.count(); i++)
	{
		QString name = OlympusCommon::Common()->WHITEBALANCES[i];
		camProp->appendValue(name,i);
	}


	switch(prop.CurrentValue.ui16Value){
		case PRM_WB_MODE_DIRECT:
			GetPropertyInfo(_index, OP_MANUAL_WB, &prop);
			camProp->setCurrentValue(OlympusCommon::Common()->MANUALWB_MODES[prop.CurrentValue.ui16Value]);
			break;
		case PRM_WB_MODE_OTWB:
			GetPropertyInfo(_index, OP_ONETOUCH_WB, &prop);
			camProp->setCurrentValue(OlympusCommon::Common()->ONETOUCHWB_MODES[prop.CurrentValue.ui16Value]);
			break;
		case PRM_WB_MODE_CUSTOM:
			GetPropertyInfo(_index, OP_CUSTOM_WB, &prop);
			camProp->setCurrentValue(OlympusCommon::Common()->CUSTOMWB_MODES[prop.CurrentValue.ui16Value]);
			break;
		default:
			camProp->setCurrentValue(0);
			break;
	}

	return camProp;

}

bool QOlympusCamera::hasBulbMode(){ 


	int bulb = GetBulbMode(_index);
	if(bulb > 0){
		_manualbulb = false;
		return true;
	}
	bool hasit = IsPropertySupported(_index, OP_BULB_MODE);
	if(!hasit)
	{
		SetBulbMode(_index,0x01E00001);

		bulb = GetBulbMode(_index);
		if(bulb > 0) {
			hasit = true;
			_manualbulb = false;
		}
		else
		{
			unsigned int val = PRM_EXP_MODE_BULB;
			hasit = IsValidPropertyValue(_index,OP_EXPOSURE_PROGRAM_MODE,&val);
			if(hasit)
			{
				_manualbulb = false;
			}
			else
			{
				_manualbulb = true;
			}
		}
	}
	else
	{
		_manualbulb = true;
	}
	return hasit; 
}



void QOlympusCamera::setCameraProperty(QCameraProperties::QCameraPropertyTypes prop, QVariant value)
{
	if(!Connected(_index))
		QCConnect();
	switch(prop)
	{
		case QCameraProperties::ResolutionMode:
			SetResolutionMode(_index, value.toUInt());
			break;
		case QCameraProperties::ImageTypes:
			break;
		case QCameraProperties::Aperture:
			SetAperture(_index, value.toUInt());
			break;
		case QCameraProperties::BulbMode:
			SetBulbMode(_index,0x0E00001);
			break;
		case QCameraProperties::ExposureMode:
			//SetExposureEx(_index, value.toUInt());
			break;
		case QCameraProperties::Iso:
			SetISO(_index, value.toUInt());
			break;
		case QCameraProperties::ExposureTimes:
			SetExposureEx(_index, value.toUInt());
			break;
		case QCameraProperties::WhiteBalanceMode:
			if(value.toUInt() == 0){
				SetWhiteBalanceMode(_index, PRM_WB_MODE_AUTO);
			}
			else if(value.toUInt() > 0 && value.toUInt() <= 12){ //DIRECT
				SetWhiteBalanceMode(_index, PRM_WB_MODE_DIRECT);
				SetManualWB(_index, OlympusCommon::Common()->MANUALWB_MODES.keys(value.toInt()).at(0));
			}
			else if(value.toUInt() > 12 && value.toUInt() <= 16){
				SetWhiteBalanceMode(_index, PRM_WB_MODE_OTWB);
				SetOneTouchWB(_index, OlympusCommon::Common()->ONETOUCHWB_MODES.keys(value.toInt()).at(0));
			}
			else if(value.toUInt() > 16 && value.toUInt() <= 20){
				SetWhiteBalanceMode(_index, PRM_WB_MODE_CUSTOM);
				SetCustomWB(_index, OlympusCommon::Common()->CUSTOMWB_MODES.keys(value.toInt()).at(0));
			}
			break;
	}

	//QCDisconnect();
}

QImage QOlympusCamera::getImage()
{
	return QImage();
}

int QOlympusCamera::QCConnect()
{
	int ret = Connect(_index);
	if(ret != 0)
	{
		MOCHA_ERROR	err;
		GetLastMochaError(&err);
		qDebug(err.strErrorMessage);
	}
	if(GetCameraControlMode(_index) == PRM_CAM_CAPTURE)
	{
		ret = SetCameraControlMode(_index,PRM_CAM_CONTROL);
		if(ret != 0)
		{
			MOCHA_ERROR	err;
			GetLastMochaError(&err);
			qDebug(err.strErrorMessage);
		}
	}

	_properties = getallproperties();
	//SetProgramMode(_index, PRM_EXP_MODE_MANUAL);

	return ret;
}

int QOlympusCamera::QCDisconnect()
{
	//SetCameraControlMode(_index,PRM_CAM_CAPTURE);

	int ret = Disconnect(_index);

	if(ret != 0)
	{
		MOCHA_ERROR	err;
		GetLastMochaError(&err);
		qDebug(err.strErrorMessage);
	}

	return ret;
}


void QOlympusCamera::image_ready(unsigned int ulObjHandle){


	if(!Connected(_index))
	{
		QCConnect();
	}

	unsigned char *buffer;

	int bufsize = ImageSize(ulObjHandle);
	int type = ImageType(ulObjHandle);

	buffer = new unsigned char[bufsize];

	int ret = GetImage(_index, ulObjHandle, buffer, bufsize);

	_imagecount++;
	QString filename;
	if(type == OBJ_FORMAT_RAW)
		filename = QString("%1/%2_%4.%3").arg(_imagedestdir).arg(_nameprefix).arg("orf").arg(_imagecount,4,10,QChar('0'));
	else
		filename = QString("%1/%2_%4.%3").arg(_imagedestdir).arg(_nameprefix).arg("jpg").arg(_imagecount,4,10,QChar('0'));

	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	QDataStream ds( &file);

	ds.writeRawData((const char *)buffer, bufsize);

	file.close();

	delete [] buffer;

	QImage image;
	if(type == OBJ_FORMAT_RAW)
	{
		//Do raw processing
		DcRImage dcraw;

		//incase the of long shutter exposure and camera hasn't finished writing and it grabs the pic before and it turns out to be jpg
		if(dcraw.isRaw(filename)){
			if(_usedarkframe && QFile::exists(_darkframe))
			{
				QStringList args;
				args += "dcrawqt";
				args += "-T";
				args += "-c";
				args += QString("-K %1").arg(_darkframe); 

				dcraw.load(filename, args);
			}
			else
				dcraw.loadthumbnail(filename);

			//QByteArray *image =dcraw.GetImage(previewFile.absoluteFilePath());

			image = dcraw.getthumbimage(); //.loadFromData(*image);
		}
	}
	else
	{
		image.load(filename);
	}

	emit image_captured(image);

	//ret = SetCameraControlMode(_index, PRM_CAM_CONTROL);

	//if(ret != 0)
	//{
	//	MOCHA_ERROR	err;
	//	GetLastMochaError(&err);
	//	qDebug(err.strErrorMessage);
	//}

	//QCDisconnect();
	emit camera_busy(false);


}