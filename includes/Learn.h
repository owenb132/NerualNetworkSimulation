#ifndef LEARN_H
#define LEARN_H

#include <vector>
#include "Object.h"
#include "NeuralNetwork.h"

class Learn {
	public:
		Learn() 
		:	o1(0), o2(0)
		{}
		~Learn() {
			clear();	
		}

		void insert(Object* r);
		void clear() { 
			for (int i = 0; i < object_.size(); ++i)
				delete object_[i]; 

			object_.clear();
		}

		NeuralNetwork* newBrain(double percentToTake = 0.5);

	private:
		std::vector< Object* > object_;
		int o1, o2;										// best two robot positions in robot_

		int score(int pos);
		void bestTwo();
};

#endif