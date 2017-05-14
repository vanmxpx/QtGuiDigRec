#pragma once

#include <QPushButton>

class Cell
	: public QPushButton
{
	Q_OBJECT
public:
	Cell(uint id,QWidget* parent = nullptr);
public slots:
	void on_parent_clicked();
signals:
void cell_checked(int, bool);
private:
	bool pushed;
	uint id;
};

