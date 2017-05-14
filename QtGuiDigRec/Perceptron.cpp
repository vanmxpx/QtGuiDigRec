#include "stdafx.h"
#include "Perceptron.h"

using namespace arma;
using namespace std;
/*presented neural network what analizing a number by reading black/white picture 3*5 with a nubmer from 0 to 9
*network has 15 input neurons, 45 neurons by default in hidden layer and 10 output neurons to each number.
*Sinapses binded to all next layer neurons*/

Perceptron::Perceptron(int nr, int ep, double lr, double am)
	: inputs(15), outputs(nr, fill::zeros),
	w(15, nr, fill::randn), wout(nr, 10, fill::randn),
	neur_count(nr), epoches(ep), learn_rate(lr), alpha_mom(am)
{
	numbers = { { 1,0,1,1,1,1,1,1,1,1 },
	{ 1,0,1,1,0,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,1,1,1,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,0,0,1,1,1 },
	{ 1,0,1,1,1,1,1,0,1,1 },
	{ 0,0,1,1,1,1,1,0,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,0,0,1,0,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,0,1,1,1,1,1,1,1 },
	{ 1,0,1,1,0,1,1,0,1,1 },
	{ 1,0,1,1,0,1,1,0,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1 } };

	fives = { { 1,1,1,1,1,1 },
	{ 1,1,1,1,1,1 },
	{ 1,1,1,0,0,1 },
	{ 1,1,1,1,1,1 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 1,0,0,1,1,1 },
	{ 1,1,1,1,1,0 },
	{ 1,0,1,1,1,1 },
	{ 0,0,0,0,0,0 },
	{ 0,0,0,0,0,0 },
	{ 0,1,1,1,1,1 },
	{ 1,1,1,1,0,1 },
	{ 1,1,1,1,1,1 },
	{ 1,1,1,1,1,1 } };
}

vec Perceptron::analize(vec number)
{
	vec result(10, fill::zeros);
	inputs = number;
	double tmp;
	for (int row = 0; row < neur_count; row++)
	{
		//inputs sinapses
		tmp = 0;
		for (int col = 0; col < 15; col++)
			tmp += inputs.at(col) * w.at(col, row);
		outputs.at(row) = normalizeAnswer(tmp);
	}
	//hidden sinapses
	for (int row = 0; row < 10; row++)
	{
		tmp = 0;
		for (int col = 0; col < neur_count; col++)
			tmp += outputs.at(col) * wout.at(col, row);
		result.at(row) = normalizeAnswer(tmp);
	}
	return result;
}

void Perceptron::start_test()
{
	//Test
	for (int i = 0; i < 10; i++)
	{
		cout << "This number [" << i << "] is: ";
		vec res = analize(numbers.col(i));
		cout << res.index_max() << " result" << endl;
	}
	//Control
	for (int i = 0; i < 6; i++)
	{
		cout << "This number from fives[" << i << "] is: ";
		vec res = analize(fives.col(i));
		cout << res.index_max() << " result" << endl;
	}
}
bool Perceptron::save_weights() const {

	return w.save("digits_wghts.mat") &&
		wout.save("digits_wghts_out.mat");
}
bool Perceptron::load_weights() {
	mat loadw;
	mat loadwout;
	if (loadw.load("digits_wghts.mat") &&
		loadwout.load("digits_wghts_out.mat"))
	{
		w = loadw;
		wout = loadwout;
		return true;
	}
	return false;
}

double Perceptron::normalizeAnswer(double answer) const
{
	return 1 / (1 + exp(-answer));
}
double Perceptron::gradFunc(double answer)
{
	return(1 - answer)*answer;
}

void Perceptron::learn()
{
	mat delta(neur_count, 3);
	mat grad(15, neur_count);
	mat gradout(neur_count, 10);
	mat wlast(15, neur_count, fill::zeros);
	mat woutlast(neur_count, 10, fill::zeros);

	vec err(10, fill::ones);
	vec res(10);
	vec expected(10);
	for (int i = 0; i < epoches; i++) //&& err != 0
	{
		for (int k = 0; k < 10; k++)
		{
			delta.fill(fill::zeros);
			grad.fill(fill::zeros);
			gradout.fill(fill::zeros);
			//analize
			res = analize(numbers.col(k));

			//Calc errors
			for (int e = 0; e < 10; e++)
				expected.at(e) = k == e;

			err = pow(expected - res, 2);

			//
#ifndef DEBUG
			cout << err.at(k) << endl;
#endif
			//Error spread
			//Calc deltaes
			for (int row = 0; row < 10; row++) //OUT delta func
				delta.at(row, 2) = (expected.at(row) - res.at(row)) * gradFunc(res.at(row));

			double tmp;
			for (int row = 0; row < neur_count; row++)
			{
				tmp = 0;
				for (int col = 0; col < 10; col++)//summ of weights, what binded to output neuron
					tmp += wout.at(row, col) * delta.at(col, 2);

				delta.at(row, 1) = gradFunc(outputs.at(row)) * tmp;
			}

			//Calc grad
			for (int row = 0; row < neur_count; row++)
			{
				for (int col = 0; col < 15; col++)
				{
					if (col < 10)
					{
						gradout.at(row, col) = outputs.at(row) * delta(col, 2);
						wout.at(row, col) += learn_rate * gradout.at(row, col) + alpha_mom * woutlast.at(row, col);
					}
					grad.at(row, col) = inputs.at(col) * delta.at(row, 1);
					w.at(row, col) += learn_rate * grad.at(row, col) + alpha_mom * wlast.at(row, col);
				}
			}
			///Uncomment to implement more layers
			///for (int col = 0; col < 15; col++) //for input neirons
			///{
			///	delta.at(col, 0) = gradFunc(tmp);
			///	for (int row = 0; row < 15; row++)
			///		delta.at(col, 0) += w.at(row, col) * delta.at(col, 1);
			///}

			wlast = w;
			woutlast = wout;
		}
	}
}
