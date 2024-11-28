#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <Arduino.h> 

class Dictionary {
  private:
    String keys[10];
    float values[10];
    int count;

  public:
    Dictionary();
    void add(String key, float value);
    String getKey(int index);
    float getValue(int index);
    int size();
};

#endif  // DICTIONARY_H
