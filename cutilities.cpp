#include "cutilities.h"

CUtilities::CUtilities() {

}

int CUtilities::randInt(int low, int high) {
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}
