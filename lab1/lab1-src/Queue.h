#include "List.h"

class Queue : public List {
public:
	void enqueue(int val);
	int dequeue();
};
