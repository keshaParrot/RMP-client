#include "MyDictionary.h"

Dictionary::Dictionary() : count(0) {}

void Dictionary::add(String key, float value) {
    if (count < 10) {
        keys[count] = key;
        values[count] = value;
        count++;
    }
}

String Dictionary::getKey(int index) {
    if (index >= 0 && index < count) {
        return keys[index];
    }
    return "";
}
float Dictionary::getValue(int index) {
    if (index >= 0 && index < count) {
        return values[index];
    }
    return -1;
}

int Dictionary::size() {
    return count;
}
