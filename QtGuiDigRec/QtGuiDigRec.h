#pragma once

#include <QtWidgets/QMainWindow>
#include <QHBoxLayout>
#include "Perceptron.h"
#include "ui_QtGuiDigRec.h"
#include "GeneratedFiles/ui_QtGuiDigRec.h"
#include "Cell.h"

class QtGuiDigRec : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiDigRec(QWidget *parent = Q_NULLPTR);
private slots:
	void on_cell_checked(int, bool);
private:
	void calculate();
	Ui::QtGuiDigRecClass ui;
	Perceptron* perc;
	QHBoxLayout* layout;

	arma::vec inputs;
	QVector<Cell*> cells;
	QPushButton* calcButton;
	QLabel* label;
	QLCDNumber* tablet;

};
