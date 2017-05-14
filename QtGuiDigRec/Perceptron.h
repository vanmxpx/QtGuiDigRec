#pragma once

using namespace std;
using namespace arma;

class Perceptron
{
public:
	Perceptron(int = 45, int = 10000, double = 0.3, double = 1e-6);

	vec analize(vec number);
	void learn();

	void start_test();
	bool load_weights();
	bool save_weights() const;
private:
	double normalizeAnswer(double) const;
	static double gradFunc(double answer);

	vec inputs;
	vec outputs;

	mat w;
	mat wout;
	int neur_count;
	const double epoches;
	double learn_rate;
	double alpha_mom;
	mat numbers;
	mat fives;
};

