package com.example.javamore;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.TextView;

import com.github.mikephil.charting.charts.BarChart;
import com.github.mikephil.charting.components.Description;
import com.github.mikephil.charting.components.Legend;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private TextView totalAmountTextView;
    private TextView interestAmountTextView;
    private TextView depositLabel;
    private TextView interestLabel;
    private TextView periodLabel;
    private SeekBar depositSeekBar;
    private SeekBar interestSeekBar;
    private SeekBar periodSeekBar;
    private BarChart barChart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize Views
        totalAmountTextView = findViewById(R.id.total_amount);
        interestAmountTextView = findViewById(R.id.interest_amount);
        depositLabel = findViewById(R.id.deposit_label);
        interestLabel = findViewById(R.id.interest_label);
        periodLabel = findViewById(R.id.period_label);
        depositSeekBar = findViewById(R.id.deposit_slider);
        interestSeekBar = findViewById(R.id.interest_slider);
        periodSeekBar = findViewById(R.id.period_slider);
        barChart = findViewById(R.id.barChart);

        // Set SeekBar Change Listeners
        depositSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);
        interestSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);
        periodSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);

        // Initial Values and Chart Setup
        updateValues();
        setupBarChart();
        updateChartData();
    }

    // SeekBar change listener
    private final SeekBar.OnSeekBarChangeListener seekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            updateValues();
            updateChartData();
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
            // No action needed
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
            // No action needed
        }
    };

    // Method to update values on the screen
    private void updateValues() {
        int deposit = depositSeekBar.getProgress();
        int interestRate = interestSeekBar.getProgress();
        int period = periodSeekBar.getProgress();

        // Ensure minimum values
        deposit = Math.max(deposit, 1000);
        interestRate = Math.max(interestRate, 1);
        period = Math.max(period, 1);

        depositLabel.setText("Vklad: " + deposit);
        interestLabel.setText("Úrok: " + interestRate + "%");
        periodLabel.setText("Období: " + period + " let");

        int totalInterest = calculateCompoundInterest(deposit, (double) interestRate, period);
        int totalAmount = deposit + totalInterest;

        totalAmountTextView.setText("Napořená suma: " + totalAmount);
        interestAmountTextView.setText("Z toho úroky: " + totalInterest);
    }

    // Setting up the BarChart
    private void setupBarChart() {
        barChart.setDrawBarShadow(false);
        barChart.setDrawValueAboveBar(true);
        barChart.setMaxVisibleValueCount(50);
        barChart.setPinchZoom(false);
        barChart.setDrawGridBackground(false);

        // Description
        Description description = new Description();
        description.setText("Invested vs. Interest");
        description.setTextSize(14f);
        barChart.setDescription(description);

        // Legend
        Legend legend = barChart.getLegend();
        legend.setVerticalAlignment(Legend.LegendVerticalAlignment.TOP);
        legend.setHorizontalAlignment(Legend.LegendHorizontalAlignment.RIGHT);
        legend.setOrientation(Legend.LegendOrientation.HORIZONTAL);
        legend.setDrawInside(false);
        legend.setFormSize(10f);
        legend.setTextSize(12f);
        legend.setForm(Legend.LegendForm.CIRCLE);
    }

    // Method to update chart data
    private void updateChartData() {
        int deposit = depositSeekBar.getProgress();
        int interestRate = interestSeekBar.getProgress();
        int period = periodSeekBar.getProgress();

        // Ensure minimum values
        deposit = Math.max(deposit, 1000);
        interestRate = Math.max(interestRate, 1);
        period = Math.max(period, 1);

        // Calculate total interest
        int totalInterest = calculateCompoundInterest(deposit, (double) interestRate, period);

        // Prepare Bar Entries
        List<BarEntry> investedEntries = new ArrayList<>();
        List<BarEntry> interestEntries = new ArrayList<>();

        // Assign positions on X-axis
        investedEntries.add(new BarEntry(1f, deposit));
        interestEntries.add(new BarEntry(2f, totalInterest));

        // Create BarDataSet
        BarDataSet investedDataSet = new BarDataSet(investedEntries, "Invested Amount");
        investedDataSet.setColor(Color.BLUE);
        investedDataSet.setValueTextColor(Color.BLACK);
        investedDataSet.setValueTextSize(16f);

        BarDataSet interestDataSet = new BarDataSet(interestEntries, "Interest");
        interestDataSet.setColor(Color.GREEN);
        interestDataSet.setValueTextColor(Color.BLACK);
        interestDataSet.setValueTextSize(16f);

        // Add both datasets to BarData
        BarData barData = new BarData(investedDataSet, interestDataSet);
        barData.setBarWidth(0.3f); // set custom bar width

        barChart.setData(barData);

        // Configure XAxis
        List<String> labels = new ArrayList<>();
        labels.add(""); // Placeholder for index 0
        labels.add("Invested");
        labels.add("Interest");
        labels.add(""); // Placeholder for index 3

        barChart.getXAxis().setGranularity(1f);
        barChart.getXAxis().setCenterAxisLabels(true);
        barChart.getXAxis().setDrawGridLines(false);
        barChart.getXAxis().setLabelCount(labels.size());
        barChart.getXAxis().setPosition(com.github.mikephil.charting.components.XAxis.XAxisPosition.BOTTOM);
        barChart.getXAxis().setAxisMinimum(0f);
        barChart.getXAxis().setAxisMaximum(3f);
        barChart.getXAxis().setValueFormatter(new IndexAxisValueFormatter(labels));

        // Remove right YAxis
        barChart.getAxisRight().setEnabled(false);

        // Animate the chart
        barChart.animateY(1000);

        // Refresh the chart
        barChart.invalidate();
    }

    // Compound interest formula calculation
    private int calculateCompoundInterest(int principal, double rate, int time) {
        double compoundInterest = principal * Math.pow((1 + rate / 100), time) - principal;
        return (int) compoundInterest;
    }
}