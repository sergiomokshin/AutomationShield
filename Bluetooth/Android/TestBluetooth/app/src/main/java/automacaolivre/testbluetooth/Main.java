package automacaolivre.testbluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.SeekBar;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;
import android.widget.Toast;
import android.os.Handler;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.util.Set;
import java.util.UUID;


public class Main extends ActionBarActivity {

    private String StatusSaida1 = "0";
    private String StatusSaida2 = "0";

    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private BluetoothDevice device = null;
    private String address = "";
    private boolean stopWorker = false;
    private int readBufferPosition = 0;
    private byte[] readBuffer = new byte[1024];
    private InputStream inStream;
    byte delimiter = 10;
    Handler handler = new Handler();

    private Button btSaida1;
    private Button btSaida2;

    private int ValueSaida1;
    private int ValueSaida2;


    private UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        btSaida1 = (Button) findViewById(R.id.btSaida1);
        btSaida2 = (Button) findViewById(R.id.btSaida2);

        btSaida1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("1");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        btSaida2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("2");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });


        try {
            ConnectDevice();
            beginListenForCommands();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void EnviarRGB(String Porta, int Progress) throws IOException {
        String comando = "|A" + Porta + String.valueOf(Progress) + "|";
        writeData(comando);
    }

    private void EnviarComandoDigital(String Saida) throws IOException {
        //|D21|
        String comando = "|D" + Saida;

        if (Saida == "1") {
            StatusSaida1 = "1";
            comando += StatusSaida1 + "|";
        }
        if (Saida == "2") {
            StatusSaida2 = (ValueSaida2 == 1) ? "0" : "1";
            comando += StatusSaida2 + "|";
        }

        //int duracao = Toast.LENGTH_SHORT;
        //Toast toast = Toast.makeText(getApplicationContext(), comando, duracao);
        //toast.show();

        writeData(comando);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void ConnectDevice() throws IOException {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            int duracao = Toast.LENGTH_SHORT;
            Toast toast = Toast.makeText(getApplicationContext(), "Bluetooth desativado / não encontrado!", duracao);
            toast.show();
        }

        if (!mBluetoothAdapter.enable()) {
            int duracao = Toast.LENGTH_SHORT;
            Toast toast = Toast.makeText(getApplicationContext(), "Bluetooth desativado!", duracao);
            toast.show();
        }


        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        if (pairedDevices == null || pairedDevices.size() == 0) {
            int duracao = Toast.LENGTH_SHORT;
            Toast toast = Toast.makeText(getApplicationContext(), "Nenhum dispositivo pareado!", duracao);
            toast.show();

        } else {

            for (BluetoothDevice bluetoothDevice : pairedDevices) {
                if (bluetoothDevice.getName().equalsIgnoreCase("linvor") || bluetoothDevice.getName().equalsIgnoreCase("hc-06")) {

                    device = bluetoothDevice;

                   // int duracao = Toast.LENGTH_SHORT;
                  ///  Toast toast = Toast.makeText(getApplicationContext(), "Pareado com:" + this.device.getName(), duracao);
                  //  toast.show();

                    address = this.device.getAddress();


                    if (this.device.getUuids() != null && this.device.getUuids().length > 0) {
                        this.MY_UUID = this.device.getUuids()[0].getUuid();
                    }


                    mBluetoothAdapter.cancelDiscovery();

                    //btSocket = device.createInsecureRfcommSocketToServiceRecord(MY_UUID);
                    //btSocket.connect();

                    //BluetoothSocket socket = null;

                    try {
                        //socket = device.createRfcommSocketToServiceRecord(SERIAL_UUID);
                        btSocket = device.createInsecureRfcommSocketToServiceRecord(MY_UUID);
                    } catch (Exception e) {e.printStackTrace();}

                    try {
                        btSocket.connect();
                    } catch (IOException e) {
                        e.printStackTrace();
                        try {

                            e.printStackTrace();
                            btSocket =(BluetoothSocket) device.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(device,1);
                            btSocket.connect();
                        }
                        catch (Exception e2) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    private void writeData(String data) throws IOException {

        try {
            write(data);
        } catch (IOException ex) {
            ConnectDevice();
            write(data);
        }
    }

    private void write(String data) throws IOException {
        OutputStream outStream = btSocket.getOutputStream();
        byte[] msgBuffer = data.getBytes();
        outStream.write(msgBuffer, 0, msgBuffer.length);

    }


    public void beginListenForCommands()   {
        try {
            inStream = btSocket.getInputStream();
        } catch (IOException e) {
        }

        Thread workerThread = new Thread(new Runnable()
        {
            public void run()
            {
                while(!Thread.currentThread().isInterrupted() && !stopWorker)
                {
                    try
                    {
                        int bytesAvailable = inStream.available();
                        if(bytesAvailable > 0)
                        {
                            byte[] packetBytes = new byte[bytesAvailable];
                            inStream.read(packetBytes);
                            for(int i=0;i<bytesAvailable;i++)
                            {
                                byte b = packetBytes[i];
                                if(b == delimiter)
                                {
                                    byte[] encodedBytes = new byte[readBufferPosition];
                                    System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                    final String data = new String(encodedBytes, "US-ASCII");
                                    readBufferPosition = 0;
                                    handler.post(new Runnable()
                                    {
                                        public void run() {

                                            if (data.contains("COMANDOS")) {

                                                String[] DataCommand = data.split("#");

                                                ValueSaida1 = Integer.parseInt(DataCommand[1]);
                                                ValueSaida2 = Integer.parseInt(DataCommand[2]);

                                                if(ValueSaida1 == 1) {
                                                    btSaida1.setText("Botão 1 - ON");
                                                }
                                                else {
                                                    btSaida1.setText("Botão 1 - OFF");
                                                }

                                                if(ValueSaida2 == 1) {
                                                    btSaida2.setText("Botão 2 - ON");
                                                }
                                                else {
                                                    btSaida2.setText("Botão 2 - OFF");
                                                }
                                            }

                                           //txtMsg.setText(data);


                                        }
                                    });
                                }
                                else
                                {
                                    readBuffer[readBufferPosition++] = b;
                                }
                            }
                        }
                    }
                    catch (IOException ex)
                    {
                        stopWorker = true;
                    }
                }
            }
        });

        workerThread.start();
    }

}
