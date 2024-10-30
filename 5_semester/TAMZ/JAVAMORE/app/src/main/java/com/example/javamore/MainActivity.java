// MainActivity.java
package com.example.javamore;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Menu;
import android.view.MenuItem;
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
    private TextView regularDepositLabel;
    private TextView periodLabel;
    private SeekBar depositSeekBar;
    private SeekBar interestSeekBar;
    private SeekBar regularDepositSeekBar;
    private SeekBar periodSeekBar;
    private BarChart barChart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        totalAmountTextView = findViewById(R.id.total_amount);
        interestAmountTextView = findViewById(R.id.interest_amount);
        depositLabel = findViewById(R.id.deposit_label);
        interestLabel = findViewById(R.id.interest_label);
        periodLabel = findViewById(R.id.period_label);
        depositSeekBar = findViewById(R.id.deposit_slider);
        interestSeekBar = findViewById(R.id.interest_slider);
        periodSeekBar = findViewById(R.id.period_slider);
        barChart = findViewById(R.id.barChart);
        regularDepositLabel = findViewById(R.id.regular_deposit_label);
        regularDepositSeekBar = findViewById(R.id.regular_deposit_slider);

        depositSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);
        interestSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);
        periodSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);
        regularDepositSeekBar.setOnSeekBarChangeListener(seekBarChangeListener);

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        int lastDeposit = prefs.getInt("last_deposit", 50000);
        int lastInterest = prefs.getInt("last_interest", 5);
        int lastPeriod = prefs.getInt("last_period", 5);
        int regularDeposit = prefs.getInt("regular_deposit", 0);

        depositSeekBar.setProgress(lastDeposit);
        interestSeekBar.setProgress(lastInterest);
        periodSeekBar.setProgress(lastPeriod);
        regularDepositSeekBar.setProgress(regularDeposit);

        depositLabel.setText("Deposit: " + lastDeposit);
        interestLabel.setText("Interest: " + lastInterest + "%");
        periodLabel.setText("Period: " + lastPeriod + " yrs");
        regularDepositLabel.setText("Regular Deposit: " + regularDeposit);

        updateValues();
        setupBarChart();
        updateChartData();
    }

    private final SeekBar.OnSeekBarChangeListener seekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            updateValues();
            updateChartData();
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) { }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) { }
    };

    private void updateValues() {
        int deposit = depositSeekBar.getProgress();
        int interestRate = interestSeekBar.getProgress();
        int period = periodSeekBar.getProgress();
        int regularDeposit = regularDepositSeekBar.getProgress();

        deposit = Math.max(deposit, 1000);
        interestRate = Math.max(interestRate, 1);
        period = Math.max(period, 1);

        depositLabel.setText("Deposit: " + deposit);
        interestLabel.setText("Interest: " + interestRate + "%");
        periodLabel.setText("Period: " + period + " yrs");
        regularDepositLabel.setText("Regular Deposit: " + regularDeposit);

        int totalInvested = deposit + (regularDeposit * period);
        double totalInterest = calculateCompoundInterestWithRegularDeposit(deposit, interestRate, period, regularDeposit);
        double totalAmount = totalInvested + totalInterest;

        totalAmountTextView.setText("Total Amount: " + (int) totalAmount);
        interestAmountTextView.setText("Total Interest: " + (int) totalInterest);

        saveToHistory(deposit, interestRate, period, (int) totalAmount, (int) totalInterest);
        saveCurrentSettings(deposit, interestRate, period);
        saveRegularDeposit(regularDeposit);
    }

    private void saveRegularDeposit(int regularDeposit) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        prefs.edit()
                .putInt("regular_deposit", regularDeposit)
                .apply();
    }

    private void saveCurrentSettings(int deposit, int interestRate, int period) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        prefs.edit()
                .putInt("last_deposit", deposit)
                .putInt("last_interest", interestRate)
                .putInt("last_period", period)
                .apply();
    }

    private void saveToHistory(int deposit, int interestRate, int period, int totalAmount, int totalInterest) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String history = prefs.getString("history", "");

        String newEntry = deposit + "," + interestRate + "," + period + "," + totalAmount + "," + totalInterest + ";";
        history += newEntry;

        prefs.edit().putString("history", history).apply();
    }

    private void setupBarChart() {
        barChart.setDrawBarShadow(false);
        barChart.setDrawValueAboveBar(true);
        barChart.setMaxVisibleValueCount(50);
        barChart.setPinchZoom(false);
        barChart.setDrawGridBackground(false);

        Description description = new Description();
        description.setText("");
        description.setTextSize(14f);
        barChart.setDescription(description);

        Legend legend = barChart.getLegend();
        legend.setVerticalAlignment(Legend.LegendVerticalAlignment.TOP);
        legend.setHorizontalAlignment(Legend.LegendHorizontalAlignment.RIGHT);
        legend.setOrientation(Legend.LegendOrientation.HORIZONTAL);
        legend.setDrawInside(false);
        legend.setFormSize(10f);
        legend.setTextSize(12f);
        legend.setForm(Legend.LegendForm.CIRCLE);
    }

    private void updateChartData() {
        int deposit = depositSeekBar.getProgress();
        int interestRate = interestSeekBar.getProgress();
        int period = periodSeekBar.getProgress();
        int regularDeposit = regularDepositSeekBar.getProgress();

        deposit = Math.max(deposit, 1000);
        interestRate = Math.max(interestRate, 1);
        period = Math.max(period, 1);

        int totalInvested = deposit + (regularDeposit * period);

        double totalInterestDouble = calculateCompoundInterestWithRegularDeposit(deposit, interestRate, period, regularDeposit);
        int totalInterest = (int) totalInterestDouble;

        List<BarEntry> investedEntries = new ArrayList<>();
        List<BarEntry> interestEntries = new ArrayList<>();

        investedEntries.add(new BarEntry(1f, totalInvested));
        interestEntries.add(new BarEntry(2f, totalInterest));

        BarDataSet investedDataSet = new BarDataSet(investedEntries, "Invested Amount");
        investedDataSet.setColor(android.graphics.Color.argb(255, 172, 157, 209));
        investedDataSet.setValueTextColor(android.graphics.Color.BLACK);
        investedDataSet.setValueTextSize(16f);

        BarDataSet interestDataSet = new BarDataSet(interestEntries, "Interest");
        interestDataSet.setColor(android.graphics.Color.argb(255, 107, 79, 169));
        interestDataSet.setValueTextColor(android.graphics.Color.BLACK);
        interestDataSet.setValueTextSize(16f);

        BarData barData = new BarData(investedDataSet, interestDataSet);
        barData.setBarWidth(0.3f);

        barChart.setData(barData);

        List<String> labels = new ArrayList<>();
        labels.add("");
        labels.add("Invested");
        labels.add("Interest");
        labels.add("");

        barChart.getXAxis().setGranularity(1f);
        barChart.getXAxis().setCenterAxisLabels(true);
        barChart.getXAxis().setDrawGridLines(false);
        barChart.getXAxis().setLabelCount(labels.size());
        barChart.getXAxis().setPosition(com.github.mikephil.charting.components.XAxis.XAxisPosition.BOTTOM);
        barChart.getXAxis().setAxisMinimum(0f);
        barChart.getXAxis().setAxisMaximum(3f);
        barChart.getXAxis().setValueFormatter(new IndexAxisValueFormatter(labels));

        barChart.getAxisRight().setEnabled(false);

        barChart.animateY(1000);
        barChart.invalidate();
    }

    private int calculateCompoundInterest(int principal, double rate, int time) {
        double compoundInterest = principal * Math.pow((1 + rate / 100), time) - principal;
        return (int) compoundInterest;
    }

    private double calculateCompoundInterestWithRegularDeposit(int principal, double rate, int time, int regularDeposit) {
        double amount = principal;
        for (int i = 0; i < time; i++) {
            amount = amount * (1 + rate / 100) + regularDeposit * (1 + rate / 100);
        }
        return amount - principal - (regularDeposit * time);
    }

    private void openChartTypeSelector() {
        Intent intent = new Intent(this, ChartTypeActivity.class);
        startActivity(intent); // Or use ActivityResultLauncher if needed
    }

    private void openSettings() {
        Intent intent = new Intent(this, SettingsActivity.class);
        startActivity(intent);
    }

    private void openHistory() {
        Intent intent = new Intent(this, HistoryActivity.class);
        startActivity(intent);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()) {
            // Uncomment and implement menu actions as needed
            // case R.id.menu_chart_type:
            //     openChartTypeSelector();
            //     return true;
            // case R.id.menu_settings:
            //     openSettings();
            //     return true;
            // case R.id.menu_history:
            //     openHistory();
            //     return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}