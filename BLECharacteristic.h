#ifndef _BLE_CHARACTERISTIC_H_
#define _BLE_CHARACTERISTIC_H_

#include "BLEAttribute.h"

enum BLEProperty {
  BLERead                 = 0x02,
  BLEWriteWithoutResponse = 0x04,
  BLEWrite                = 0x08,
  BLENotify               = 0x10,
  BLEIndicate             = 0x20
};

enum BLECharacteristicEvent {
  BLEWritten = 0,
  BLESubscribed = 1,
  BLEUnsubscribed = 2
};

class BLECentral;
class BLECharacteristic;

typedef void (*BLECharacteristicEventHandler)(BLECentral& central, BLECharacteristic& characteristic);

class BLECharacteristicValueChangeListener
{
  public:
    virtual void characteristicValueChanged(BLECharacteristic& characteristic) = 0;
};

class BLECharacteristic : public BLEAttribute
{
  friend class BLEPeripheral;

  public:
    BLECharacteristic(const char* uuid, unsigned char properties, unsigned char valueSize);
    BLECharacteristic(const char* uuid, unsigned char properties, const char* value);

    virtual ~BLECharacteristic();

    unsigned char properties() const;

    unsigned char valueSize() const;
    const unsigned char* value() const;
    unsigned char valueLength() const;

    void setValue(const unsigned char value[], unsigned char length);
    void setValue(const char* value);

    bool written();
    bool subscribed();

    void setEventHandler(BLECharacteristicEvent event, BLECharacteristicEventHandler eventHandler);

  protected:
    void setValue(BLECentral& central, const unsigned char value[], unsigned char length);
    void setSubscribed(BLECentral& central, bool written);

    void setValueChangeListener(BLECharacteristicValueChangeListener& listener);

  private:
    unsigned char                         _properties;
    unsigned char                         _valueSize;
    unsigned char*                        _value;
    unsigned char                         _valueLength;

    bool                                  _written;
    bool                                  _subscribed;

    BLECharacteristicValueChangeListener* _listener;
    BLECharacteristicEventHandler         _eventHandlers[3];
};

#endif
