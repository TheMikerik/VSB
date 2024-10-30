// HistoryItem.java
package com.example.javamore;

public class HistoryItem {
    private int deposit;
    private int interestRate;
    private int period;
    private int totalAmount;
    private int totalInterest;

    public HistoryItem(int deposit, int interestRate, int period, int totalAmount, int totalInterest) {
        this.deposit = deposit;
        this.interestRate = interestRate;
        this.period = period;
        this.totalAmount = totalAmount;
        this.totalInterest = totalInterest;
    }

    public int getTotalInterest() {
        return totalInterest;
    }

    public void setTotalInterest(int totalInterest) {
        this.totalInterest = totalInterest;
    }

    public int getTotalAmount() {
        return totalAmount;
    }

    public void setTotalAmount(int totalAmount) {
        this.totalAmount = totalAmount;
    }

    public int getPeriod() {
        return period;
    }

    public void setPeriod(int period) {
        this.period = period;
    }

    public int getInterestRate() {
        return interestRate;
    }

    public void setInterestRate(int interestRate) {
        this.interestRate = interestRate;
    }

    public int getDeposit() {
        return deposit;
    }

    public void setDeposit(int deposit) {
        this.deposit = deposit;
    }
}