
var ipArduino = 'http://192.168.0.201';

var dadosRecebidos;
var tipoAgendamento = "";


function BuscaDados() {

    var call = $.ajax({
        url: ipArduino,
        dataType: 'jsonp',
        jsonpCallback: 'dataCB'
    })
    .done(function (data) {
        console.log(data);
        BindData(data);
       // GravaLog();
        console.log("Busca dados executado com sucesso!");
    });
}

function BindData(data) {

    dadosRecebidos = data;

    $('#S1').removeClass('btn');
    $('#S1').removeClass('btn btn-success');
    $('#S1').removeClass('btn btn-danger');
    $('#S2').removeClass('btn');
    $('#S2').removeClass('btn btn-success');
    $('#S2').removeClass('btn btn-danger');
    $('#S3').removeClass('btn');
    $('#S3').removeClass('btn btn-success');
    $('#S3').removeClass('btn btn-danger');
    $('#S4').removeClass('btn');
    $('#S4').removeClass('btn btn-success');
    $('#S4').removeClass('btn btn-danger');

    $('#WHI').removeClass('btn');
    $('#WHI').removeClass('btn btn-success');
    $('#WHI').removeClass('btn btn-danger');
    $('#BLU').removeClass('btn');
    $('#BLU').removeClass('btn btn-success');
    $('#BLU').removeClass('btn btn-danger');
    $('#RED').removeClass('btn');
    $('#RED').removeClass('btn btn-success');
    $('#RED').removeClass('btn btn-danger');
    $('#GRE').removeClass('btn');
    $('#GRE').removeClass('btn btn-success');
    $('#GRE').removeClass('btn btn-danger');


    if (data.Auto == 1) {
        $("#rdModoA").prop("checked", true);
        $("#imgAuto").attr("src", "Img/icoAuto.png")
        $("#Modo").text("ON");
    }
    else {
        $("#rdModoM").prop("checked", true);
        $("#imgAuto").attr("src", "Img/icoManual.png")
        $("#Modo").text("OFF");
    }
	
    $("#DataHW").text(RetornaData() + " " + RetornaHora());

    if (data.S1 == 1) {
        $("#S1").html('On');
        $('#S1').addClass('btn btn-success');
    }
    else {
        $("#S1").html('Off');
        $('#S1').addClass('btn btn-danger');
    }
	$("#AgeS1").text(data.AgeS1HrI + ":00 ate " + data.AgeS1HrF + ":59");

    if (data.S2 == 1) {
        $("#S2").html('On');
        $('#S2').addClass('btn btn-success');
    }
    else {
        $("#S2").html('Off');
        $('#S2').addClass('btn btn-danger');
    }
	$("#AgeS2").text(data.AgeS2HrI + ":00 ate " + data.AgeS2HrF + ":59");

    if (data.S3 == 1) {
        $("#S3").html('On');
        $('#S3').addClass('btn btn-success');
    }
    else {
        $("#S3").html('Off');
        $('#S3').addClass('btn btn-danger');
    }
    $("#AgeS3").text(data.AgeS3HrI + ":00 ate " + data.AgeS3HrF + ":59");

    if (data.S4 == 1) {
        $("#S4").html('On');
        $('#S4').addClass('btn btn-success');
    }
    else {
        $("#S4").html('Off');
        $('#S4').addClass('btn btn-danger');
    }
    $("#AgeS4").text(data.AgeS4HrI + ":00 ate " + data.AgeS4HrF + ":59");


    if (data.Red == 255 && data.Green == 255 && data.Blue == 255) {
        $("#WHI").text("On");
        $('#WHI').addClass('btn btn-success');
    }
    else {
        $("#WHI").text("Off");
        $('#WHI').addClass('btn btn-danger');
    }

    if (data.Red == 0 && data.Green == 0 && data.Blue > 0) {
        $("#BLU").text("On");
        $('#BLU').addClass('btn btn-success');
    }
    else {
        $("#BLU").text("Off");
        $('#BLU').addClass('btn btn-danger');
    }

    if (data.Red > 0 && data.Green == 0 && data.Blue == 0) {
        $("#RED").text("On");
        $('#RED').addClass('btn btn-success');
    }
    else {
        $("#RED").text("Off");
        $('#RED').addClass('btn btn-danger');
    }

    if (data.Red == 0 && data.Green > 0 && data.Blue == 0) {
        $("#GRE").text("On");
        $('#GRE').addClass('btn btn-success');
    }
    else {
        $("#GRE").text("Off");
        $('#GRE').addClass('btn btn-danger');
    }

    $("#AgeRGBWHITE").text(data.AgeRGBWHITEHrI + ":00 ate " + data.AgeRGBWHITEHrF + ":59");
    $("#AgeRGBBLUE").text(data.AgeRGBBLUEHrI + ":00 ate " + data.AgeRGBBLUEHrF + ":59");
    
    HabilitaModo(data.Auto)

    HideLoading();
}
function EnviarComandoSaida(saida) {

    $("#icoExec" + saida).show();
    var statusAtual = $("#" + saida).html();
    var cmd = "?" + saida;
    if (statusAtual == "On") {
        cmd += "D";
    }
    else {
        cmd += "L";
    }
    Enviar(cmd);
}

