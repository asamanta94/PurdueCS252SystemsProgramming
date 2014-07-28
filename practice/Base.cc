#include <stdio.h>
#include "Base.h"

void
Base::foo() {
	printf("Hello\n");
}

Base::Base()
{
	val = 1;
}

Base::~Base()
{
	val = 0;
	printf("Destructing");
}
