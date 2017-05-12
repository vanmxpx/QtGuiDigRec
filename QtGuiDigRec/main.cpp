#include "stdafx.h"
#include "QtGuiDigRec.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiDigRec w;
	w.show();
	return a.exec();
}
