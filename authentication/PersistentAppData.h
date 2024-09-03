#ifndef PersistentAppData_h
#define PersistentAppData_h

#include <string>
namespace authentication {
    class PersistentAppData {
    private:
        static std::unique_ptr<PersistentAppData> instance;
    public:
        static PersistentAppData* getInstance() {
            if(instance.get() == nullptr)
                instance.reset(new PersistentAppData());
            return  instance.get();
        }
        void saveData(const std::string, const std::string);
        const std::string getData(const std::string);
    };
}


#endif /* PersistentAppData_h */
