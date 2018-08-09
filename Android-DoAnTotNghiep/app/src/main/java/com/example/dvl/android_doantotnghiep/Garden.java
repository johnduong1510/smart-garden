package com.example.dvl.android_doantotnghiep;

/**
 * Created by Admin on 30/11/2016.
 */

public class Garden {
    private int temperature;
    private int high_temperature;
    private int low_temperature;
    private int soil_hudmity;
    private int humidity;
    private int low_humidity;
    private int high_humidity;

    public void setHumidity(int humidity) {
        this.humidity = humidity;
    }

    public void setLow_humidity(int low_humidity) {
        this.low_humidity = low_humidity;
    }

    public void setHigh_humidity(int high_humidity) {
        this.high_humidity = high_humidity;
    }

    public int getHumidity() {

        return humidity;
    }

    public int getLow_humidity() {
        return low_humidity;
    }

    public int getHigh_humidity() {
        return high_humidity;
    }

    private int high_soilhumidity;
    private int low_soilhumidity;
    private boolean watering;
    private boolean mode;
    private  String chuoi="";

    public void setChuoi(String chuoi) {
        this.chuoi = chuoi;
    }

    public String getChuoi() {

        return chuoi;
    }

    public void setMode(boolean mode) {
        this.mode = mode;
    }
    public boolean isMode() {
        return mode;
    }
    public Garden() {
        temperature = low_temperature = high_temperature = 0;
        soil_hudmity = high_soilhumidity = low_soilhumidity = 0;
        watering = false;
    }
    public Garden(String tempe,String soil_moisture,String high_tempe,String low_temp,String high_soil_moisture,String low_soil_moisture){
        this.temperature=Integer.valueOf(tempe);
        this.soil_hudmity=Integer.valueOf(soil_moisture);
        this.high_temperature=Integer.valueOf(high_tempe);
        this.low_temperature=Integer.valueOf(low_temp);
        this.high_soilhumidity=Integer.valueOf(high_soil_moisture);
        this.low_soilhumidity=Integer.valueOf(low_soil_moisture);
    }

    public boolean isWatering() {
        return watering;
    }

    public int getHigh_soilhumidity() {
        return high_soilhumidity;
    }

    public int getLow_soilhumidity() {
        return low_soilhumidity;
    }

    public void setHigh_soilhumidity(int high_soilhumidity) {

        this.high_soilhumidity = high_soilhumidity;
    }

    public void setLow_soilhumidity(int low_soilhumidity) {
        this.low_soilhumidity = low_soilhumidity;
    }


    public void setWatering(boolean watering) {
        this.watering = watering;
    }


    public int getTemperature() {
        return temperature;
    }

    public int getHigh_temperature() {
        return high_temperature;
    }

    public int getLow_temperature() {
        return low_temperature;
    }

    public int getSoil_hudmity() {
        return soil_hudmity;
    }


    public void setTemperature(int temperature) {

        this.temperature = temperature;
    }

    public void setHigh_temperature(int high_temperature) {
        this.high_temperature = high_temperature;
    }

    public void setLow_temperature(int low_temperature) {
        this.low_temperature = low_temperature;
    }

    public void setSoil_hudmity(int soil_hudmity) {
        this.soil_hudmity = soil_hudmity;
    }

}
