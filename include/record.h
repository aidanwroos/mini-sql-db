#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <variant>

using namespace std;
using FieldValue = std::variant<int, string, float, bool>;

class Record {
    private:
        std::vector<FieldValue> values;

    public:
        Record() = default;
        Record(const std::vector<FieldValue>& values);

        //Accessors (get value, add value)
        const std::vector<FieldValue>& getValues() const;
        void addValue(const FieldValue& value);

        //Serialize into byte stream for storage in Page slot
        std::vector<char> serialize() const;

        //Deserialize byte stream into Record object
        static Record deserialize(const std::vector<char>& bytestream);
    
};





#endif 