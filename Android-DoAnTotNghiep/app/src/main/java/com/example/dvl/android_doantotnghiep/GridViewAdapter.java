package com.example.dvl.android_doantotnghiep;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

/**
 * Created by Admin on 1/12/2016.
 */

public class GridViewAdapter extends BaseAdapter {
    Context c;
    Integer image[];
    String data[];

    public GridViewAdapter(Context c, Integer image[], String data[])
    {
        this.c=c;
        this.image=image;
        this.data=data;
    }

    @Override
    public int getCount() {
        return image.length;
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    class ViewHolder{
        public ImageView imageView;
        public TextView textView;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater=((Activity)c).getLayoutInflater();
        ViewHolder viewHolder;
        if(convertView==null)
        {
            if(position==0 || position==2 || position==4) convertView=inflater.inflate(R.layout.gridview_item,null);
            else if(position==1 || position==3 || position==5) convertView=inflater.inflate(R.layout.gridview_item_2,null);
            viewHolder=new ViewHolder();
            viewHolder.imageView=(ImageView)convertView.findViewById(R.id.imageView1);
            viewHolder.textView=(TextView)convertView.findViewById(R.id.textView1);
            convertView.setTag(viewHolder);
        }
        else viewHolder=(ViewHolder)convertView.getTag();
        /*Fill data*/
        viewHolder.imageView.setImageResource(image[position]);
        viewHolder.textView.setText(data[position]);
        return convertView;
    }
}
