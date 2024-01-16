package com.myfirstapp.hodl;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;

public class Splash extends AppCompatActivity {

    private TextView loadingDots;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);

        loadingDots = findViewById(R.id.textView3);

        // Set dark mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
            // Use system default dark mode
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_FOLLOW_SYSTEM);
        } else {
            // Use a custom dark mode for versions earlier than Android 10
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
        }

        // Start loading dots animation
        startLoadingDotsAnimation();

        // Set a timer for 4 seconds, then go to the Login activity for Android 13 and above
        new CountDownTimer(3000, 1000) {
            public void onTick(long millisUntilFinished) {
                // Not needed for this example
            }

            public void onFinish() {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                    // For Android 13 and above
                    Intent intent = new Intent(Splash.this, Login.class);
                    startActivity(intent);
                    finish();
                }
            }
        }.start();
    }

    private void startLoadingDotsAnimation() {
        new CountDownTimer(Long.MAX_VALUE, 1000) {
            int dotCount = 0;

            public void onTick(long millisUntilFinished) {
                switch (dotCount % 3) {
                    case 0:
                        loadingDots.setText(".");
                        break;
                    case 1:
                        loadingDots.setText("..");
                        break;
                    case 2:
                        loadingDots.setText("...");
                        break;
                }
                dotCount++;
            }

            public void onFinish() {
                // Not needed for this example
            }
        }.start();
    }
}
