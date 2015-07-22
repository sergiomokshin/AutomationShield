//Android 4.0

package automacaolivre.testbluetooth;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import android.location.Address;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.os.Bundle;
import android.app.Activity;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Switch;
import android.widget.Toast;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.widget.Button;
import android.widget.SeekBar;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;
import android.os.Handler;
import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;


public class Main extends Activity {
    
	private int S1;
	private String NameS1 = "";
    private TextView txtS1;
    private ImageButton imgS1;
    
	private int S2;
	private String NameS2 = "";
    private TextView txtS2;
    private ImageButton imgS2;
    
	private int S3;
	private String NameS3 = "";
    private TextView txtS3;
    private ImageButton imgS3;
    
	private int S4;
	private String NameS4 = "";
    private TextView txtS4;
    private ImageButton imgS4;
    	
	private int SRGB;
	private String NameSRGB = "";	
    private TextView txtSRGB;
  	
    private SeekBar seekBarR;
    private SeekBar seekBarG;
    private SeekBar seekBarB;
    private int SR;
    private int SG;
    private int SB;

    String address;
    Handler handler = new Handler();
    private Boolean FirstTime;
    private boolean stopWorker = false;
    private int readBufferPosition = 0;
    private byte[] readBuffer = new byte[1024];
    private TextView txtMsg;
    byte delimiter = 10;

    private final int REQUEST_CONNECT_DEVICE = 1;
    private final int REQUEST_SETUP_DEVICE = 2;

    private BluetoothAdapter meuAdaptadorBluetooth = null;
    private BluetoothSocket mmSocket = null;
    private BluetoothDevice mmDevice = null;
    private InputStream mmInStream = null;
    private OutputStream mmOutStream = null;

    SharedPreferences.Editor editor;
    SharedPreferences sharedPreferences;
	private UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toast.makeText(this, "Conectando com o dispositivo.", Toast.LENGTH_LONG).show();
        
        imgS1 = (ImageButton) findViewById(R.id.imgS1);
        txtS1 = (TextView) findViewById(R.id.txtS1);
		
		imgS2 = (ImageButton) findViewById(R.id.imgS2);
        txtS2 = (TextView) findViewById(R.id.txtS2);
		
		imgS3 = (ImageButton) findViewById(R.id.imgS3);
        txtS3 = (TextView) findViewById(R.id.txtS3);
		
		imgS4 = (ImageButton) findViewById(R.id.imgS4);
        txtS4 = (TextView) findViewById(R.id.txtS4);
		
        txtSRGB = (TextView) findViewById(R.id.txtSRGB);
        
        seekBarR = (SeekBar) findViewById(R.id.seekR);
        seekBarG = (SeekBar) findViewById(R.id.seekG);
        seekBarB = (SeekBar) findViewById(R.id.seekB);

        AtualizaLabels();

        txtMsg = (TextView) findViewById(R.id.txtMsg);
        FirstTime = true;
     
        imgS1.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("1");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
		
		 imgS2.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("2");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
		
