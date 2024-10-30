// HistoryActivity.java
package com.example.javamore;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import androidx.appcompat.app.AppCompatActivity;
import android.preference.PreferenceManager;
import java.util.ArrayList;
import java.util.List;

public class HistoryActivity extends AppCompatActivity {

    private ListView historyListView;
    private Button clearHistoryButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_history);

        historyListView = findViewById(R.id.listView_history);
        clearHistoryButton = findViewById(R.id.button_clear_history);

        List<String> historyItems = getHistory();
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, historyItems);
        historyListView.setAdapter(adapter);

        clearHistoryButton.setOnClickListener(v -> {
            SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
            prefs.edit().remove("history").apply();

            adapter.clear();
            adapter.notifyDataSetChanged();
        });
    }
    private List<String> getHistory() {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String history = prefs.getString("history", "");

        List<String> historyList = new ArrayList<>();
        if (!history.isEmpty()) {
            String[] entries = history.split(";");
            for (String entry : entries) {
                if (!entry.isEmpty()) {
                    String[] parts = entry.split(",");
                    if (parts.length == 5) {
                        String display = "Deposit: " + parts[0] +
                                ", Interest: " + parts[1] + "%" +
                                ", Period: " + parts[2] + " yrs" +
                                "\nTotal: " + parts[3] +
                                ", Interest: " + parts[4];
                        historyList.add(display);
                    }
                }
            }
        }
        return historyList;
    }
}