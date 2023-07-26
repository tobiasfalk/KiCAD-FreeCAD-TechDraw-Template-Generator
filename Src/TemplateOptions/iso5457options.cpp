#include "iso5457options.h"

bool ISO5457Options::getTrimmingMarks() const
{
    return trimmingMarks;
}

void ISO5457Options::setTrimmingMarks(bool newTrimmingMarks)
{
    trimmingMarks = newTrimmingMarks;
}

ISO5457Options::ISO5457Options(QObject *parent)
    : QObject{parent}
{
    setTrimmingMarks(true);
}
