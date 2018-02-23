#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    latitude = 69.0;
    longitude = 15.0;
    
    hours = 12;
    min = sec = 0;
    
    year = 2018;
    month = 1;
    day = 1;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    /* Calculate Julian Day */
    float d = calculate_julian(year, month, day);
    
    /* Calculate sun position */
    double w = rev(282.9404 + 4.70935E-5   * d);    // Longitude of perihelion
    double a = 1.000000;                            // Mean distance, a.u.
    double e = 0.016709 - 1.151E-9         * d;     // Eccentricity
    double M = rev(356.0470 + 0.9856002585 * d);    // Mean anomaly
    
    double oblecl = rev(23.4393 - 3.563E-7 * d);    // obliquity
    
    double L = rev(w + M);
    
    double E = M + RADEG * e * sind(M) * (1 + e * cosd(M)); //Eccentric anomaly
    
    /* Sun coordinates x towards perihelion */
    double x = cosd(E) - e;
    double y = sind(E) * sqrt(1 - e * e);
    
    double r = sqrt(x * x + y * y); // Heliocentric distance
    double v = atan2(y, x) * RADEG; // True anomaly
    
    double lon = rev(v + w);
    
    /* Calculate rectangular coordinates */
    x = r * cosd(lon);
    y = r * sind(lon);
    double z = 0.0;
    
    double xequat = x;
    double yequat = y * cosd(oblecl) - 0.0 * sind(oblecl);
    double zequat = y * sind(oblecl) + 0.0 * cosd(oblecl);
    
    double RA = atan2d(yequat, xequat) / 15.0; // Right Ascension Degrees
    
    double Decl = asind(zequat / r);           // Declination in degrees
    
    double GMT0 = rev(L + 180.0);
    GMT0 = tohour(GMT0);
    
    double UT = 12; // convert time to float time
    
    double sidereal = GMT0 + UT + longitude / 15.0;
    
    float HA = sidereal - RA;   // hour angle
    float HAd = fromhour(HA);   // hour angle degrees
    
    /* Convert to rectangular coordinates */
    x = cosd(HAd) * cosd(Decl);
    y = sind(HAd) * cosd(Decl);
    z = sind(Decl);
    
    
    /* Rotate coordinates */
    float xhor = x * sind(latitude) - z * cosd(latitude);
    float yhor = y;
    float zhor = x * cosd(latitude) + z * sind(latitude);
    
    azimuth = atan2d(yhor, xhor) + 180;
    altitude = asind(zhor);
    
    
    printf("Calculated azimuth: %f and altitude %f \n", azimuth, altitude);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofExit();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
