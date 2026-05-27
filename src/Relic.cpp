#include "Relic.h"

Relic::Relic(RelicType type, const std::string& name, const std::string& description)
    : type_(type), name_(name), description_(description) {
}