function EnviarComandoRGB(saida) {

    $("#icoExec" + saida).show();
    var statusAtual = $("#" + saida).html();
    var cmd = "?";
    if (statusAtual == "On") {
        cmd += "RGBOFF";
    }
    else {
        cmd += saida;
    }
    Enviar(cmd);
}

function EnviarComando(saida) {
    $("#icoExec" + saida).show();
    Enviar("?" + saida);
}

function EnviarComandoAUTO() {


    if (dadosRecebidos.Auto == 1) {
        EnviarComando("AUTOD");
    }
    else {
        EnviarComando("AUTOL");
    }        
}



function Enviar(comando) {

    var urlComando = ipArduino + comando;
    console.log(urlComando);

    var call = $.ajax({
        url: urlComando,
        dataType: 'jsonp',
        jsonpCallback: 'dataCB'
    })

        .done(function (data) {
            console.log(data);
            BindData(data);
            console.log("Comando enviado com sucesso!");

            if (comando == "?AUTOL" || comando == "?AUTOD") {
                //Rebind para busca de dados após ativação de modo
                console.log("Buscando novamente dados do modo Automatico")
                $('#icoExeAUTOL').show();
                BuscaDados();
            }
        });
}

function HabilitaModo(Modo) {
    if (Modo == 1) // automatico, desabilitar funcoes de agendamento com faixa de horário
    {
        $('#S1').prop('disabled', true);
        $('#S2').prop('disabled', true);
        $('#S3').prop('disabled', true);
        $('#S4').prop('disabled', true);
        $('#WHI').prop('disabled', true);
        $('#BLU').prop('disabled', true);
        $('#RED').prop('disabled', true);
        $('#GRE').prop('disabled', true);
    }
    else {
        $('#S1').prop('disabled', false);
        $('#S2').prop('disabled', false);
        $('#S3').prop('disabled', false);
        $('#S4').prop('disabled', false);
        $('#WHI').prop('disabled', false);
        $('#BLU').prop('disabled', false);
        $('#RED').prop('disabled', false);
        $('#GRE').prop('disabled', false);
    }
}


function MostraPopUpHorarioArduino(acao) {
    $('#modalHorarioArduino').modal('show')

    $("#modalHorarioArduinoTitle").text("Alterar Horario Equipamento");

    $("#DataArduino").val(RetornaData());
    $("#HoraArduino").val(RetornaHora());
}


function AlterarHorarioArduino() {

    var DataArduino = $("#DataArduino").val();
    var HoraArduino = $("#HoraArduino").val();
    var cmdIni = "?DataHora" + "y" + DataArduino + "yz" + HoraArduino + "z";
    Enviar(cmdIni);

    //BuscaDados();
    $('#modalHorarioArduino').modal('hide')

}

