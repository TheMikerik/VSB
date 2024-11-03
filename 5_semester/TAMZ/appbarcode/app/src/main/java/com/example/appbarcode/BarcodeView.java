package com.example.appbarcode;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Configuration;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;

public class BarcodeView extends View {

    static final int[] L = {0x0D, 0x19, 0x13, 0x3D, 0x23, 0x31, 0x2F, 0x3B, 0x37, 0x0B};
    static final int[] R = {0x72, 0x66, 0x6C, 0x42, 0x5C, 0x5E, 0x50, 0x44, 0x48, 0x74};

    static int BARCODE_WIDTH = 600;
    static int BARCODE_HEIGHT = 200;
    static int BARCODE_LINE_WIDTH = 5;
    private boolean showValidationMessage = false;

    int code[] = new int[12];

    public int[] getCode() {
        return code;
    }

    public BarcodeView(Context context) {
        super(context);
        setDefaults();
        updateBarcodeSize();
    }

    public BarcodeView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        setDefaults();
        updateBarcodeSize();
    }

    void setDefaults() {
        int copyFrom[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2};
        System.arraycopy(copyFrom, 0, code, 0, copyFrom.length);
    }

    public void enableValidationMessage(boolean enable) {
        showValidationMessage = enable;
    }

    public String validateUPC(int[] code) {
        int sum = 0;
        for (int i = 0; i < code.length - 1; i++) {
            sum += (i % 2 == 0) ? code[i] * 3 : code[i];
        }
        int checkDigit = (10 - (sum % 10)) % 10;

        if (checkDigit == code[11]) {
            return "Validní kontrolní číslo.";
        } else {
            return "Neplatné kontrolní číslo. Doporučené kontrolní číslo je: " + checkDigit;
        }
    }

    public void setCode(int[] newCode) {
        if (newCode.length == 12) {
            String validationMessage = validateUPC(newCode);

            if (validationMessage.equals("Validní kontrolní číslo.")) {
                System.arraycopy(newCode, 0, code, 0, newCode.length);
                invalidate();
            }

            if (showValidationMessage) {
                Toast.makeText(getContext(), validationMessage, Toast.LENGTH_SHORT).show();
            }
        }
    }

    public void updateBarcodeSize() {
        if (getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
            BARCODE_WIDTH = 1500;
            BARCODE_HEIGHT = 500;
        } else {
            BARCODE_WIDTH = 600;
            BARCODE_HEIGHT = 200;
        }
        BARCODE_LINE_WIDTH = Math.max(1, BARCODE_WIDTH / 120);
        invalidate();
    }

    @SuppressLint("DrawAllocation")
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        Paint tbPaint = new Paint();
        tbPaint.setColor(Color.BLACK);
        tbPaint.setStrokeWidth(BARCODE_LINE_WIDTH);

        Paint twPaint = new Paint();
        twPaint.setColor(Color.WHITE);
        canvas.drawRect(new Rect(0, 0, BARCODE_WIDTH, BARCODE_HEIGHT), twPaint);

        Paint separatorPaint = new Paint();
        separatorPaint.setColor(Color.RED);
        separatorPaint.setStrokeWidth(BARCODE_LINE_WIDTH);

        Paint textPaint = new Paint();
        textPaint.setColor(Color.RED);
        textPaint.setTextSize(30);
        textPaint.setAntiAlias(true);

        int startX = 10;

        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;
        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;

        for (int i = 0; i < 6; i++) {
            drawBarcodeSection(canvas, startX, code[i], L, tbPaint);
            canvas.drawText(String.valueOf(code[i]), startX + BARCODE_LINE_WIDTH * 3, BARCODE_HEIGHT + 30, textPaint);
            startX += 7 * BARCODE_LINE_WIDTH;
        }

        startX += BARCODE_LINE_WIDTH;
        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;
        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;
        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;

        for (int i = 6; i < 12; i++) {
            drawBarcodeSection(canvas, startX, code[i], R, tbPaint);
            canvas.drawText(String.valueOf(code[i]), startX + BARCODE_LINE_WIDTH * 3, BARCODE_HEIGHT + 30, textPaint);
            startX += 7 * BARCODE_LINE_WIDTH;
        }

        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
        startX += BARCODE_LINE_WIDTH * 2;
        canvas.drawLine(startX, 0, startX, BARCODE_HEIGHT, separatorPaint);
    }



    private void drawBarcodeSection(Canvas canvas, int startX, int digit, int[] encoding, Paint paint) {
        int pattern = encoding[digit];
        for (int i = 0; i < 7; i++) {
            if ((pattern & (1 << (6 - i))) != 0) {
                canvas.drawLine(startX + i * BARCODE_LINE_WIDTH, 0, startX + i * BARCODE_LINE_WIDTH, BARCODE_HEIGHT, paint);
            }
        }
    }

}
