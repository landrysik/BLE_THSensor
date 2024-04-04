# BLE_THSensor
This repository contains modified BLE firmware from pvvx for (originally zigbee) Tuya thermometers based on [TS0201](https://pvvx.github.io/TS0201_TZ3000) to allow usage of Sensirion SHT40 sensor IC.

## Motivation
I needed some wireless thermometers for more "industrial" applications in my smart home setup where I can't use the whole thermometer body for measure and need only small remote probe. For example in underfloor heating, HVAC (air temperature + RH for intake and exhaust air) or in hot water boiler with solar thermal system (glycol pipe temperature to/from storage tank). 

This sensor uses CHT8305 sensing chip which I was not able to buy in "probe form factor". On the other hand SHT40 sensors are available on aliexpress in variety of custom probe-style designs. I previously used modified LYWSD03MMC xiaomi sensors which use SHT40 from factory (so only simple hardware mod was required) but those sensors have LCD screen (which is not needed in most applications) and only use small CR2032 battery (200mAh) with small lifespan. On the other hand this TS0201 uses 2xAAA battery (1200mAh when LiFeS2 cell used) and is more suitable for long term remote sensing where the LCD display is not needed.
To use SHT40 in this thermometer I needed to do some modification of the firmware - this is the reason this repository was created

## Result
This is the final result - thermoemter with remote sensing probe. 
![PXL_20240307_185227133](https://github.com/landrysik/BLE_THSensor/assets/124715451/58f63bc2-2a85-486c-a338-33f6cc31ad95)

## Modification
> [!NOTE]
> First get the pvvx firmware working and verify everything works fine. More info here: https://github.com/pvvx/BLE_THSensor/issues/3

To do the actual mod, open the thermometer body and desolder the original sensing chip (hot air or just be bit brutal with soldering iron, we won't need the chip...)
Drill the hole in the top cover and feed through the wire from the SHT40 sensing probe. Solder the wires according to the image below directly on the ZTU module (it has nice thick pads).![PXL_20240307_183910697](https://github.com/landrysik/BLE_THSensor/assets/124715451/11ee4473-1e1f-4232-a5e7-961d3af75bef)

The thermometer should work (transmit BLE packets) and you should be able to connect with TelinkFlasher to modify settings etc. But will report 0.0°C/0% RH as it has now unknown chip.
## Flash the modified firmware
Open Telink Flasher (see original pvvx site) and select firmware update file and flash the modified .bin file.
After flashing the thermometer should work as usual and report correct temperature and relative humidity.

If anybody reads this - (work in progress, will add more info later) And yes, the actual firmware :)
