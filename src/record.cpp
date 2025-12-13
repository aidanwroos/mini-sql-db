#include <stdlib.h>
#include <stdio.h>
#include "record.h"

//default
Record::Record(){}


//initializes private member "values" with the field values
Record::Record(const std::vector<FieldValue>& values) : values(values){}


//return the record's values
const std::vector<FieldValue>& Record::getValues() const {
    return values;
}
