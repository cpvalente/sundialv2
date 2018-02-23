#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define PI          3.14159265358979323846
#define TWO_PI      6.28318530717958647693
#define RADEG       (180.0 / PI)
#define DEGRAD      (PI / 180.0)
#define HOURAD      (15.0 * DEGRAD)
#define fromhour(x) (x * 15.0)
#define tohour(x)   (x / 15.0)
#define sind(x)     sin((x) * DEGRAD)
#define cosd(x)     cos((x) * DEGRAD)
#define tand(x)     tan((x) * DEGRAD)
#define asind(x)    (RADEG * asin(x))
#define acosd(x)    (RADEG * acos(x))
#define atand(x)    (RADEG * atan(x))
#define atan2d(y,x) (RADEG * atan2((y),(x)))

/*  
    
    SOURCES
    1. http://www.stjarnhimlen.se/comp/tutorial.html#1
 
    X axis points to the celestial equator in the south, the Y axis to the horizon in the west, and the Z axis to the north celestial pole
 
    Note:
    Astronomical Twilight at 18 degrees
    Civil Twilight at 12 degrees
 
    Source: http://jebrown.us/SolarAlmanac/
 
    
    TODO:
    - Implement hour
    - Add Timezone and daylight savings
    - Implement UI
    - Draw results
 
    Checked OK against
    https://www.esrl.noaa.gov/gmd/grad/solcalc/azel.html
    http://www.pveducation.org/pvcdrom/suns-position-high-accuracy
 
 */

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float azimuth, altitude;
    float latitude, longitude;
    int hours, min, sec, year, month, day;
    
    inline double rev( double x ) {
    /* normalize rotation in 0 - 360 range */
        return x - floor( x / 360.0) * 360.0;
    }
    
    inline double cbrt( double x ) {
    /* compute cube root */
        if ( x > 0.0 )
            return exp( log(x) / 3.0 );
        
        else if ( x < 0.0 )
            return -cbrt(-x);
        
        else // x == 0.0
            return 0.0;
    }
    
    inline float calculate_julian (int y, int m, int d, int h = 0){
        return 367 * y - ( 7 * (y + (( m + 9 ) / 12))) / 4 + ( 275 * m) / 9 + d - 730530;
    }
    
    inline double normalize_sidereal(double s){
        /* compute cube root */
        if ( s < 0.0 )
            return normalize_sidereal(s + 24);
        
        else if ( s > 24.0 )
            return normalize_sidereal(s - 24);
        
        else
            return s;
    }
    
    inline void print_this_in_hours(float t){
        /* Make date time thing to return this? */
        int h, m;
        float s;
        
        h = floor(t);
        m = floor((t - h) * 60);
        s = ((t - h) * 60 - m) * 60;
        
        printf("%ih %im %fs \n",h, m, s);
        
    }
    
    static inline float time_to_decimal_hours(int h, int m, int s = 0){
        /* Returns float decimal hours from 24 hour time */
        
        float t;
        t = h;
        
        t += m / 60.0;
        t += s / 60.0 / 60.0;
        return t;
   
    }
	
};
