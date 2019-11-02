#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

inline PersonAddressBuilder PersonBuilder::lives(){
    return PersonAddressBuilder{ person };
}
inline PersonJobBuilder PersonBuilder::works(){
    return PersonJobBuilder{ person };
}
