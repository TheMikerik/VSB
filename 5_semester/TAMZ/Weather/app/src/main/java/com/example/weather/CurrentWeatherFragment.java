package com.example.weather;

import android.content.Intent;
import android.os.Bundle;
import androidx.fragment.app.Fragment;
import androidx.appcompat.widget.Toolbar;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

public class CurrentWeatherFragment extends Fragment {

    private EditText inputCity;
    private TextView temperatureContainerText;
    private TextView descriptionContainerText;
    private ImageView iconContainerImage;
    private CurrentWeatherAPI currentWeatherAPI;
    private Button btnOk;

    private String apiKey = "0878489af83340fd9659bfa80bce5eba";

    public CurrentWeatherFragment() {
        // Required empty public constructor
    }

    public static CurrentWeatherFragment newInstance() {
        return new CurrentWeatherFragment();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState){
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_current_weather, container, false);

        inputCity = view.findViewById(R.id.input_city);
        temperatureContainerText = view.findViewById(R.id.temperature_container_text);
        descriptionContainerText = view.findViewById(R.id.description_container_text);
        iconContainerImage = view.findViewById(R.id.icon_container_image);
        btnOk = view.findViewById(R.id.btn_ok);

        // Initialize CurrentWeatherAPI
        currentWeatherAPI = new CurrentWeatherAPI(getActivity(), apiKey);

        btnOk.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                String city = inputCity.getText().toString();
                currentWeatherAPI.getWeatherData(city, temperatureContainerText, descriptionContainerText, iconContainerImage);
            }
        });

        return view;
    }

    public String getCity(){
        return inputCity.getText().toString();
    }
}