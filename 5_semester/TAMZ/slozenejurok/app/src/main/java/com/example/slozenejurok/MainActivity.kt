package com.example.slozenejurok

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.SeekBar
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    private lateinit var totalAmountTextView: TextView
    private lateinit var interestAmountTextView: TextView

    private lateinit var depositLabel: TextView
    private lateinit var interestLabel: TextView
    private lateinit var periodLabel: TextView

    private lateinit var depositSeekBar: SeekBar
    private lateinit var interestSeekBar: SeekBar
    private lateinit var periodSeekBar: SeekBar

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        totalAmountTextView = findViewById(R.id.total_amount)
        interestAmountTextView = findViewById(R.id.interest_amount)
        depositLabel = findViewById(R.id.deposit_label)
        interestLabel = findViewById(R.id.interest_label)
        periodLabel = findViewById(R.id.period_label)
        depositSeekBar = findViewById(R.id.deposit_slider)
        interestSeekBar = findViewById(R.id.interest_slider)
        periodSeekBar = findViewById(R.id.period_slider)

        depositSeekBar.setOnSeekBarChangeListener(seekBarChangeListener)
        interestSeekBar.setOnSeekBarChangeListener(seekBarChangeListener)
        periodSeekBar.setOnSeekBarChangeListener(seekBarChangeListener)

        updateValues()
    }

    LineChart myChart = findViewById(R.id.lineChart);
    myChart.setBackgroundColor(Color.LTGRAY);
    zkurvenapyco
    List<Entry> entries = new ArrayList<>();
    entries.add(new Entry(0, 0));
    entries.add(new Entry(5, 5));
    LineDataSet dataSet = new LineDataSet(entries, "Label");
    dataSet.setLineWidth(20);

    LineData lineData = new LineData(dataSet);
    myChart.setData(lineData);
    myChart.invalidate();

    private val seekBarChangeListener = object : SeekBar.OnSeekBarChangeListener {
        override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
            updateValues()
        }

        override fun onStartTrackingTouch(seekBar: SeekBar?) {
        }

        override fun onStopTrackingTouch(seekBar: SeekBar?) {
        }
    }

    private fun updateValues() {
        val deposit = depositSeekBar.progress
        val interestRate = interestSeekBar.progress
        val period = periodSeekBar.progress

        depositLabel.text = "Vklad: $deposit"
        interestLabel.text = "Úrok: $interestRate"
        periodLabel.text = "Období: $period"

        val totalInterest = calculateCompoundInterest(deposit, interestRate.toDouble(), period)
        val totalAmount = deposit + totalInterest

        totalAmountTextView.text = "Napořená suma: $totalAmount"
        interestAmountTextView.text = "Z toho úroky: $totalInterest"
    }

    // Compound interest formula calculation
    private fun calculateCompoundInterest(principal: Int, rate: Double, time: Int): Int {
        val compoundInterest = principal * Math.pow((1 + rate / 100), time.toDouble()) - principal
        return compoundInterest.toInt()
    }
}
