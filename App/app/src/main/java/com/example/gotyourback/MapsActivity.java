package com.example.gotyourback;

import android.os.Bundle;
import android.os.StrictMode;
import android.support.v4.app.FragmentActivity;
import android.util.Log;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.UiSettings;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;
import com.google.maps.android.PolyUtil;
import com.google.maps.DirectionsApi;
import com.google.maps.GeoApiContext;
import com.google.maps.errors.ApiException;
import com.google.maps.model.DirectionsResult;
import com.google.maps.model.DirectionsRoute;
import com.google.maps.model.TravelMode;

import org.joda.time.DateTime;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private static final int overview = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }

    private DirectionsResult getDirectionsDetails(String origin,String destination,TravelMode mode) {
        DateTime now = new DateTime();
        try {
            // Bypass the liver.
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder()
                    .permitAll().build();
            StrictMode.setThreadPolicy(policy);
            return DirectionsApi.newRequest(getGeoContext())
                    .mode(mode)
                    .origin(origin)
                    .destination(destination)
                    .departureTime(now)
                    .await();
        } catch (ApiException e) {
            e.printStackTrace();
            return null;
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {

        setupGoogleMapScreenSettings(googleMap);
        // Hardcode in the places to go.
        DirectionsResult results = getDirectionsDetails("52 Oxford St, Cambridge, MA 02138","1000 Olin Way Needham, MA 02492",TravelMode.WALKING);
        if (results != null) {
            addPolyline(results, googleMap);
            List<LatLng> path = getDecodedPath(results, googleMap);
            positionCamera(results.routes[overview], googleMap);
            addMarkersToMap(results, googleMap);
            Log.i("Directions Results.", results.routes[0].legs[0].duration.humanReadable);
            startTravel(path);
        }
    }

    private void setupGoogleMapScreenSettings(GoogleMap mMap) {
        mMap.setBuildingsEnabled(true);
        mMap.setIndoorEnabled(true);
        mMap.setTrafficEnabled(true);
        UiSettings mUiSettings = mMap.getUiSettings();
        mUiSettings.setZoomControlsEnabled(true);
        mUiSettings.setCompassEnabled(true);
        mUiSettings.setMyLocationButtonEnabled(true);
        mUiSettings.setScrollGesturesEnabled(true);
        mUiSettings.setZoomGesturesEnabled(true);
        mUiSettings.setTiltGesturesEnabled(true);
        mUiSettings.setRotateGesturesEnabled(true);
    }

    private void addMarkersToMap(DirectionsResult results, GoogleMap mMap) {
        mMap.addMarker(new MarkerOptions().position(new LatLng(results.routes[overview].legs[overview].startLocation.lat,results.routes[overview].legs[overview].startLocation.lng)).title(results.routes[overview].legs[overview].startAddress));
        mMap.addMarker(new MarkerOptions().position(new LatLng(results.routes[overview].legs[overview].endLocation.lat,results.routes[overview].legs[overview].endLocation.lng)).title(results.routes[overview].legs[overview].startAddress).snippet(getEndLocationTitle(results)));
    }

    private void positionCamera(DirectionsRoute route, GoogleMap mMap) {
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(route.legs[overview].startLocation.lat, route.legs[overview].startLocation.lng), 12));
    }

    private void addPolyline(DirectionsResult results, GoogleMap mMap) {
        List<LatLng> decodedPath = PolyUtil.decode(results.routes[overview].overviewPolyline.getEncodedPath());
        mMap.addPolyline(new PolylineOptions().addAll(decodedPath));

    }
    private List<LatLng> getDecodedPath(DirectionsResult results, GoogleMap mMap) {
        List<LatLng> decodedPath = PolyUtil.decode(results.routes[overview].overviewPolyline.getEncodedPath());
        return decodedPath;
    }

    private String getEndLocationTitle(DirectionsResult results){
        return  "Time :"+ results.routes[overview].legs[overview].duration.humanReadable + " Distance :" + results.routes[overview].legs[overview].distance.humanReadable;
    }

    private void startTravel(List<LatLng> decodedPath) {
        // Generate a list of directions.
        double[][] directions = new double[decodedPath.size()][2];
        // This measurement is in miles.
        int earth_radius = 3959;
        for (int i=5; i < decodedPath.size()/5; i++) {
            // Use the Haversine formula to get distances.
            i *= 5;
            double longitude_difference = Math.toRadians(decodedPath.get(i).latitude - decodedPath.get(i-5).latitude);
            double latitude_difference = Math.toRadians(decodedPath.get(i).longitude - decodedPath.get(i-5).longitude);
  //          double distance_total = Math.sqrt(Math.pow(latitude_difference, 2.0) + Math.pow(longitude_difference, 2.0));
            double imm = Math.pow((Math.sin(latitude_difference/2)), 2) + Math.cos(Math.toRadians(decodedPath.get(i).latitude)) * Math.cos(Math.toRadians(decodedPath.get(i-5).latitude)) * Math.pow(Math.sin(longitude_difference/2),2);
            double scaled_imm = 2 * Math.atan2( Math.sqrt(imm), Math.sqrt(1-imm));
            double distance = earth_radius * scaled_imm;
            double theta = Math.toDegrees(Math.atan2(Math.sin(longitude_difference) * Math.cos(Math.toRadians(decodedPath.get(i).latitude)), Math.cos(Math.toRadians(decodedPath.get(i-5).latitude)) * Math.sin(Math.toRadians(decodedPath.get(i).latitude)) - Math.sin(Math.toRadians(decodedPath.get(i-5).latitude)) * Math.cos(Math.toRadians(decodedPath.get(i).latitude)) * Math.cos(longitude_difference)));
            directions[i][0] = distance;
            directions[i][1] = theta;
            Log.i("distance", Double.toString(distance));

            Log.i("angle", Double.toString(theta));
        }
        Log.i("directions array", Double.toString(directions.length));
    }

    private GeoApiContext getGeoContext() {
        GeoApiContext geoApiContext = new GeoApiContext();
        return geoApiContext
                .setQueryRateLimit(3)
                .setApiKey("API_KEY_HERE")
                .setConnectTimeout(1, TimeUnit.SECONDS)
                .setReadTimeout(1, TimeUnit.SECONDS)
                .setWriteTimeout(1, TimeUnit.SECONDS);
    }

}
