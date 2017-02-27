/* Copyright (C) 2007-2013 Multi Touch Oy, Finland, http://www.multitaction.com
 *
 * This file is part of MultiTouch Cornerstone.
 *
 * All rights reserved. You may use this file only for purposes for which you
 * have a specific, written permission from Multi Touch Oy.
 *
 */
#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>
#include "imageDisplayer.hpp"


namespace customProjects
{
	imageDisplayer::imageDisplayer(MultiWidgets::WidgetPtr _parentWidget, QString _imagePath, QString _imageName, bool _isCenterAligned = false):ImageWidget()
	{
		isImageLoaded = false;
		eventAddOut("imageLoaded");
		//setBackgroundColor(1.0f, 0.0f, 0.0f, 1.0f);

		parentWidget = _parentWidget;
		imagePath = _imagePath;
		imageName = _imageName;
		isCenterAligned = _isCenterAligned;
		parentWidget->addChild(this);  

		setName(imageName.toUtf8());

		Radiant::BinaryData d;
		auto ms = std::make_shared<MultiWidgets::MessageSendOperator>(0.1f, "checkForLoading", d, false);
		ms->setName("loadingTest");
		addOperator(ms);

		if (load(imagePath))
		{
			if (isCenterAligned)
			{
				alignToCenter();
			}
			isImageLoaded = true;
			//eventSend("imageLoaded");
		}
	}

	void imageDisplayer::setMyLocation(Nimble::Vector2 _coordinates)
	{
		setLocation(_coordinates);
	}

	Nimble::Vector2 imageDisplayer::getMylocation()
	{
		return location();
	}

	void imageDisplayer::setMyScale(float _scaleValue)
	{
		setScale(_scaleValue);
	}

	float imageDisplayer::getMyScale()
	{
		return scale();
	}

	void imageDisplayer::setMyOpacity(float _alphaValue)
	{
		setOpacity(_alphaValue);
	}

	float imageDisplayer::getMyOpacity()
	{
		return opacity();
	}

	void imageDisplayer::setMyRotation(float _rotationValue)
	{
		setRotation(_rotationValue);
	}

	float imageDisplayer::getMyRotation()
	{
		return rotation();
	}

	void imageDisplayer::alignToCenter()
	{
		setX(x() - (width() / 2));
		setY(y() - (height() / 2));
	}

	void imageDisplayer::animateMyLocation(Nimble::Vector2 _startLocation, Nimble::Vector2 _endLocation, float _duration)// starting point, ending point, duration
	{
		MultiWidgets::AnimationCurve<Nimble::Vector2> curverForLocation;
		curverForLocation.addKey(0.f, _startLocation);
		curverForLocation.addKey(_duration, _endLocation);

		MultiWidgets::AnimationClip clipForLocation;
		clipForLocation.setCurve("location", curverForLocation);
		clipForLocation.setWrapMode(MultiWidgets::AnimationClip::ONCE);

		QString tStr;
		tStr = getImageName();
	
		animation().addClip("locationAnim", clipForLocation);
		animation().play("locationAnim");
	}

	void imageDisplayer::animateMyScale(float _startScale, float _endScale, float _duration)//starting scale value, ending scale value, duration
	{

	}	

	void imageDisplayer::animateMyOpacity(float _startOpacity, float _endOpacity, float _duration)//starting opacity value, ending opacity value, duration
	{
		MultiWidgets::AnimationCurve<float> curverForOpacity;
		curverForOpacity.addKey(0.f, _startOpacity);
		curverForOpacity.addKey(_duration, _endOpacity);

		MultiWidgets::AnimationClip clipForOpacity;
		clipForOpacity.setCurve("opacity", curverForOpacity);
		clipForOpacity.setWrapMode(MultiWidgets::AnimationClip::ONCE);

		animation().addClip("opacityAnim", clipForOpacity);
		animation().play("opacityAnim");
	}

	void imageDisplayer::animateMyRotation(float _startRotation, float _endRotation, float _duration)//starting opacity value, ending opacity value, duration
	{
		// Create animation curve with floating-point key-frames
		auto curve = MultiWidgets::AnimationCurveFloat();
		curve.addKey(0, 3);
		curve.addKey(3, 4);

		

		// Create animation clip and map the curve to "rotation" attribute. Also set the clip to loop
		auto clip = MultiWidgets::AnimationClip();
		clip.setCurve("rotation", curve);
		clip.setWrapMode(MultiWidgets::AnimationClip::LOOP);

		// Add the animation clip to a widget and give it a name for reference
		animation().addClip("my-animation", clip);

		// Play animation
		animation().play("my-animation");

	/*	for (int i = 0; i < 90; i++)
		{
			float ang = i *(3.14 / 180);
			setRotationAboutCenter(ang);

		}*/
	}

	void imageDisplayer::eventProcess(const QByteArray & messageId, Radiant::BinaryData & data)
	{
		/*
		if (animation().isPlaying("opacityAnim"))
		{
		}
		else
		{
		}
		*/

		if (messageId == "checkForLoading"&& isImageLoaded)
		{
			eventSend("imageLoaded");
			isImageLoaded = false;
		}
	}

	QString imageDisplayer::getImageName()
	{
		return imageName;
	}	

	void imageDisplayer::animComplete()
	{

	}
}
