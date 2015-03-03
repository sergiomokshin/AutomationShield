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
import android.widget.Toast;


import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;


public class Main extends ActionBarActivity {

    private String StatusSaida1 = "0";
    private String StatusSaida2 = "0";
    private String StatusSaida3 = "0";
    private String StatusSaida4 = "0";

    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket btSocket = null;
    private BluetoothDevice device = null;
    private String address = "";

    private UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btSaida1 = (Button) findViewById(R.id.btSaida1);
        Button btSaida2 = (Button) findViewById(R.id.btSaida2);
        Button btSaida3 = (Button) findViewById(R.id.btSaida3);
        Button btSaida4 = (Button) findViewById(R.id.btSaida4);

        SeekBar seekBarR = (SeekBar) findViewById(R.id.seekR);
        SeekBar seekBarG = (SeekBar) findViewById(R.id.seekG);
        SeekBar seekBarB = (SeekBar) findViewById(R.id.seekB);

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

        btSaida3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("3");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        btSaida4.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("4");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        seekBarR.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                // TODO Auto-generated method stub
                try {
                    EnviarRGB("6", progress);
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });

        seekBarG.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                // TODO Auto-generated method stub
                try {
                    EnviarRGB("5", progress);
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });

        seekBarB.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub

            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress,
                                          boolean fromUser) {
                // TODO Auto-generated method stub
                try {
                    EnviarRGB("3", progress);
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });

        try {
            ConnectDevice();
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
            StatusSaida1 = (StatusSaida1 == "1") ? "0" : "1";
            comando += StatusSaida1 + "|";
        }
        if (Saida == "2") {
            StatusSaida2 = (StatusSaida2 == "1") ? "0" : "1";
            comando += StatusSaida2 + "|";
        }
        if (Saida == "3") {
            StatusSaida3 = (StatusSaida3 == "1") ? "0" : "1";
            comando += StatusSaida3 + "|";
        }
        if (Saida == "4") {
            StatusSaida4 = (StatusSaida4 == "1") ? "0" : "1";
            comando += StatusSaida4 + "|";
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

}
