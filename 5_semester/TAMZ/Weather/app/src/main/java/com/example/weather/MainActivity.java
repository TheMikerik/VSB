package com.example.weather;

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
        setContentView(R.layout.activity_main);

        inputCity = findViewById(R.id.input_city);
        temperatureContainerText = findViewById(R.id.temperature_container_text);
        descriptionContainerText = findViewById(R.id.description_container_text);
        iconContainerImage = findViewById(R.id.icon_container_image);
        Button okButton = findViewById(R.id.btn_ok);
        Button forecastButton = findViewById(R.id.btn_forecast);

        String apiKey = "0878489af83340fd9659bfa80bce5eba";
        currentWeatherAPI = new CurrentWeatherAPI(this, apiKey);

        okButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String city = inputCity.getText().toString();
                currentWeatherAPI.getWeatherData(city, temperatureContainerText, descriptionContainerText, iconContainerImage);
            }
        });

        forecastButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String city = inputCity.getText().toString();
                Intent intent = new Intent(MainActivity.this, ForecastActivity.class);
                intent.putExtra("city", city);
                intent.putExtra("apiKey", apiKey);
                startActivity(intent);
            }
        });
    }
}