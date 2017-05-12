#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiDigRec.h"

class QtGuiDigRec : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiDigRec(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiDigRecClass ui;
};
