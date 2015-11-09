#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include "Functions.h"

class Neuron {
 public:
   Neuron() {}
   Neuron(const Neuron & n)
   : weights(n.getWeights()), inputs(n.getInputs())
   {}

  std::vector< double > getWeights() const { return weights; }
  std::vector< double > getInputs() const { return inputs; }

   // the purpose of this function is to sum up all the
   // weights * x
   // Note: this is essentially:
   //   weights vector (dot product) x vector
   double fire();

   void insert(const double &);
   void insertw(const double &);
   void clear();

   void setWeight(const double value, const int pos) { weights[pos] = value; }

 private:
  std::vector< double > weights;
  std::vector< double > inputs;
};

#endif