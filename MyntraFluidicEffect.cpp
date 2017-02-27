
/// [Include application header]
#include <MultiWidgets/Application.hpp>
#include "RelativeMotion.hpp"

/// [Declare main]
int main(int argc, char ** argv)
{
/// [Declare main]

  /// [Init application]
  MultiWidgets::Application app;

  bool ok = app.init(argc, argv);
  if(!ok)
    return 1;
  /// [Init application]

	auto relMotion = MultiWidgets::create<customProjects::RelativeMotion>();
	app.mainLayer()->addChild(relMotion);


  /// [Create widgets]
  
  /// [Run application]
  // Run the application:
  return app.run();
}
/// [Run application]



