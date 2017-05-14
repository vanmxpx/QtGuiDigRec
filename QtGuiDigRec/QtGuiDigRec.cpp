#include "stdafx.h"
#include "QtGuiDigRec.h"
#include "Cell.h"

QtGuiDigRec::QtGuiDigRec(QWidget *parent)
	: QMainWindow(parent), perc(new Perceptron()), layout(new QHBoxLayout(this)), inputs(15,fill::zeros), cells(15),
calcButton(new QPushButton(this)), label(new QLabel(this)), tablet(new QLCDNumber(this))
{
	ui.setupUi(this);
	if (!perc->load_weights())
		perc->learn();

	this->setWindowTitle("Digits recognizing");
	this->setFixedSize(200, 170);
	tablet->setFixedSize(90, 90);
	label->setText("Recognized number is:");
	calcButton->setText("Recognize");
	
	connect(calcButton, &QPushButton::clicked, this, &QtGuiDigRec::calculate);

	QGridLayout *grid = new QGridLayout(this);
	grid->setContentsMargins(1, 1, 1, 1);
	for(uint i = 0; i < 5; i++)
	{
		for (uint k = 0; k < 3; k++)
		{
			Cell* newCell = new Cell(k + i*3, this);
			cells.push_back(newCell);
			grid->addWidget(newCell, i, k);
			connect(newCell, &Cell::cell_checked, this, &QtGuiDigRec::on_cell_checked);
		}
	}
	QVBoxLayout* resultLauout = new QVBoxLayout(this);
	resultLauout->addWidget(calcButton);
	resultLauout->addWidget(label);
	resultLauout->addWidget(tablet);
	resultLauout->setAlignment(Qt::AlignTop);
	layout->setContentsMargins(5, 5, 5, 5);
	layout->setAlignment(Qt::AlignTop);
	layout->addLayout(grid);
	layout->addLayout(resultLauout);
	QWidget *as = new QWidget();
	as->setLayout(layout);
	this->setCentralWidget(as);
}

void QtGuiDigRec::on_cell_checked(int count, bool value)
{
	inputs.at(count) = value;
}

void QtGuiDigRec::calculate()
{
	vec result = perc->analize(inputs);
	tablet->display(int(result.index_max()));
}
