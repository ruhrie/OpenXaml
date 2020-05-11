#include "xml/UID.h"

namespace xut
{
    unsigned int UID = 0; /// A counter to gurarantee unique variable names

    unsigned int GetUID()
    {
        return UID++;
    }
} // namespace xut