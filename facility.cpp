#include "facility.h"

facility::facility(const QString& name, int usageMinutes) : name(name), usageMinutes(usageMinutes) {}

QString facility::getName() const {
    return name;
}

int facility::getUsageMinutes() const {
    return usageMinutes;
}
