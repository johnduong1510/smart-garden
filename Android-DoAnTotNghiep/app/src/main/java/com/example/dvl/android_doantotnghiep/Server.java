package com.example.dvl.android_doantotnghiep;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

/**
 * Created by John on 4/2/2017.
 */

public class Server {

    Garden garden;
    Context c;
    DataFromServer dataFromServer;
    public Server(){
        garden=new Garden();
    }
    public Server(Context c){this.c=c;garden=new Garden();}
    public void readJsonFromServer(String link){
        new ReadJson().execute(link);
    }
    public void sendDataToWebServer(String datalink,String name,String data)
    {
        datalink+=name+"="+data;
        new SendToWebServer().execute(datalink);
    }

    public void setContainer(DataFromServer dataFromServer)
    {
        this.dataFromServer=dataFromServer;
    }

    public interface DataFromServer
    {
        void incomingDataFromServer(Garden garden);
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

    public String sendRequestToWebServer(String url)
    {
        return null;
    }

    /*----------------------------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------Inner Class gửi dữ liệu lên webserver---------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    class SendToWebServer extends AsyncTask<String,Void,String>
    {

        @Override
        protected String doInBackground(String... strings) {
            String chuoi=getStringFromURL(strings[0]);
            return chuoi;
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            garden.setChuoi(s);
            //Toast.makeText(c,garden.getChuoi(),Toast.LENGTH_SHORT).show();
            dataFromServer.incomingDataFromServer(garden);
        }
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------Inner Class đọc jSon trả về object Garden-----------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------*/
    class ReadJson extends AsyncTask<String,Void,String> {



        @Override
        protected String doInBackground(String... strings) {
            String chuoi = getStringFromURL(strings[0]);
            return chuoi;
        }

        @Override
        protected void onPostExecute(String s) {
            super.onPostExecute(s);
            //  Toast.makeText(MainActivity.this,s,Toast.LENGTH_SHORT).show();
            try {
                //Dua toan bo noi dung lay tu URL la json dua vao jsonObject
                JSONObject jsonObject=new JSONObject(s);
                garden.setTemperature(Integer.valueOf(jsonObject.getString("temperature")));
                garden.setHumidity(Integer.valueOf(jsonObject.getString("moisture")));
                garden.setSoil_hudmity(Integer.valueOf(jsonObject.getString("soil_moisture")));
                garden.setHigh_temperature(Integer.valueOf(jsonObject.getString("high_tempe")));
                garden.setLow_temperature(Integer.valueOf(jsonObject.getString("low_tempe")));
                garden.setHigh_soilhumidity(Integer.valueOf(jsonObject.getString("high_soil_moisture")));
                garden.setLow_soilhumidity(Integer.valueOf(jsonObject.getString("low_soil_moisture")));
                garden.setLow_humidity(Integer.valueOf(jsonObject.getString("low_moisture")));
                garden.setHigh_humidity(Integer.valueOf(jsonObject.getString("high_moisture")));
                garden.setWatering(Boolean.parseBoolean(jsonObject.getString("isWatering")));
                garden.setMode(Boolean.parseBoolean(jsonObject.getString("isMode")));
                dataFromServer.incomingDataFromServer(garden);
            } catch (JSONException e) {
                e.printStackTrace();
            } catch (Exception exce){}
        }


    }
}
