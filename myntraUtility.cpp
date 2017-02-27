#include "myntraUtility.hpp"

namespace customProjects
{
	myntraUtility::myntraUtility()
	{
		
	}
	
	QString myntraUtility::getPathFor(QString _assetName)
	{
		if(_assetName == "screenSaver")
		{
			return "/myntra/img/ScreenSaver.jpg";
		}
		else if(_assetName == "productIntroVideo")
		{
			return "/myntra/vid/gingerBread (online-video-cutter.com).mp4";
		}
		else if (_assetName == "linkingArrow")
		{
			return "/myntra/img/arrow.png";
		}
	}
}
