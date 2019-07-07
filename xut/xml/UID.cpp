#include "xml/UID.h"

unsigned int UID = 0;

unsigned int GetUID()
{
	return UID++;
}