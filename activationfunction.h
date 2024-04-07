#pragma once
class ActivationFunction
{
public:
	virtual double compute(double entry) const;
	virtual double performThresholding(double entry) const;
};