		 imgS3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {
                try {
                    EnviarComandoDigital("3");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
		
		 imgS4.setOnClickListener(new OnClickListener() {
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

        meuAdaptadorBluetooth = BluetoothAdapter.getDefaultAdapter();
        address = sharedPreferences.getString("ADDRESS", "");
        
        if (address == "") {
            Intent intent = new Intent(Intent.ACTION_VIEW);
            intent.setClassName("automacaolivre.testbluetooth", "automacaolivre.testbluetooth.DeviceListActivity");
            startActivityForResult(intent,90);

        } else {
            Connect(false);
        }

    }

    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.my_options_menu, menu);
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {           
            case R.id.DeviceListActivity:
                Intent intentD = new Intent(Intent.ACTION_VIEW);
                intentD.setClassName("automacaolivre.testbluetooth", "automacaolivre.testbluetooth.DeviceListActivity");
                startActivityForResult(intentD,90);
                return true;
            case R.id.SetupDevice:
                Intent intentS = new Intent(Intent.ACTION_VIEW);
                intentS.setClassName("automacaolivre.testbluetooth", "automacaolivre.testbluetooth.SetupDevice");
                startActivityForResult(intentS,90);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void AtualizaLabels() {

        //final SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        sharedPreferences = getSharedPreferences("APP_PREFS", Context.MODE_PRIVATE);
        editor = sharedPreferences.edit();

        NameS1 = sharedPreferences.getString("S1", "Saída 1");
        NameS2 = sharedPreferences.getString("S2", "Saída 2");
        NameS3 = sharedPreferences.getString("S3", "Saída 3");
        NameS4 = sharedPreferences.getString("S4", "Saída 4");        
        NameSRGB = sharedPreferences.getString("SRGB", "ILUMINACAO");

        txtS1.setText(NameS1);
		txtS2.setText(NameS2);
		txtS3.setText(NameS3);
		txtS4.setText(NameS4);		
		txtSRGB.setText(NameSRGB);		       
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (resultCode) {
            case REQUEST_CONNECT_DEVICE:
                    String addressAtual = sharedPreferences.getString("ADDRESS", "");

                    address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
                    sharedPreferences = getSharedPreferences("APP_PREFS", Context.MODE_PRIVATE);
                    editor = sharedPreferences.edit();
                    editor.putString("ADDRESS", address);
                    editor.commit();

                    Boolean alterouDispositivo = (addressAtual.toString() != address.toString());

                    Connect(alterouDispositivo);
                break;
            case REQUEST_SETUP_DEVICE:
                AtualizaLabels();
                break;
        }
    }
  
    private void Connect(Boolean forceConect) {

        if(!forceConect && mmSocket != null && mmSocket.isConnected())
        {
            return;
        }

        meuAdaptadorBluetooth.cancelDiscovery();
        mmDevice = meuAdaptadorBluetooth.getRemoteDevice(address);

        try {

            mmSocket = mmDevice.createRfcommSocketToServiceRecord(MY_UUID);
            if(!mmSocket.isConnected())
            mmSocket.connect();
            mmInStream = mmSocket.getInputStream();
            mmOutStream = mmSocket.getOutputStream();

            String enviada = "";
            byte[] send = enviada.getBytes();
            mmOutStream.write(send);

            beginListenForCommands();

        } catch (IOException e) {
            Toast.makeText(this, "Ocorreu um erro durante a conexão com o Bluetooth, verifique se a placa de automação está ligada e dentro do raio de alcance!", Toast.LENGTH_LONG).show();
        }
    }

    private void EnviarRGB(String Porta, int Progress) throws IOException {

        String comando = "|A" + Porta + String.valueOf(Progress) + "|";
        writeData(comando);

    }

    private void EnviarComandoDigital(String S) throws IOException {

     
        //|D21|
        String comando = "|D" + S;

        String StatusS = "";

        if (S == "1") {
            StatusS = (S1 == 1) ? "0" : "1";
            comando += StatusS + "|";
        }
        if (S == "2") {
            StatusS = (S2 == 1) ? "0" : "1";
            comando += StatusS + "|";
        }
        if (S == "3") {
            StatusS = (S3 == 1) ? "0" : "1";
            comando += StatusS + "|";
        }
        if (S == "4") {
            StatusS = (S4 == 1) ? "0" : "1";
            comando += StatusS + "|";
        }      

        writeData(comando);
    }

    private boolean writeData(String data) throws IOException {

        try {
            return write(data);
        } catch (IOException ex) {
            meuAdaptadorBluetooth = BluetoothAdapter.getDefaultAdapter();
            Connect(true);
            return write(data);
        }
    }

    private boolean write(String data) throws IOException {

        byte[] msgBuffer = data.getBytes();

        if(mmSocket.isConnected()) {

            mmOutStream.write(msgBuffer, 0, msgBuffer.length);
            return true;
        }
        else {
            Toast.makeText(this, "Dispositivo não conectado, reconecte e tente novamente!", Toast.LENGTH_LONG).show();
            return false;

        }

    }

    public void beginListenForCommands() {

        try {
            mmInStream = mmSocket.getInputStream();
        } catch (IOException e) {

            Toast.makeText(this, "Dispositivo não conectado, reconecte e tente novamente!", Toast.LENGTH_LONG).show();
        }

        Thread workerThread = new Thread(new Runnable() {
            public void run() {
                while (!Thread.currentThread().isInterrupted() && !stopWorker) {
                    try {
                        int bytesAvailable = mmInStream.available();
                        if (bytesAvailable > 0) {
                            byte[] packetBytes = new byte[bytesAvailable];
                            mmInStream.read(packetBytes);
                            for (int i = 0; i < bytesAvailable; i++) {
                                byte b = packetBytes[i];
                                if (b == delimiter) {
                                    byte[] encodedBytes = new byte[readBufferPosition];
                                    System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                    final String data = new String(encodedBytes, "US-ASCII");
                                    readBufferPosition = 0;
                                    handler.post(new Runnable() {
                                        public void run() {

                                            if (data.contains("COMANDOS")) {
                                                AtualizaDadosPlaca(data);
                                            }

                                            //txtMsg.setText(data);
                                            txtMsg.setText("");
                                        }
                                    });
                                } else {
                                    readBuffer[readBufferPosition++] = b;
                                }
                            }
                        }
                    } catch (IOException ex) {
                        stopWorker = true;
                        //Toast.makeText(this, "Ocorreu um erro durante o recebimendo dos dados do dispositivo!", Toast.LENGTH_LONG).show();
                    }
                }
            }
        });

        workerThread.start();
    }

    private void AtualizaDadosPlaca(String data) {

        try {
            String[] DataCommand = data.split("#");

            S1 = Integer.parseInt(DataCommand[1]);
            S2 = Integer.parseInt(DataCommand[2]);
            S3 = Integer.parseInt(DataCommand[3]);
            S4 = Integer.parseInt(DataCommand[4]);           
            SR = Integer.parseInt(DataCommand[5]);
            SG = Integer.parseInt(DataCommand[6]);
            SB = Integer.parseInt(DataCommand[7]);
            
			                     
            if (S1 == 1) {
                imgS1.setImageResource(R.drawable.on);
            } else {
                imgS1.setImageResource(R.drawable.off);
            }
            txtS1.setText(NameS1);

            if (S2 == 1) {
                imgS2.setImageResource(R.drawable.on);
            } else {
                imgS2.setImageResource(R.drawable.off);
            }
            txtS2.setText(NameS2);

            if (S3 == 1) {
                imgS3.setImageResource(R.drawable.on);
            } else {
                imgS3.setImageResource(R.drawable.off);
            }
            txtS3.setText(NameS3);

            if (S4 == 1) {
                imgS4.setImageResource(R.drawable.on);
            } else {
                imgS4.setImageResource(R.drawable.off);
            }
            txtS4.setText(NameS4);

            txtSRGB.setText(NameSRGB);

            if (FirstTime) {
                seekBarR.setProgress(SR / 28);
                seekBarR.refreshDrawableState();

                seekBarG.setProgress(SG / 28);
                seekBarG.refreshDrawableState();

                seekBarB.setProgress(SB / 28);
                seekBarB.refreshDrawableState();
                FirstTime = false;  
            }

        }
        catch (Exception ex) {
           // Toast.makeText(this, "Erro na reconexão de parametros!", Toast.LENGTH_LONG).show();
        }
    }
}