package automacaolivre.testbluetooth;

import android.os.Bundle;
import android.content.Intent;
import android.app.Activity;
import android.widget.Button;
import android.widget.EditText;
import android.view.View;
import android.view.View.OnClickListener;
import android.content.SharedPreferences;
import android.widget.TextView;

public class SetupDevice extends Activity  {

    private String NameS1 = "";
    private EditText edtS1;
    
	private String NameS2 = "";
    private EditText edtS2;
    
	private String NameS3 = "";
    private EditText edtS3;
    
	private String NameS4 = "";
    private EditText edtS4;
	
	private String NameSRGB = "";
    private EditText edtSRGB;

    private Button btAlterar;


    SharedPreferences.Editor editor;
    SharedPreferences sharedPreferences;

    @Override
    public void onCreate(final Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.setup_device);

        sharedPreferences = getSharedPreferences("APP_PREFS", getBaseContext().MODE_PRIVATE);

        btAlterar = (Button) findViewById(R.id.btAlterar);

        edtS1 = (EditText) findViewById(R.id.edtS1);
        NameS1 = sharedPreferences.getString("S1", "S1");
        edtS1.setText(NameS1);
        
		edtS2 = (EditText) findViewById(R.id.edtS2);
        NameS2 = sharedPreferences.getString("S2", "S2");
        edtS2.setText(NameS2);
        
		edtS3 = (EditText) findViewById(R.id.edtS3);
        NameS3 = sharedPreferences.getString("S3", "S3");
        edtS3.setText(NameS3);
        
		edtS4 = (EditText) findViewById(R.id.edtS4);
        NameS4 = sharedPreferences.getString("S4", "S4");
        edtS4.setText(NameS4);
        
				
		edtSRGB = (EditText) findViewById(R.id.edtSRGB);
        NameSRGB = sharedPreferences.getString("SRGB", "SRGB");
        edtSRGB.setText(NameSRGB);
        
		
        btAlterar.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View arg0) {

                sharedPreferences = getSharedPreferences("APP_PREFS", 0);
                editor = sharedPreferences.edit();

                editor.putString("S1", edtS1.getText().toString());                
				editor.putString("S2", edtS2.getText().toString());
                editor.putString("S3", edtS3.getText().toString());
                editor.putString("S4", edtS4.getText().toString());
                editor.putString("SRGB", edtSRGB.getText().toString());
               										
                editor.commit();
                Bundle conData = new Bundle();
                conData.putString("OK", "OK");
                Intent intent = new Intent();
                intent.putExtras(conData);
                setResult(2, intent);
                finish();
            }
        });
    }


}
