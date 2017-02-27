#include <MultiWidgets\ItemFlowWidget.hpp>
#include <MultiWidgets/StayInsideParentOperator.hpp>
#include "RelativeMotion.hpp"
#include "MenuBubble.hpp"
#include "InteractiveBlob.hpp"
#include "myntraUtility.hpp"
#include "imageDisplayer.hpp"
#include <Luminous/Image.hpp>
#include <Nimble/Math.hpp>
#include "drawnArrow.hpp"

#define PI 3.14

namespace customProjects
{
	RelativeMotion::RelativeMotion()
	{
		setBackgroundColor(0.0, 0.0, 0.0, 0.0);
		setSize(1920, 1080);
		targetPoint = Nimble::Vector2f(400, 540);
		targetPoint1 = Nimble::Vector2f(1520, 540);

		auto menububble = MultiWidgets::create<customProjects::imageDisplayer>(this, "Denium.png", "menuBubble", true);
		menububble->setCenterLocation(Nimble::Vector2(960, 540));
		menububble->addOperator(std::make_shared<MultiWidgets::StayInsideParentOperator>());
		rotationAngle = 0;
		totalCount = 4;

		for (int i = 0; i < totalCount; i++)
		{
			auto da = MultiWidgets::create <customProjects::drawnArrow>(this, menububble);
			da->setName("drawnLine_"+(QString::number(i).toUtf8()));
			//da->setDepth(10+i*2);
			auto interactiveBlob = MultiWidgets::create<InteractiveBlob>(this, menububble, i, totalCount, 450, da);
			break;
		}

		/*
		auto da = MultiWidgets::create <customProjects::drawnArrow>(this);
		da->setName("drawnArrow");
		Radiant::BinaryData d;
		addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.01f, "changePoint", d, false));
		*/

		/*
		Luminous::Image imgObj;
		imgObj.read("face.jpg");
		Radiant::info("image width is " + (QString::number(imgObj.width())).toUtf8());
		*/

		/*
		auto ifw = MultiWidgets::create<MultiWidgets::ItemFlowWidget>(this);
		ifw->setBackgroundColor(1.0,0.0,0.0,1.0);
		addChild(ifw);
		ifw->setLocation(600, 500);

		for (int i = 1; i <= 10; i++)
		{

			auto w = MultiWidgets::create<MultiWidgets::ImageWidget>(); //MultiWidgets::WidgetPtr _parentWidget, QString _imagePath, QString _imageName, bool _isCenterAligned = false
			QString path;
			path = "images/" + QString::number(i) + ".jpg";
			w->setName(("image_" + QString::number(i)).toUtf8());
			if (w->load(path))
			{
				ifw->addItem(w);
			}
			else
			{
				Radiant::info("image not loaded " + path.toUtf8());
			}
		}

		auto button = MultiWidgets::create<Widget>();
		button->setSize(350, 150);
		button->setCenterLocation(ifw->location());
		addChild(button);
		button->setVisible(false);

		QString currentImage;

		ifw->eventAddListener("new-center-item", [=] {
			Radiant::info("new-center-item is " + ifw->topWidget()->name());
			//ifw->topWidget()->setVisible(false);

			if ((ifw->topWidget()->name() == "image_6") ||
				(ifw->topWidget()->name() == "image_8") ||
				(ifw->topWidget()->name() == "image_10") ||
				(ifw->topWidget()->name() == "image_2")
				)
			{
				//auto w = ifw->topWidget();
				//currentImage = (ifw->topWidget().dynamic_pointer_cast<MultiWidgets::ImageWidget>()->source()) + "";
				//Radiant::info("event is new-center-item " + ().toUtf8());

				//ifw->topWidget().dynamic_pointer_cast<MultiWidgets::ImageWidget>()->source()
				button->setVisible(true);
			}
			else
			{
				button->setVisible(false);
			}
		});

		
		ifw->setTouchArea(MultiWidgets::Widget::TouchArea::TOUCH_CONTENT_BOX);
		ifw->eventAddListener("finger-down", [=]
		{
			
			Radiant::info("I am tapped " + (ifw->topWidget()->name()));

			auto newImage = MultiWidgets::create<MultiWidgets::ImageWidget>();
			newImage->load(ifw->topWidget().dynamic_pointer_cast<MultiWidgets::ImageWidget>()->source());
			addChild(newImage);
			newImage->setLocation(ifw->location());
		});


		*/
	}

	/*
	void RelativeMotion::renderBackground(Luminous::RenderContext & r) const
	{
		//Radiant::info("RelativeMotion renderBackground ");
	
		Nimble::Vector2 center = Nimble::Vector2(0,0);
		float radius = 100;
		Luminous::Style s;		
		s.setFillColor(Radiant::Color(1, 0, 1, 1));
		r.drawRect(Nimble::Rect(0, 0, 500, 200), s);
		r.drawRect(Nimble::Rect(200, 200, 500, 700), s);
		s.fill();
		s.setStrokeColor(Radiant::Color(0.2, 1, 0.5, 1));
		s.setStrokeWidth(5);
		r.drawLine(Nimble::Vector2f(100, 100), Nimble::Vector2f(200, 100), s);
		r.drawLine(Nimble::Vector2f(200, 100), Nimble::Vector2f(200, 400), s);
		r.drawLine(Nimble::Vector2f(200, 400), Nimble::Vector2f(100, 400), s);
		r.drawLine(Nimble::Vector2f(100, 400), Nimble::Vector2f(100, 100), s);
	}
	*/

	void RelativeMotion::eventProcess(const QByteArray & messageId, Radiant::BinaryData & data)
	{
	}

	MultiWidgets::WidgetPtr RelativeMotion::getChildByName(QString _childName)
	{
		for (auto ci = childBegin(); ci != childEnd(); ++ci)
		{
			MultiWidgets::WidgetPtr w = (*ci);
			if (w->name() == _childName)
			{
				return w;
			}
		}
	}

	MultiWidgets::WidgetPtr RelativeMotion::getChildInBaseWidgetByType(MultiWidgets::WidgetPtr _parent, QString _classType)
	{

		if (_classType == "InteractiveBlob")
		{
			for (auto ci = _parent->childBegin(); ci != _parent->childEnd(); ++ci)
			{
				MultiWidgets::WidgetPtr w = (*ci);
				if (w.dynamic_pointer_cast<customProjects::InteractiveBlob>() != nullptr)
				{
					return w;
				}
			}
		}
		
	}


	Nimble::Vector2f RelativeMotion::getRotatedPoint(Nimble::Vector2f _point, float _radius, float _angle)
	{
		float xC;
		xC = _point.x + _radius * cos(_angle);
		float yC;
		yC = _point.y + _radius * sin(_angle);
		Nimble::Vector2 tmpPoint = Nimble::Vector2f(xC, yC);
		return tmpPoint;
	}
}
