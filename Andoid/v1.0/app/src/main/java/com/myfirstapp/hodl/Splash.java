package com.myfirstapp.hodl;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

import androidx.appcompat.app.AppCompatActivity;

public class Splash extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);

        // Use a Handler to delay the launch of the Login activity
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                // Create an Intent to switch to the Login activity
                Intent intent = new Intent(Splash.this, Login.class);
                startActivity(intent);

                // Finish the Splash activity to prevent the user from coming back to it
                finish();
            }
        }, 2000); // 3000 milliseconds = 3 seconds
    }
}
