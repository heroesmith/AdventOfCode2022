#include "AdventOfCode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
      QApplication app(argc, argv);
	  
      // IHM
      AdventOfCode::AdventOfCode w(app.arguments());
      w.show();

      // Et c'est partiiii !
      return app.exec();
}
