package com.example.fastfuel;

import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class UserInterfacePage extends AppCompatActivity implements View.OnClickListener {

    public CardView card1, card2,card3,card4, card5,card6;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_interface_page);

        card1 = (CardView) findViewById(R.id.my_profile);
        card2 = (CardView) findViewById(R.id.view_balance);
        card3 = (CardView) findViewById(R.id.recharge_wallet);
        card4 = (CardView) findViewById(R.id.history);
        card5 = (CardView) findViewById(R.id.notifications);
        card6 = (CardView) findViewById(R.id.current_price);

        card1.setOnClickListener(this);
        card2.setOnClickListener(this);
        card3.setOnClickListener(this);
        card4.setOnClickListener(this);
        card5.setOnClickListener(this);
        card6.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        Intent i;
        if (v.getId() == R.id.my_profile) {
            i = new Intent(this, ProfileActivity.class);
            i.putExtra("name", getIntent().getStringExtra("name"));
            i.putExtra("email", getIntent().getStringExtra("email"));
            i.putExtra("username", getIntent().getStringExtra("username"));
            i.putExtra("password", getIntent().getStringExtra("password"));
            startActivity(i);
        } else if (v.getId() == R.id.view_balance) {
            i = new Intent(this, balance.class);
            startActivity(i);
        } else if (v.getId() == R.id.recharge_wallet) {
            i = new Intent(this, wallet.class);
            startActivity(i);
        } else if (v.getId() == R.id.history) {
            i = new Intent(this, fortag.class);
            startActivity(i);
        } else if (v.getId() == R.id.notifications) {
            i = new Intent(this, ProfileActivity.class);
            startActivity(i);
        } else if (v.getId() == R.id.current_price) {
            i = new Intent(this, wallet.class);
            startActivity(i);
        }
    }
}