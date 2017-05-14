#include "stdafx.h"
#include "Cell.h"

Cell::Cell(uint id,QWidget* parent)
	: QPushButton(parent),pushed(false), id(id)
{
	connect(this, &Cell::clicked, this, &Cell::on_parent_clicked);
	this->setText("");
	this->setFixedSize(30, 30);
	this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #CECECE, stop: 1 #FFFFFF);");
}

void Cell::on_parent_clicked()
{
	pushed = !pushed;
	if (pushed)
		this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #000000, stop: 1 #7A7A7A);");
	else
		this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #CECECE, stop: 1 #FFFFFF);");
	emit cell_checked(id, pushed);
}
