package com.example.weather;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.widget.ImageView;
import android.widget.TextView;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.json.JSONObject;

public class CurrentWeatherAPI {

    private Context context;
    private String apiKey;

    public CurrentWeatherAPI(Context context, String apiKey) {
        this.context = context;
        this.apiKey = apiKey;
    }

    public void getWeatherData(final String city, final TextView temperatureText, final TextView descriptionText, final ImageView iconImage) {
        new Thread() {
            public void run() {
                try {
                    URL url = new URL("https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");

                    BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                    StringBuilder response = new StringBuilder();
                    String line;
                    while ((line = br.readLine()) != null) {
                        response.append(line);
                    }
                    br.close();

                    JSONObject jsonObject = new JSONObject(response.toString());
                    final String temperature = jsonObject.getJSONObject("main").getString("temp");
                    final String description = jsonObject.getJSONArray("weather").getJSONObject(0).getString("description");
                    final String icon = jsonObject.getJSONArray("weather").getJSONObject(0).getString("icon");

                    new Handler(Looper.getMainLooper()).post(new Runnable() {
                        @Override
                        public void run() {
                            temperatureText.setText(temperature);
                            descriptionText.setText(description);
                            int resourceId = context.getResources().getIdentifier("icon_" + icon, "drawable", context.getPackageName());
                            iconImage.setImageResource(resourceId);
                        }
                    });

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }
}