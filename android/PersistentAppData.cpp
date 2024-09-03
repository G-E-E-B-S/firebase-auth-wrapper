#include "authentication/PersistentAppData.h"
namespace authentication {

    // TODO: remove singleton
    std::unique_ptr<PersistentAppData> PersistentAppData::instance;

    void PersistentAppData::saveData(const std::string, const std::string) {
        // NOTE: Do nothing in android
    }

    const std::string PersistentAppData::getData(const std::string) {
        return "";
    }
}
