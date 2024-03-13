package org.example;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class StatsWriter {
    private int die_count;
    private int coin_picked;

    public StatsWriter(int dies, int coins) {
        this.die_count = dies;
        this.coin_picked = coins;

        this.writeToFile();
    }

    public void writeToFile() {
        try {
            File file = new File("stats.txt");
            if (file.exists()) {
                file.delete();
            }
            file.createNewFile();

            try (PrintWriter writer = new PrintWriter(new FileWriter(file))) {
                writer.println("die_count=" + die_count);
                writer.println("coin_picked=" + coin_picked);
            }
            System.out.println("Output file with stats was generated");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
