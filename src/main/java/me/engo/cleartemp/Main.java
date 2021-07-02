package me.engo.cleartemp;

import me.engo.cleartemp.assets.API;

import java.io.IOException;

public class Main {

    public static void main(String[] args)
    {
        try
        {
            //START API AS MAIN METHOD
            API.clearTemp(args);
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
