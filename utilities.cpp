#include <QtGlobal>
#include "utilities.h"

Utilities::Utilities() {

}

int Utilities::randInt(int low, int high) {
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}
