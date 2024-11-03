package com.example.appbarcode;

import android.Manifest;
import android.content.ContentValues;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.lifecycle.ViewModelProvider;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_WRITE_EXTERNAL_STORAGE = 1;
    private BarcodeView barcodeView;
    private EditText inputCode;
    private BarcodeViewModel barcodeViewModel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        barcodeView = findViewById(R.id.barcodeView);
        inputCode = findViewById(R.id.inputCode);

        barcodeViewModel = new ViewModelProvider(this).get(BarcodeViewModel.class);

        if (barcodeViewModel.getBarcodeCode() != null) {
            barcodeView.setCode(barcodeViewModel.getBarcodeCode());
        }

        Button drawButton = findViewById(R.id.drawButton);
        drawButton.setOnClickListener(v -> {
            String codeText = inputCode.getText().toString();
            if (codeText.length() == 12) {
                int[] codeArray = new int[12];
                for (int i = 0; i < 12; i++) {
                    codeArray[i] = Character.getNumericValue(codeText.charAt(i));
                }
                barcodeView.enableValidationMessage(true);
                barcodeView.setCode(codeArray);
                barcodeViewModel.setBarcodeCode(codeArray);
                barcodeView.enableValidationMessage(false);
            } else {
                Toast.makeText(this, "UPC-A musí mít 12 číslic.", Toast.LENGTH_SHORT).show();
            }
        });

        Button saveButton = findViewById(R.id.saveButton);
        saveButton.setOnClickListener(v -> saveBarcodeToGallery());
    }

    public void onConfigurationChanged(@NonNull Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        barcodeView.updateBarcodeSize();
    }

    private void saveBarcodeToGallery() {
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.Q) {
            saveBarcode();
        } else {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},
                        REQUEST_WRITE_EXTERNAL_STORAGE);
            } else {
                saveBarcode();
            }
        }
    }


    private void saveBarcode() {
        int padding = 30;
        int bitmapWidth = barcodeView.getWidth() + 2 * padding;
        int bitmapHeight = barcodeView.getHeight() + 2 * padding + 50;

        Bitmap bitmap = Bitmap.createBitmap(bitmapWidth, bitmapHeight, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);

        canvas.drawColor(Color.WHITE);

        canvas.translate(padding, padding);

        barcodeView.draw(canvas);

        ContentValues values = new ContentValues();
        values.put(MediaStore.Images.Media.DISPLAY_NAME, "barcode_" + System.currentTimeMillis() + ".png");
        values.put(MediaStore.Images.Media.MIME_TYPE, "image/png");

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.Q) {
            values.put(MediaStore.Images.Media.RELATIVE_PATH, "Pictures/Barcodes");
        }

        Uri uri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);
        if (uri != null) {
            try (OutputStream out = getContentResolver().openOutputStream(uri)) {
                if (out != null) {
                    bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
                    Toast.makeText(this, "Čárový kód uložen do galerie.", Toast.LENGTH_SHORT).show();
                }
            } catch (Exception e) {
                Toast.makeText(this, "Chyba při ukládání čárového kódu.", Toast.LENGTH_SHORT).show();
                e.printStackTrace();
            }
        } else {
            Toast.makeText(this, "Chyba při vytváření souboru pro čárový kód.", Toast.LENGTH_SHORT).show();
        }
    }


    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putIntArray("barcode_code", barcodeView.getCode());
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        if (savedInstanceState.containsKey("barcode_code")) {
            int[] savedCode = savedInstanceState.getIntArray("barcode_code");
            if (savedCode != null) {
                barcodeView.setCode(savedCode);
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == REQUEST_WRITE_EXTERNAL_STORAGE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                saveBarcode();
            } else {
                Toast.makeText(this, "Permission denied to save barcode.", Toast.LENGTH_SHORT).show();
            }
        }
    }
}
