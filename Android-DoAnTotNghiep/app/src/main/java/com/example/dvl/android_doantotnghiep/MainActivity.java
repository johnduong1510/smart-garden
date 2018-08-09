package com.example.dvl.android_doantotnghiep;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.AsyncTask;
import android.os.CountDownTimer;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.Toast;

import com.kyleduo.switchbutton.SwitchButton;
import com.tomer.fadingtextview.FadingTextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Objects;

import static android.graphics.Paint.ANTI_ALIAS_FLAG;
import static com.tomer.fadingtextview.FadingTextView.SECONDS;

public class MainActivity extends AppCompatActivity implements Server.DataFromServer{
    Garden garden;
    View v;
    String link="http://vuonthongminh.esy.es/template1/lib/data.json";
    String datalink="http://vuonthongminh.esy.es/template1/lib/uploadFromAndroid.php?";
    Integer image[] = {R.drawable.thermometer,R.drawable.settings_temp,R.drawable.humudity_icon,R.drawable.settings_humidity,R.drawable.soil_humidityicon, R.drawable.settings_soil_humidity};
    String data[] = {"0℃","0℃\n0℃","0%","0%\n0%","0%","0%\n0%"};
    Server server;
    Thread updating;
    FloatingActionButton fabMode;
    boolean updating_flag=false;
    /*Component*/
    GridView gridView;
    FadingTextView fadingTextView_1,fadingTextView_2;
    GridViewAdapter adapter;
    SwitchButton switchWatering;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        garden=new Garden();
        server=new Server(MainActivity.this);
        server.setContainer(MainActivity.this);
        /*Anh xa component*/
        fabMode = (FloatingActionButton) findViewById(R.id.fabMode);
        switchWatering = (SwitchButton) findViewById(R.id.waterSwitchButton);
        gridView = (GridView) findViewById(R.id.gridView);
        fadingTextView_1=(FadingTextView)findViewById(R.id.fadingTextView);
        fadingTextView_2=(FadingTextView)findViewById(R.id.fadingTextView_2);
        fadingTextView_1.setTimeout(3,SECONDS);
        fadingTextView_2.setTimeout(3,SECONDS);
        updateFadingTextView("Không có thông báo",1);
        updateFadingTextView("Không có thông báo",2);
        //Thiet lap Adapter cho grid view
        adapter = new GridViewAdapter(MainActivity.this, image, data);//Thiet lap adapter va du lieu gia ban dau
        gridView.setAdapter(adapter);

        /*Doc Json*/
        server.readJsonFromServer(link);
        updating=new Thread(new Update());
        updating_flag=true;
        updating.start();
        //Toast.makeText(MainActivity.this,garden.getTemperature()+"",Toast.LENGTH_SHORT).show();
        /*Sau khi lay du lieu xong thi cap nhap lai UI*/
        /*Restart UI*/
        String dulieu[]={String.valueOf(garden.getTemperature()),String.valueOf(garden.getSoil_hudmity()),String.valueOf(garden.getLow_temperature()),
                String.valueOf(garden.getHigh_temperature()),String.valueOf(garden.getLow_soilhumidity()),String.valueOf(garden.getHigh_soilhumidity())};
        updateUI(dulieu);

