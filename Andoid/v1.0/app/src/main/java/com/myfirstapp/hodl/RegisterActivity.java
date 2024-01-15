package com.myfirstapp.hodl;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.textfield.TextInputLayout;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class RegisterActivity extends AppCompatActivity {

    FirebaseDatabase db;
    DatabaseReference reference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        Button registerButton = findViewById(R.id.register2);
        TextInputLayout usernameRegisterTextInputLayout = findViewById(R.id.username_register2);
        TextInputLayout passwordRegisterTextInputLayout = findViewById(R.id.password_register2);

        TextView login_button = findViewById(R.id.login_hv_acc);

        login_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(RegisterActivity.this, Login.class);
                startActivity(intent);
            }
        });

        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Registration functionality
                String newUsername = usernameRegisterTextInputLayout.getEditText().getText().toString();
                String newPassword = passwordRegisterTextInputLayout.getEditText().getText().toString();

                db = FirebaseDatabase.getInstance();
                reference = db.getReference("Users");

                // Check if the username already exists
                reference.child(newUsername).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                        if (dataSnapshot.exists()) {
                            Toast.makeText(RegisterActivity.this, "Username already exists, choose another one.", Toast.LENGTH_SHORT).show();
                        } else {
                            // If username doesn't exist, create a new user
                            reference.child(newUsername).setValue(newPassword);
                            Toast.makeText(RegisterActivity.this, "Account created successfully", Toast.LENGTH_SHORT).show();

                            // Pass the username to LoginActivity
                            Intent intent = new Intent(RegisterActivity.this, Login.class);
                            startActivity(intent);
                        }
                    }

                    @Override
                    public void onCancelled(@NonNull DatabaseError databaseError) {
                        Toast.makeText(RegisterActivity.this, "Database error", Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
    }
}