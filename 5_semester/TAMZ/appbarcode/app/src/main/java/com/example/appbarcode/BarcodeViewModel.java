package com.example.appbarcode;

import androidx.lifecycle.ViewModel;

public class BarcodeViewModel extends ViewModel {
    private int[] barcodeCode;

    public int[] getBarcodeCode() {
        return barcodeCode;
    }

    public void setBarcodeCode(int[] barcodeCode) {
        this.barcodeCode = barcodeCode;
    }
}
