// ChartTypeActivity.java
package com.example.javamore;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import androidx.appcompat.app.AppCompatActivity;

public class ChartTypeActivity extends AppCompatActivity {

    public static final String EXTRA_CHART_TYPE = "extra_chart_type";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chart_type);

        Button barChartButton = findViewById(R.id.button_bar_chart);
        Button lineChartButton = findViewById(R.id.button_line_chart);

        barChartButton.setOnClickListener(v -> {
            Intent result = new Intent();
            result.putExtra(EXTRA_CHART_TYPE, "Bar");
            setResult(RESULT_OK, result);
            finish();
        });

        lineChartButton.setOnClickListener(v -> {
            Intent result = new Intent();
            result.putExtra(EXTRA_CHART_TYPE, "Line");
            setResult(RESULT_OK, result);
            finish();
        });
    }
}