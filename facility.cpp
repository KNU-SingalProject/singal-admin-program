#include "facility.h"

// facility.cpp
facility::facility(const QString& name, int usageMinutes, int facilityId)
    : name(name), usageMinutes(usageMinutes), facilityId(facilityId) {}

QString facility::getName() const {
    return name;
}

int facility::getUsageMinutes() const {
    return usageMinutes;
}

