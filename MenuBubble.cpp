#include "imageDisplayer.hpp"
#include "MenuBubble.hpp"


namespace customProjects
{
	MenuBubble::MenuBubble(float x, float y)
	{
		setBackgroundColor(1.0, 1.0, 0.0, 1.0);
		//setBackgroundColor(255, 255, 255, 0);
		setLocation(500, 500);
		//setInputFlags(INPUT_PASS_TO_CHILDREN);
		setFlags(MultiWidgets::Widget::LOCK_DEPTH);
	/*	setX(x-50);
		setY(y-50);*/
	
		auto img = MultiWidgets::create<ImageWidget>();
		if (img->load("Denium.png"))
		{
			addChild(img);
			img->setX(-(img->width() / 2));
			img->setY(-(img->height() / 2));
		//	img->setDepth(-10);
		//	img->setFixed();
		//	//img->setFlags(MultiWidgets::Widget::LOCK_DEPTH);
		//	//img->setInputFlags(InputFlags::INPUT_NONE);
		}


	

		
	}
}