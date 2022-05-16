#include <iostream>

#include "Gui/MainWindow.hpp"
#include <QApplication>


// Radium includes
#include <Core/Math/DualQuaternion.hpp>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow window;
	window.show();
	return app.exec();
}
