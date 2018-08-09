package com.example.dvl.android_doantotnghiep;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import es.dmoral.toasty.Toasty;

public class LoginActivity extends AppCompatActivity {
    EditText edt_username,edt_password;
    Button btLogin;
    String link="http://vuonthongminh.esy.es/template1/lib/getdata.php?";
    ProgressDialog progressDialog;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        edt_username=(EditText)findViewById(R.id.edt_username);
        edt_password=(EditText)findViewById(R.id.edt_password);
        btLogin=(Button)findViewById(R.id.btLogin);

        btLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String usr=edt_username.getText().toString();
                String passwd=edt_password.getText().toString();
                String temp=link+"username="+usr+"&password="+passwd;
                new Login().execute(temp);
            }
        });
    }

    class Login extends AsyncTask<String,Void,String>{

        @Override
        protected String doInBackground(String... strings) {
            String chuoi=getStringFromURL(strings[0]);
            return chuoi;
        }

        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            progressDialog=new ProgressDialog(LoginActivity.this);
            progressDialog.setTitle("Login");
            progressDialog.setMessage("Loading...");
            progressDialog.show();
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            progressDialog.dismiss();
            if(s.contains("successfully")) {
                Toasty.success(LoginActivity.this,"Login successfully",Toast.LENGTH_SHORT,true).show();
                startActivity(new Intent(LoginActivity.this,MainActivity.class));
                LoginActivity.this.finish();
            }
            else Toasty.error(LoginActivity.this,"Login failed",Toast.LENGTH_SHORT,true).show();
        }
    }

    public String getStringFromURL(String urlString)
    {

        try {
            URL url=new URL(urlString);
            HttpURLConnection urlConnection=(HttpURLConnection) url.openConnection();
            urlConnection.connect();
            InputStream in=urlConnection.getInputStream();
            BufferedReader reader=new BufferedReader(new InputStreamReader(in,"UTF-8"));
            String data = "",tam="";
            while ((tam = reader.readLine()) != null){
                data += tam + "\n";
            }
            urlConnection.disconnect();
            in.close();
            reader.close();
            return data;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
