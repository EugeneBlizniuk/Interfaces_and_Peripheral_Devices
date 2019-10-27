#ifndef BATTERY_H
#define BATTERY_H


class Battery
{
public:
    Battery() {}
    ~Battery() {}

    void setPercentage(unsigned int);
    void setIsOnline(bool);
    void setIsSaverOn(bool);

    unsigned int getPercentage();
    bool getIsOnline();
    bool getIsSaverOn();
private:
    unsigned int percentage = 0;
    bool isOnline = false;
    bool isSaverOn = false;
};

#endif // BATTERY_H