function MostraPopUpPeriodo(acao) {
    $('#modalPeriodo').modal('show')

    if (acao == "S1") {
        tipoAgendamento = "?AgeS1Hr";
        $("#modalPeriodoTitle").text("Agendamento Saida 1");
        $("#hrInicio").val(dadosRecebidos.AgeS1HrI);
        $("#hrFim").val(dadosRecebidos.AgeS1HrF);
    }
	else if (acao == "S2") {
        tipoAgendamento = "?AgeS2Hr";
        $("#modalPeriodoTitle").text("Agendamento Saida 2");
        $("#hrInicio").val(dadosRecebidos.AgeS2HrI);
        $("#hrFim").val(dadosRecebidos.AgeS2HrF);
    }
	else if (acao == "S3") {
        tipoAgendamento = "?AgeS3Hr";
        $("#modalPeriodoTitle").text("Agendamento Saida 3");
        $("#hrInicio").val(dadosRecebidos.AgeS3HrI);
        $("#hrFim").val(dadosRecebidos.AgeS3HrF);
    }
    else if (acao == "S4") {
        tipoAgendamento = "?AgeS4Hr";
        $("#modalPeriodoTitle").text("Agendamento Saida 4");
        $("#hrInicio").val(dadosRecebidos.AgeS4HrI);
        $("#hrFim").val(dadosRecebidos.AgeS4HrF);
    }
    else if (acao == "WHI") {
        tipoAgendamento = "?AgeRGBWHITEHr";
        $("#modalPeriodoTitle").text("Agendamento Saida RGB - White");
        $("#hrInicio").val(dadosRecebidos.AgeRGBWHITEHrI);
        $("#hrFim").val(dadosRecebidos.AgeRGBWHITEHrF);
    }
    else if (acao == "BLU") {
        tipoAgendamento = "?AgeRGBBLUEHr";
        $("#modalPeriodoTitle").text("Agendamento Saida RGB - Blue");
        $("#hrInicio").val(dadosRecebidos.AgeRGBBLUEHrI);
        $("#hrFim").val(dadosRecebidos.AgeRGBBLUEHrF);
    }
}

function AlterarPeriodo() {

    var horaInicio = $("#hrInicio").val();
    var horaFim = $("#hrFim").val();
    var cmdIni = tipoAgendamento + "I" + "y" + horaInicio + "y" + tipoAgendamento + "F" + "z" + horaFim + "z";
    Enviar(cmdIni);

    BuscaDados();

    $('#modalPeriodo').modal('hide')
}


function MostraPopUpHorario(acao) {

    $('#modalHorario').modal('show')
    if (acao == "FEE1") {
        tipoAgendamento = "?AgeFeed1";
        $("#modalHorarioTitle").text("Agendamento Alimentacao 1");
        $("#hrHorario").val(dadosRecebidos.AgeFeed1);
    }
    else if (acao == "FEE2") {
        tipoAgendamento = "?AgeFeed2";
        $("#modalHorarioTitle").text("Agendamento Alimentacao 2");
        $("#hrHorario").val(dadosRecebidos.AgeFeed2);
    }
}

function AlterarHorario() {
    var hora = $("#hrHorario").val();
    var cmdHr = tipoAgendamento + "y" + hora + "y";
    Enviar(cmdHr);
    $('#modalHorario').modal('hide');
}

function HideLoading() {

    $('#icoExeAUTOL').hide();
    $('#icoExeAUTOD').hide();

    $('#icoExecS1').hide();
    $('#icoExecS2').hide();
    $('#icoExecS3').hide();
    $('#icoExecS4').hide();

    $('#icoExecWHI').hide();
    $('#icoExecBLU').hide();
    $('#icoExecRED').hide();
    $('#icoExecGRE').hide();
    $('#icoExecFEE1').hide();
    $('#icoExecFEE2').hide();
    $('#icoExecPHC').hide();
}

function RetornaData() {

    var data = "";

    if (dadosRecebidos.Day < 10) {
        data = "0" + dadosRecebidos.Day + "/";
    }
    else {
        data = dadosRecebidos.Day + "/";
    }

    if (dadosRecebidos.Mounth < 10) {
        data += "0" + dadosRecebidos.Mounth + "/";
    }
    else {
        data += dadosRecebidos.Mounth + "/";
    }
    data += "20" + dadosRecebidos.Year;

    return data;
}

function RetornaHora() {

    var hora = "";

    if (dadosRecebidos.Hour < 10) {
        hora = "0" + dadosRecebidos.Hour + ":";
    }
    else {
        hora = dadosRecebidos.Hour + ":";
    }

    if (dadosRecebidos.Minute < 10) {
        hora += "0" + dadosRecebidos.Minute + ":";
    }
    else {
        hora += dadosRecebidos.Minute + ":";
    }

    if (dadosRecebidos.Second < 10) {
        hora += "0" + dadosRecebidos.Second;
    }
    else {
        hora += dadosRecebidos.Second;
    }

    return hora;

}
