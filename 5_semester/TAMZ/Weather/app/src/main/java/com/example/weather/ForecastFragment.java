package com.example.weather;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import androidx.fragment.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

public class ForecastFragment extends Fragment {

    private ArrayList<ForecastItem> forecastList = new ArrayList<>();
    private ForecastAdapter adapter;
    private ListView listView;

    private String apiKey = "0878489af83340fd9659bfa80bce5eba";
    private String city = "London"; // Default city or you can make it dynamic

    public ForecastFragment() {
        // Required empty public constructor
    }

    public static ForecastFragment newInstance() {
        return new ForecastFragment();
    }

    // ForecastFragment.java
    @Override
    public void onResume(){
        super.onResume();
        // Fetch the current city whenever the fragment resumes
        MainActivity mainActivity = (MainActivity) getActivity();
        if(mainActivity != null){
            String currentCity = mainActivity.getCurrentCity();
            if(!currentCity.isEmpty()){
                getForecastData(getActivity(), currentCity, apiKey);
            }
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState){
        View view = inflater.inflate(R.layout.fragment_forecast, container, false);

        listView = view.findViewById(R.id.list_view);
        adapter = new ForecastAdapter(getActivity(), forecastList);
        listView.setAdapter(adapter);

        // Fetch city from MainActivity
        MainActivity mainActivity = (MainActivity) getActivity();
        if(mainActivity != null){
            city = mainActivity.getCurrentCity();
        }

        getForecastData(getActivity(), city, apiKey);

        return view;
    }

    private void getForecastData(final Context context, final String city, final String apiKey) {
        new Thread() {
            public void run() {
                try {
                    URL url = new URL("https://api.openweathermap.org/data/2.5/forecast?q=" + city + "&appid=" + apiKey + "&units=metric");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");

                    BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                    StringBuilder response = new StringBuilder();
                    String line;
                    while ((line = br.readLine()) != null){
                        response.append(line);
                    }
                    br.close();

                    JSONObject jsonObject = new JSONObject(response.toString());
                    JSONArray list = jsonObject.getJSONArray("list");

                    for (int i = 0; i < list.length(); i++){
                        JSONObject item = list.getJSONObject(i);
                        String temp = item.getJSONObject("main").getString("temp");
                        String date = item.getString("dt_txt");
                        String description = item.getJSONArray("weather").getJSONObject(0).getString("description");
                        String icon = item.getJSONArray("weather").getJSONObject(0).getString("icon");

                        ForecastItem forecastItem = new ForecastItem(date, temp, description, icon);
                        forecastList.add(forecastItem);
                    }

                    new Handler(Looper.getMainLooper()).post(new Runnable(){
                        @Override
                        public void run(){
                            adapter.notifyDataSetChanged();
                        }
                    });

                } catch (Exception e){
                    e.printStackTrace();
                }
            }
        }.start();
    }

    private class ForecastItem {
        String date;
        String temp;
        String description;
        String icon;

        ForecastItem(String date, String temp, String description, String icon){
            this.date = date;
            this.temp = temp;
            this.description = description;
            this.icon = icon;
        }
    }

    private class ForecastAdapter extends ArrayAdapter<ForecastItem> {

        public ForecastAdapter(Context context, ArrayList<ForecastItem> forecastItems){
            super(context, 0, forecastItems);
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent){
            if(convertView == null){
                convertView = LayoutInflater.from(getContext()).inflate(R.layout.list_item_forecast, parent, false);
            }

            ForecastItem forecastItem = getItem(position);

            TextView forecastText = convertView.findViewById(R.id.forecast_text);
            ImageView iconImage = convertView.findViewById(R.id.icon_image);

            forecastText.setText("Date: " + forecastItem.date + "\nTemp: " + forecastItem.temp + "°C, " + forecastItem.description);

            int resourceId = getContext().getResources().getIdentifier("icon_" + forecastItem.icon, "drawable", getContext().getPackageName());
            iconImage.setImageResource(resourceId);

            return convertView;
        }
    }
}