/* Copyright (C) 2007-2013 Multi Touch Oy, Finland, http://www.multitaction.com
 *
 * This file is part of MultiTouch Cornerstone.
 *
 * All rights reserved. You may use this file only for purposes for which you
 * have a specific, written permission from Multi Touch Oy.
 *
 */
#ifndef AAA_HEADER
#define AAA_HEADER

#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>
#include <Nimble/Random.hpp>
#pragma once
namespace customProjects
{
	class imageDisplayer : public MultiWidgets::ImageWidget
	{
		public:
			MultiWidgets::WidgetPtr parentWidget;
			QString imagePath;
			QString imageName;
			bool isCenterAligned;

			MultiWidgets::MessageSendOperator *mso;

			imageDisplayer(MultiWidgets::WidgetPtr, QString, QString, bool);

			void setMyLocation(Nimble::Vector2);
			Nimble::Vector2 getMylocation();

			void setMyScale(float);
			float getMyScale();

			void setMyOpacity(float);
			float getMyOpacity();
			
			void setMyRotation(float);
			float getMyRotation();

			void alignToCenter();

			void animateMyLocation(Nimble::Vector2, Nimble::Vector2, float);// starting point, ending point, duration
			void animateMyScale(float, float, float);//starting scale value, ending scale value, duration
			void animateMyOpacity(float, float, float);//starting opacity value, ending opacity value, duration
			void animateMyRotation(float, float, float);
			QString getImagePath();
			//starting rotation value, end rotation value, duration
			QString getImageName();

			virtual void eventProcess(const QByteArray & messageId, Radiant::BinaryData & data) OVERRIDE;

			void animComplete();

			bool isImageLoaded;
	};
}

#endif