        /***********************************Catch Events*****************************************/
        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
                if(position==1)
                {
                    updating_flag=false;
                    createCustomTemperatureDialog();
                }
                else if(position==3)
                {
                    updating_flag=false;
                    createCustomHumidityDialog();

                }
                else if(position==5)
                {
                    updating_flag=false;
                    createCustomSoilHumidity();
                }
            }
        });

        fabMode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                updating_flag=false;
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                String tam=datalink+"mode="+!garden.isMode();
                Log.d("tam",tam);
                new AsyncTask<String, Void, String>() {
                    ProgressDialog myProgressDialog;
                    @Override
                    protected void onPreExecute() {
                        super.onPreExecute();
                        myProgressDialog=ProgressDialog.show(MainActivity.this,"Mode","Loading..",false,true);
                    }

                    @Override
                    protected String doInBackground(String... strings) {
                        String chuoi=server.getStringFromURL(strings[0]);
                        return chuoi;
                    }

                    @Override
                    protected void onPostExecute(String s) {
                        super.onPostExecute(s);
                        //Toast.makeText(MainActivity.this,s,Toast.LENGTH_SHORT).show();
                        if(s!=null && s.contains("mode:OK")) myProgressDialog.dismiss();
                    }
                }.execute(tam);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        updating_flag=true;
                        updating.run();
                    }
                }).start();
            }
        });

        switchWatering.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                updating_flag=false;
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                String tam=datalink+"isWatering="+switchWatering.isChecked();
                new AsyncTask<String, Void, String>() {
                    ProgressDialog myProgressDialog;
                    @Override
                    protected void onPreExecute() {
                        super.onPreExecute();
                        myProgressDialog=ProgressDialog.show(MainActivity.this,"Watering","Loading..",false,true);
                    }

                    @Override
                    protected String doInBackground(String... strings) {
                        String chuoi=server.getStringFromURL(strings[0]);
                        return chuoi;
                    }

                    @Override
                    protected void onPostExecute(String s) {
                        super.onPostExecute(s);
                        //Toast.makeText(MainActivity.this,s,Toast.LENGTH_SHORT).show();
                        if(s!=null && s.contains("isWatering:OK")) myProgressDialog.dismiss();
                    }
                }.execute(tam);
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        updating_flag=true;
                        updating.run();
                    }
                }).start();
            }
        });



        /***********************************Custom Fuction*********************************************/
    }

    /*Tao hop thoai Dialog tuy chon, cho phep nhan cac gia tri nguong cao, nguong thap*/
    public void createCustomHumidityDialog() {
        AlertDialog.Builder mydialog = new AlertDialog.Builder(MainActivity.this);
        LayoutInflater inflater = getLayoutInflater();
        v = inflater.inflate(R.layout.settings_humidity_dialog, null);
        mydialog.setView(v);
        mydialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                Thread tam = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        updating_flag = true;
                        updating.run();
                    }
                });
                tam.start();

            }
        });
        mydialog.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, final int which) {
                EditText etLowHumi = (EditText) v.findViewById(R.id.etLowHumidity);
                EditText etHighHumi = (EditText) v.findViewById(R.id.etHighHumidity);
                if (!etLowHumi.getText().toString().isEmpty() || !etHighHumi.getText().toString().isEmpty()) {
                    final String LowHumi = etLowHumi.getText().toString();
                    final String HighHumi = etHighHumi.getText().toString();
                    //Gui data
                    //den server de cap nhap
                    Thread tam=new Thread(new Runnable() {
                        @Override
                        public void run() {
                            if(!LowHumi.equalsIgnoreCase(""))server.sendDataToWebServer(datalink,"setup_low_moisture",LowHumi);
                            if(!HighHumi.equalsIgnoreCase(""))server.sendDataToWebServer(datalink,"setup_high_moisture",HighHumi);
                            updating_flag=true;
                            updating.run();
                        }
                    });
                    tam.start();
                    //
                    //
                } else dialog.dismiss();
            }
        });
        mydialog.show();
    }


    /*Tao hop thoai Dialog tuy chon, cho phep nhan cac gia tri nguong cao, nguong thap*/
    public void createCustomTemperatureDialog() {
        AlertDialog.Builder mydialog = new AlertDialog.Builder(MainActivity.this);
        LayoutInflater inflater = getLayoutInflater();
        v = inflater.inflate(R.layout.settings_temperature_dialog, null);
        mydialog.setView(v);
        mydialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                Thread tam = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        updating_flag = true;
                        updating.run();
                    }
                });
                tam.start();

            }
        });
        mydialog.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, final int which) {
                EditText etLowTemp = (EditText) v.findViewById(R.id.etLowTemperature);
                EditText etHighTemp = (EditText) v.findViewById(R.id.etHighTemperature);
                if (!etLowTemp.getText().toString().isEmpty() || !etHighTemp.getText().toString().isEmpty()) {
                    final String LowTemp = etLowTemp.getText().toString();
                    final String HighTemp = etHighTemp.getText().toString();
                    //Gui data
                    //den server de cap nhap
                    Thread tam=new Thread(new Runnable() {
                        @Override
                        public void run() {
                            if(!LowTemp.equalsIgnoreCase(""))server.sendDataToWebServer(datalink,"setup_low_tempe",LowTemp);
                            if(!HighTemp.equalsIgnoreCase(""))server.sendDataToWebServer(datalink,"setup_high_tempe",HighTemp);
                            updating_flag=true;
                            updating.run();
                        }
                    });
                    tam.start();
                    //
                    //
                } else dialog.dismiss();
            }
        });
        mydialog.show();
    }

    /*Tao hop thoai Dialog tuy chon, cho phep nhan cac gia tri nguong cao, nguong thap*/
    public void createCustomSoilHumidity() {
        AlertDialog.Builder mydialog = new AlertDialog.Builder(MainActivity.this);
        LayoutInflater inflater = getLayoutInflater();
        v = inflater.inflate(R.layout.settings_soilhumidity_dialog, null);
        mydialog.setView(v);
        mydialog.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                Thread tam = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        updating_flag = true;
                        updating.run();
                    }
                });
                tam.start();
            }
        });
        mydialog.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                EditText etLowSoilHumidity = (EditText) v.findViewById(R.id.etLowSoilHumidity);
                EditText etHighSoilHumidity = (EditText) v.findViewById(R.id.etHighSoilHumidity);
                if (!etLowSoilHumidity.getText().toString().isEmpty() || !etHighSoilHumidity.getText().toString().isEmpty()) {
                    final String LowSoilHumidity = etLowSoilHumidity.getText().toString();
                    final String HighSoilHumidity = etHighSoilHumidity.getText().toString();
                    //Gui data
                    //den server de cap nhap
                    //
                    Thread tam=new Thread(new Runnable() {
                        @Override
                        public void run() {
                            if(!LowSoilHumidity.equalsIgnoreCase("")) server.sendDataToWebServer(datalink,"setup_low_soil_moisture",LowSoilHumidity);
                            if(!HighSoilHumidity.equalsIgnoreCase("")) server.sendDataToWebServer(datalink,"setup_high_soil_moisture",HighSoilHumidity);
                            updating_flag=true;
                            updating.run();
                        }
                    });
                    tam.start();
                } else dialog.dismiss();
            }
        });
        mydialog.show();
    }


    public void updateFadingTextView(String newtext,int position)
    {
        ArrayList<String> mTexts_1 = new ArrayList<>();
        mTexts_1.add(getString(R.string.default_fadingTextView_1));

        ArrayList<String> mTexts_2 = new ArrayList<>();
        mTexts_2.add(getString(R.string.default_fadingTextView_2));


        if (position == 1) {
            mTexts_1.add(newtext);
            String texts_1[] = new String[mTexts_1.size()];
            texts_1 = mTexts_1.toArray(texts_1);
            fadingTextView_1.setTexts(texts_1);
        }
        if (position == 2) {
            mTexts_2.add(newtext);
            String texts_2[] = new String[mTexts_2.size()];
            texts_2 = mTexts_2.toArray(texts_2);
            fadingTextView_2.setTexts(texts_2);
        }
    }

    public void updateUI(String data[])
    {
        /*Updating gridview apdater*/
        adapter = new GridViewAdapter(MainActivity.this, image, data);
        gridView.setAdapter(adapter);
    }
    public void updateControl(boolean water, boolean mode) {
        /*Update Watering*/
        switchWatering.setChecked(water);
        /*Check mode - if auto then lock switchbutton*/
        if(mode)
        {
            switchWatering.setEnabled(false);
            fabMode.setImageBitmap(textAsBitmap("Auto",80f,Color.WHITE));
        }
        else {
            switchWatering.setEnabled(true);
            fabMode.setImageBitmap(textAsBitmap("Manual",160f,Color.WHITE));
        }
    }

    public static Bitmap textAsBitmap(String text, float textSize, int textColor) {
        Paint paint = new Paint(ANTI_ALIAS_FLAG);
        paint.setTextSize(textSize);
        paint.setColor(textColor);
        paint.setTextAlign(Paint.Align.LEFT);
        float baseline = -paint.ascent(); // ascent() is negative
        int width = (int) (paint.measureText(text) + 0.0f); // round
        int height = (int) (baseline + paint.descent() + 0.0f);
        Bitmap image = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);

        Canvas canvas = new Canvas(image);
        canvas.drawText(text, 0, baseline, paint);
        return image;
    }

    @Override
    public void incomingDataFromServer(Garden garden) {
        this.garden=garden;
        data[0]=getString(R.string.tempe) + "\n" +  garden.getTemperature()+"℃";
        data[1]=garden.getLow_temperature()+"℃\n"+garden.getHigh_temperature()+"℃";
        data[2]=getString(R.string.humidity)+"\n"+garden.getHumidity()+"%";
        data[3]=garden.getLow_humidity()+"%\n"+garden.getHigh_humidity()+"%";
        data[4]=getString(R.string.soil_humidity)+"\n"+garden.getSoil_hudmity()+"%";
        data[5]=garden.getLow_soilhumidity()+"%\n"+garden.getHigh_soilhumidity()+"%";
       /*Update data to gridview*/
        updateUI(data);
        /******Update Control*********/
        updateControl(garden.isWatering(),garden.isMode());
        //Toast.makeText(MainActivity.this,"incomingDataFromServer: "+garden.isMode()+"",Toast.LENGTH_SHORT).show();
    }
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    class Update implements Runnable{

        @Override
        public void run() {
            while (updating_flag)
            {
                server.readJsonFromServer(link);
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }


    @Override
    public void onBackPressed() {
        super.onBackPressed();
        updating_flag=false;
        MainActivity.this.finish();
    }
}

