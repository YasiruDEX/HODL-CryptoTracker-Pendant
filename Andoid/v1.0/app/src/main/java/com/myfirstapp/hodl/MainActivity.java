package com.myfirstapp.hodl;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.myfirstapp.hodl.databinding.ActivityMainBinding;

public class
MainActivity extends AppCompatActivity {

    ActivityMainBinding binding;
    String CelestialBody;
    String TimesInt;

    String Stop_loss;
    String take_profit;
    FirebaseDatabase db;
    DatabaseReference reference;

    // Assuming your button has an ID named "buttonSwitchPage"
//    Button buttonSwitchPage = findViewById(R.id.login);


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Switch chart_view = findViewById(R.id.chart_switch);

        Intent intent = getIntent();
        if (intent != null) {
            String username = intent.getStringExtra("USERNAME");
            if (username != null) {
                // Assuming you have a TextView with the id greetingTextView
                TextView greetingTextView = findViewById(R.id.greetingTextView);
                greetingTextView.setText("Hello, " + username);
            }
        }

        binding.button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Stop_loss = binding.autoCompleteTextView4.getText().toString();
                take_profit = binding.autoCompleteTextView3.getText().toString();

                if (!Stop_loss.isEmpty() && !take_profit.isEmpty() && !take_profit.equals(" ") && !Stop_loss.equals(" ")) {
                db = FirebaseDatabase.getInstance();
                    reference = db.getReference("stop_loss");
                    reference.setValue(Stop_loss);
                    reference = db.getReference("take_profit");
                    reference.setValue(take_profit).addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(@NonNull Task<Void> task) {

//                            binding.autoCompleteTextView.setText("");
                            Toast.makeText(MainActivity.this, "Margins Set", Toast.LENGTH_SHORT).show();
                            binding.autoCompleteTextView3.setText(" ");
                            binding.autoCompleteTextView4.setText(" ");

                        }
                    });
                } else {
                    Toast.makeText(MainActivity.this, "Margins cannot set empty", Toast.LENGTH_SHORT).show();
                }

            }
        });

        binding.button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                CelestialBody = binding.autoCompleteTextView.getText().toString();
                TimesInt = binding.autoCompleteTextView2.getText().toString();

                if(!CelestialBody.isEmpty()){
                    Celestial celestial = new Celestial(CelestialBody);
                    Celestial time_int_obj = new Celestial(TimesInt);
                    db = FirebaseDatabase.getInstance();
                    reference = db.getReference("need_chart");
                    reference.setValue(chart_view.isChecked());
                    reference = db.getReference("time_interval");
                    reference.setValue(TimesInt);
                    reference = db.getReference("current_coin");
                    reference.setValue(CelestialBody).addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(@NonNull Task<Void> task) {

//                            binding.autoCompleteTextView.setText("");
                            Toast.makeText(MainActivity.this, "Coin Set", Toast.LENGTH_SHORT).show();

                        }
                    });
                }

            }
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
        // Handle onResume functionality here if needed
        String[] celestial = getResources().getStringArray(R.array.coin_list);
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(this, R.layout.dropdown_item,celestial);
        binding.autoCompleteTextView.setAdapter(arrayAdapter);

        String[] times = getResources().getStringArray(R.array.times_list);
        ArrayAdapter<String> arrayAdapter2 = new ArrayAdapter<>(this, R.layout.dropdown_item,times);
        binding.autoCompleteTextView2.setAdapter(arrayAdapter2);
    }

}
