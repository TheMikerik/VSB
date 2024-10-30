// SettingsActivity.java
package com.example.javamore;

import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;
import android.widget.SeekBar;
import androidx.appcompat.app.AppCompatActivity;
import android.preference.PreferenceManager;

public class SettingsActivity extends AppCompatActivity {

    private SeekBar depositStepSeekBar, interestStepSeekBar, periodStepSeekBar;
    private Button colorPickerButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        depositStepSeekBar = findViewById(R.id.seekBar_deposit_step);
        interestStepSeekBar = findViewById(R.id.seekBar_interest_step);
        periodStepSeekBar = findViewById(R.id.seekBar_period_step);
        colorPickerButton = findViewById(R.id.button_color_picker);

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        depositStepSeekBar.setProgress(prefs.getInt("deposit_step", 1000));
        interestStepSeekBar.setProgress(prefs.getInt("interest_step", 1));
        periodStepSeekBar.setProgress(prefs.getInt("period_step", 1));

        depositStepSeekBar.setOnSeekBarChangeListener(new SimpleSeekBarChangeListener(value -> {
            prefs.edit().putInt("deposit_step", value).apply();
        }));

        interestStepSeekBar.setOnSeekBarChangeListener(new SimpleSeekBarChangeListener(value -> {
            prefs.edit().putInt("interest_step", value).apply();
        }));

        periodStepSeekBar.setOnSeekBarChangeListener(new SimpleSeekBarChangeListener(value -> {
            prefs.edit().putInt("period_step", value).apply();
        }));

        colorPickerButton.setOnClickListener(v -> {
            int currentColor = prefs.getInt("chart_color", Color.BLUE);
            int newColor;
            if (currentColor == Color.BLUE) {
                newColor = Color.RED;
            } else if (currentColor == Color.RED) {
                newColor = Color.GREEN;
            } else {
                newColor = Color.BLUE;
            }
            prefs.edit().putInt("chart_color", newColor).apply();
        });
    }

    interface OnSeekBarChangeListener {
        void onValueChanged(int value);
    }

    static class SimpleSeekBarChangeListener implements SeekBar.OnSeekBarChangeListener {
        private final OnSeekBarChangeListener listener;

        SimpleSeekBarChangeListener(OnSeekBarChangeListener listener) {
            this.listener = listener;
        }

        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            listener.onValueChanged(progress);
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {}
        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {}
    }
}