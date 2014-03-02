

/*================================================================================================*/
/*   Author : Yuan Xiang																	   */
/*   Role :	Idle Screen 																	   */
/*   Reference documents : TN Idle Screen														   */
/*================================================================================================*/
/* Comments :																					   */
/* 	file	: 										   */
/* 	Labels	:																				   */
/*================================================================================================*/
/* Modifications	(month/day/year)															   */
/*================================================================================================*/
/* date	| author	   |FeatureID					|modification							   */
/*=========|==============|============================|==========================================*/
/*02/27/13 |Yuan Xiang    |PR407669-Yuanxiang-001 | No ¡°Maker¡±and ¡°Model¡±in image details screen*/
/*=========|==============|============================|==========================================*/


#include <stdlib.h>
#include <stdio.h>
#include "camera_custom_if.h"
//PR407669-yuanxiang-begin
#define LOG_TAG "custm_SetExif"
#include <utils/Log.h>
#include <cutils/properties.h>
//PR407669-yuanxiang-end

namespace NSCamCustom
{


#define EN_CUSTOM_EXIF_INFO
//PR407669-yuanxiang-begin
//MINT32 custom_SetExif(void **ppCustomExifTag)
//{
//#ifdef EN_CUSTOM_EXIF_INFO
//#define CUSTOM_EXIF_STRING_MAKE  "custom make"
//#define CUSTOM_EXIF_STRING_MODEL "custom model"
//#define CUSTOM_EXIF_STRING_SOFTWARE "custom software"
//static customExifInfo_t exifTag = {CUSTOM_EXIF_STRING_MAKE,CUSTOM_EXIF_STRING_MODEL,CUSTOM_EXIF_STRING_SOFTWARE};
MINT32 custom_SetExif(void **ppCustomExifTag)
{
#ifdef EN_CUSTOM_EXIF_INFO
    char model[32];
    char manufacturer[32];
    property_get("ro.product.display.model", model, "default");
    ALOGI("custom_SetExif model= %s",model);
    property_get("ro.product.manufacturer", manufacturer, "default");
    ALOGI("custom_SetExif manufacturer= %s",manufacturer);
    //#define CUSTOM_EXIF_STRING_MAKE  "custom make"
    //#define CUSTOM_EXIF_STRING_MODEL "custom model"
    static customExifInfo_t exifTag = { 0 };
    for (int i = 0; i < 32; i++) {
        if (model[i] != '\0' && i < strlen(model)) {
            exifTag.strModel[i] = (unsigned char) model[i];
        } else {
            exifTag.strModel[i] = '\0';
        }
        if (manufacturer[i] != '\0' && i < strlen(manufacturer)) {
            exifTag.strMake[i] = (unsigned char) manufacturer[i];
        } else {
            exifTag.strMake[i] = '\0';
        }
    }
//PR407669-yuanxiang-end
    if (0 != ppCustomExifTag) {
        *ppCustomExifTag = (void*)&exifTag;
    }
    return 0;
#else
    return -1;
#endif
}
//
customExif_t const&
getCustomExif()
{
    static customExif_t inst = {
        bEnCustom       :   false,  // default value: false.
        u4ExpProgram    :   0,      // default value: 0.    '0' means not defined, '1' manual control, '2' program normal
    };
    return inst;
}
//
MINT32 get_atv_disp_delay(MINT32 mode)
{
    return ((ATV_MODE_NTSC == mode)?ATV_MODE_NTSC_DELAY:((ATV_MODE_PAL == mode)?ATV_MODE_PAL_DELAY:0));
}

MINT32 get_atv_input_data()
{
    return ATV_INPUT_DATA_FORMAT;
}

};  //NSCamCustom

