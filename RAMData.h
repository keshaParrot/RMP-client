#ifndef RAMDATA_H
#define RAMDATA_H

class RAMData {
  public:
    float load;
    float total;
    float used;
    float virtualUsed;
    float available;
    float virtualAvailable;

    RAMData();
};

#endif  // RAMDATA_H
