#include <stdio.h>
#include <stdlib.h>

// the type of structure or union is completed when closing } 
// of its declaration is seen; it must contain at least
// one member or the behaviour is undefined
//

struct xyz {
	int x;
} var1;

main(void)
{
	struct xyz; // new incomplete type struct xyz
	struct abc {
		struct xyz *p;
	} var2;
	struct xyz {
		struct abc *p;
	} var3;
}
