#pragma once
/*
	Classe de base permettant l'utilisation de différentes fonction d'activation
*/
class ActivationFunction
{
public:
	virtual double compute(double entry) const;
	virtual double performThresholding(double entry) const;
};