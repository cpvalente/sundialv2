// Fill out your copyright notice in the Description page of Project Settings.

#include "breachSundialv3.h"
#include "Suncalc.h"

void USuncalc::second(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth)
{}

void USuncalc::without_executor(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth){}


void USuncalc::calculateSunPos(const float latitude, const float longitude, const FDateTime date, float& altitude, float& azimuth){
    
    
    // could be implemented clever with pointers
    int year = date.GetYear();
    int month = date.GetMonth();
    int day = date.GetDay();
    
    int hour = date.GetHour();
    int min = date.GetMinute();
    
    /* Calculate Julian Day */
    float d = calculate_julian(year, month, day);     // julian days
    
    /* Calculate sun position */
    double w = rev(282.9404 + 4.70935E-5   * d);      // longitude of perihelion
    double a = 1.000000;                              // mean distance, a.u.
    double e = 0.016709 - 1.151E-9         * d;       // eccentricity
    double M = rev(356.0470 + 0.9856002585 * d);      // mean anomaly
    
    double oblecl = rev(23.4393 - 3.563E-7 * d);      // obliquity
    
    double L = rev(w + M);                            // mean longitude
    
    double E = M + RADEG * e * sind(M) * (1 + e * cosd(M)); //Eccentric anomaly
    
    /* Sun coordinates x towards perihelion */
    double x = cosd(E) - e;
    double y = sind(E) * sqrt(1 - e * e);
    
    double r = sqrt(x * x + y * y); // heliocentric distance
    double v = atan2(y, x) * RADEG; // true anomaly
    
    double lon = rev(v + w);
    
    /* Calculate rectangular coordinates */
    x = r * cosd(lon);
    y = r * sind(lon);
    double z = 0.0;
    
    double xequat = x;
    double yequat = y * cosd(oblecl) - 0.0 * sind(oblecl);
    double zequat = y * sind(oblecl) + 0.0 * cosd(oblecl);
    
    double RA = atan2d(yequat, xequat) / 15.0; // Right Ascension Degrees
    
    double Decl = asind(zequat / r);           // declination in degrees
    
    /* Time calculations */
    /* !!! Build time here !!! */

    double GMT0 = rev(L + 180.0);
    GMT0 = tohour(GMT0);
    
    double UT = time_to_decimal_hours(hour, min); // convert time to float time
    
    double sidereal = GMT0 + UT + (longitude / 15.0);
    
    float HA = sidereal - RA; // hour angle
    float HAd = fromhour(HA);
    
    /* Convert to rectangular coordinates */
    x = cosd(HAd) * cosd(Decl);
    y = sind(HAd) * cosd(Decl);
    z = sind(Decl);
    
    
    /* Rotate coordinates */
    float xhor = x * sind(latitude) - z * cosd(latitude);
    float yhor = y;
    float zhor = x * cosd(latitude) + z * sind(latitude);
    
    azimuth = atan2d( yhor, xhor) + 180;
    altitude = asind(zhor);
    
}

