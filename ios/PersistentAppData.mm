#include "authentication/PersistentAppData.h"
#include "KeychainHelper.h"

namespace authentication {
std::unique_ptr<PersistentAppData> PersistentAppData::instance;
void PersistentAppData::saveData(const std::string key, const std::string value) {
    KeychainHelper::saveStringValue(key, value);
}

const std::string PersistentAppData::getData(const std::string key) {
    return KeychainHelper::getStringValue(key);
}
}

