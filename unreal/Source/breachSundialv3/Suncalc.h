// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Suncalc.generated.h"

#define PIE         3.14159265358979323846  // redefine PI
#define TWO_PI      6.28318530717958647693
#define RADEG       (180.0 / PIE)           // convert RAD to DEG
#define DEGRAD      (PIE / 180.0)           // convert DEG to RAD
#define HOURAD      (15.0 * DEGRAD)         // convert to HOUR RADI
#define fromhour(x) (x * 15.0)              // convert HOUR to DEGREES
#define tohour(x)   (x / 15.0)              // convert DEGREES to HOUR
#define sind(x)     sin((x) * DEGRAD)
#define cosd(x)     cos((x) * DEGRAD)
#define tand(x)     tan((x) * DEGRAD)
#define asind(x)    (RADEG * asin(x))
#define acosd(x)    (RADEG * acos(x))
#define atand(x)    (RADEG * atan(x))
#define atan2d(y,x) (RADEG * atan2((y),(x)))

/*
 
 Revision Date 08.02.2017
 
 SOURCES
 1. http://www.stjarnhimlen.se/comp/tutorial.html#1
 
 X axis points to the celestial equator in the south, the Y axis to the horizon in the west, and the Z axis to the north celestial pole
 
 Note:
 Astronomical Twilight at 18 degrees, needs editing in Unreal skysphere BP
 
 TODO:
 - Implement hour modifications
 -- Local to GMT
 -- Daylight savings
 - Add Timezone and daylight savings
 
 Checked OK against
 https://www.esrl.noaa.gov/gmd/grad/solcalc/azel.html
 http://www.pveducation.org/pvcdrom/suns-position-high-accuracy
 
 Useful BP
 https://docs.unrealengine.com/latest/INT/Programming/Introduction/
 
 */

UCLASS()
class BREACHSUNDIALV3_API USuncalc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
    
	
public:
    UFUNCTION(BlueprintCallable, Category="SunCalc")
    // & outputs, inputs normal
    static void calculateSunPos(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth);
    
    UFUNCTION(BlueprintCallable, Category = "SunCalc")
    static void second(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth);
    
    UFUNCTION(BlueprintPure, Category = "SunCalc")
    static void without_executor(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth);
    
    
private:
    static inline double rev( double x ) {
        /* normalize rotation, 0 - 360 */
        return x - floor(x / 360.0) * 360.0;
    }
    
    static inline double cbrt( double x ) {
        /* compute cube root */
        if ( x > 0.0 )      return exp( log(x) / 3.0 );
        else if ( x < 0.0 ) return -cbrt(-x);
        else                return 0.0;
    }
    
    static inline float calculate_julian (int y, int m, int d, int h = 0){
        return 367 * y - ( 7 * (y + (( m + 9 ) / 12))) / 4 + ( 275 * m) / 9 + d - 730530;
    }
    
    static inline double normalize_sidereal(double s){
        /* normalize sidereal time to 24 hours */
        if ( s < 0.0 )          return normalize_sidereal(s + 24);
        else if ( s > 24.0 )    return normalize_sidereal(s - 24);
        else                    return s;
    }
    
    static inline void print_this_in_hours(float t){
        /* Print decimal time to normal time format */
        /* Make this a function to return a FDateTime */
        int h, m;
        float s;
        
        h = floor(t);
        m = floor((t - h) * 60);
        s = ((t - h) * 60 - m) * 60;
        
        printf("%ih %im %fs \n",h, m, s);
        
    }
	
    static inline double time_to_decimal_hours(int h, int m, int s = 0){
        /* Returns float decimal hours from 24 hour time */
        return h + (m / 60.0) + ( s / (60.0 * 60.0));
        
    }
    
};
