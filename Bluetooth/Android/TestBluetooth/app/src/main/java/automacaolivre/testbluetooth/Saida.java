package automacaolivre.testbluetooth;

public class Saida {
    private String _Codigo;
    private String _Nome;    

    public Saida() {

    }

    public Saida(String Codigo, String Nome) {
        this._Codigo = Codigo;
        this._Nome = Nome;        
    }

    public String getCodigo() {
        return _Codigo;
    }

    public void setCodigo(String Codigo) {
        this._Codigo = Codigo;
    }

    public String getNome() {
        return _Nome;
    }

    public void setNome(String Nome) {
        this._Nome = Nome;
    }
  
}