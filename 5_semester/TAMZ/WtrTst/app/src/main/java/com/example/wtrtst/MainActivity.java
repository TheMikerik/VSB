package com.example.wtrtst; // Ensure this matches your project's package name

import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private EditText inputCity;
    private TextView temperatureContainerText;
    private TextView descriptionContainerText;
    private ImageView iconContainerImage;
    private CurrentWeatherAPI currentWeatherAPI;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // Ensure this layout exists

        inputCity = findViewById(R.id.input_city);
        temperatureContainerText = findViewById(R.id.temperature_container_text);
        descriptionContainerText = findViewById(R.id.description_container_text);
        iconContainerImage = findViewById(R.id.icon_container_image);

        Button okButton = findViewById(R.id.btn_ok);
        Button forecastButton = findViewById(R.id.btn_forecast);

        String apiKey = "0878489af83340fd9659bfa80bce5eba"; // Consider securing your API key
        currentWeatherAPI = new CurrentWeatherAPI(this, apiKey);

        okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String city = inputCity.getText().toString().trim();
                if(!city.isEmpty()) {
                    currentWeatherAPI.getWeatherData(city, temperatureContainerText, descriptionContainerText, iconContainerImage);
                } else {
                    inputCity.setError("Please enter a city name");
                }
            }
        });

        forecastButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String city = inputCity.getText().toString().trim();
                if(!city.isEmpty()) {
                    Intent intent = new Intent(MainActivity.this, ForecastActivity.class);
                    intent.putExtra("city", city);
                    intent.putExtra("apiKey", apiKey);
                    startActivity(intent);
                } else {
                    inputCity.setError("Please enter a city name");
                }
            }
        });
    }
}