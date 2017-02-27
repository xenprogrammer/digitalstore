#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>

namespace customProjects
{
	class myntraUtility : public MultiWidgets::Widget
	{
	public:
		myntraUtility();
		QString getPathFor(QString);
	};
}