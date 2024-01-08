# CYD28_Touchscreen
Bit banged XPT2046 SPI library for the CheapYellowDisplay 2.8" version.  

The touchscreen interface on the 2.8" version of the CYD is available on completely different pins as both SPI interfaces.  
This library is based on the XPT2046 lib written by Paul Stoffregen, but instead of HW SPI it is using a bit banged version leaving the both HSPI and VSPI interfaces for other tasks like handling the SD card or driving the display.  

Pinout is fixed in the header file, using the configuration present on the CYD 2.8" board:
```
#define CYD28_TouchR_IRQ 	36
#define CYD28_TouchR_MOSI 	32
#define CYD28_TouchR_MISO 	39
#define CYD28_TouchR_CLK 	25
#define CYD28_TouchR_CS 	33
```

## PlatformIO  
Simply add the library url to the lib_deps in the `platformio.ini` file:  
```
lib_deps =
	https://github.com/hexeguitar/CYD28_Touchscreen
```  
## LVGL8.x  
Create the touchscreen object + input device driver for the lvgl library:  
```
CYD28_TouchR ts = CYD28_TouchR(CYD28_DISPLAY_HOR_RES, CYD28_DISPLAY_VER_RES);
CYD28_TS_Point oldPoint;
lv_indev_drv_t indev_drv;
```  
Configure it:  
```
lv_indev_drv_init(&indev_drv);
indev_drv.type = LV_INDEV_TYPE_POINTER;
indev_drv.read_cb = touch_read;
lv_indev_drv_register(&indev_drv);
```  
Create read callback:  
```
void touch_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    if (dispPtr->ts.touched())
    {
        CYD28_TS_Point p = dispPtr->ts.getPointScaled();
        data->state = LV_INDEV_STATE_PR;
        data->point.x = p.x;
        data->point.y = p.y;
        dispPtr->oldPoint.x = p.x;
        dispPtr->oldPoint.y = p.y;
        //log_i("X = %d, Y = %d", data->point.x, data->point.y);
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
        data->point.x = dispPtr->oldPoint.x;
        data->point.y = dispPtr->oldPoint.y;
    }
}
```  
## [See here for a full example project using this library][1]

---  
(c) 01.2024 by Piotr Zapart  
www.hexefx.com  

[1]: https://github.com/hexeguitar/ESP32_TFT_PIO