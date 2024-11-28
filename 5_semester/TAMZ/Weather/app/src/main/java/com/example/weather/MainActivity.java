// MainActivity.java
package com.example.weather;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import android.view.MenuItem;

public class MainActivity extends AppCompatActivity {

    private BottomNavigationView bottomNavigationView;

    private CurrentWeatherFragment currentWeatherFragment;
    private ForecastFragment forecastFragment;
    private GraphFragment graphFragment; // New fragment

    private boolean isLandscape;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        isLandscape = getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE;

        setContentView(R.layout.activity_main);

        currentWeatherFragment = CurrentWeatherFragment.newInstance();
        forecastFragment = ForecastFragment.newInstance();
        graphFragment = GraphFragment.newInstance();

        if (isLandscape) {
            loadFragment(R.id.fragment_current_weather, currentWeatherFragment);
            loadFragment(R.id.fragment_forecast, forecastFragment);
        } else {
            loadFragment(R.id.fragment_container, currentWeatherFragment);

            bottomNavigationView = findViewById(R.id.bottom_navigation);
            bottomNavigationView.setOnNavigationItemSelectedListener(navListener);
        }
    }

    private BottomNavigationView.OnNavigationItemSelectedListener navListener =
            new BottomNavigationView.OnNavigationItemSelectedListener(){
                @Override
                public boolean onNavigationItemSelected(@NonNull MenuItem item){
                    Fragment selectedFragment = null;

                    int itemId = item.getItemId();
                    if (itemId == R.id.navigation_current_weather) {
                        selectedFragment = currentWeatherFragment;
                    } else if (itemId == R.id.navigation_forecast) {
                        selectedFragment = forecastFragment;
                    } else if (itemId == R.id.navigation_graph) {

                    }

                    return loadFragment(R.id.fragment_container, selectedFragment);
                }
            };

    private boolean loadFragment(int containerId, Fragment fragment){
        if(fragment != null){
            getSupportFragmentManager()
                    .beginTransaction()
                    .replace(containerId, fragment)
                    .commit();
            return true;
        }
        return false;
    }

    public ForecastFragment getForecastFragment(){
        return forecastFragment;
    }

    public String getCurrentCity(){
        String city = currentWeatherFragment.getCity();
        if(city == null || city.trim().isEmpty()){
            return "Ostrava";
        }
        return city;
    }
}